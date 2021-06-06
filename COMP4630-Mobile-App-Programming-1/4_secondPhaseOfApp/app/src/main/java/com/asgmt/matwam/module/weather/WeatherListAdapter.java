package com.asgmt.matwam.module.weather;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.recyclerview.widget.DiffUtil;
import androidx.recyclerview.widget.RecyclerView;

import com.android.volley.toolbox.NetworkImageView;
import com.asgmt.matwam.R;
import com.asgmt.matwam.store.Store;
import com.asgmt.matwam.store.remote.Network;
import com.asgmt.matwam.store.local.weather.Weather;
import com.asgmt.matwam.module.base.BaseListAdapter;

import java.util.List;
import java.util.Objects;

public class WeatherListAdapter extends BaseListAdapter<Weather, WeatherListAdapter.WeatherViewHolder> {

    public WeatherListAdapter(Context context) {
        super(context, new DiffUtil.ItemCallback<Weather>() {
            @Override
            public boolean areItemsTheSame(@NonNull Weather oldItem, @NonNull Weather newItem) {
                return Objects.equals(oldItem.id, newItem.id);
            }

            @Override
            public boolean areContentsTheSame(@NonNull Weather oldItem, @NonNull Weather newItem) {
                return oldItem.equals(newItem);
            }
        });
    }

    public void fetchWeathers() {
        for (int i = 0; i < getItemCount(); i++) {
            fetchWeather(i);
        }
    }

    public void fetchWeather(final int position) {
        final Weather weather = getItem(position);
        weather.isLoading = true;
        notifyItemChanged(position);
        Store.getInstance(_context).fetchWeather(weather, new Store.Callback<Weather>() {
            @Override
            public void onResponse(Weather data) {
                weather.isLoading = false;
                weather.icon = data.icon;
                weather.summary = data.summary;
                notifyItemChanged(position);
            }

            @Override
            public void onError(String msg) {
                weather.isLoading = false;
                weather.summary = msg;
                notifyItemChanged(position);
            }
        });
    }

    @NonNull
    @Override
    public WeatherViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_weather, parent, false);
        return new WeatherViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull WeatherViewHolder holder, final int position) {
        final Weather weather = _differ.getCurrentList().get(position);
        holder.clContent.setVisibility(weather.isLoading ? View.INVISIBLE : View.VISIBLE);
        holder.pbLoading.setVisibility(weather.isLoading ? View.VISIBLE : View.INVISIBLE);
        if (!weather.isLoading) {
            Network.getInstance(_context).fetchImage(holder.nivWeather, weather.icon);
            holder.tvWeather.setText(weather.summary);
            if (!weather.isLoading) {
                holder.tvLabel.setText(weather.label);
                holder.tvPlace.setText(weather.place);
                holder.itemView.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View view) {
                        if (_onItemClickListener != null) {
                            _onItemClickListener.onItemClick(position);
                        }
                    }
                });
                holder.ivRefresh.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View view) {
                        if (_onItemChildClickListener != null) {
                            _onItemChildClickListener.onItemChildClick(position);
                        }
                    }
                });
            }
        }
    }

    static class WeatherViewHolder extends RecyclerView.ViewHolder {

        ConstraintLayout clContent;
        ProgressBar pbLoading;
        ImageView ivRefresh;
        TextView tvLabel;
        TextView tvPlace;
        NetworkImageView nivWeather;
        TextView tvWeather;

        public WeatherViewHolder(@NonNull View itemView) {
            super(itemView);
            clContent = itemView.findViewById(R.id.iw_cl_content);
            pbLoading = itemView.findViewById(R.id.iw_pb_loading);
            ivRefresh = itemView.findViewById(R.id.iw_iv_refresh);
            tvLabel = itemView.findViewById(R.id.iw_tv_label);
            tvPlace = itemView.findViewById(R.id.iw_tv_place);
            nivWeather = itemView.findViewById(R.id.iw_niv_weather);
            tvWeather = itemView.findViewById(R.id.iw_tv_weather);
        }
    }
}
