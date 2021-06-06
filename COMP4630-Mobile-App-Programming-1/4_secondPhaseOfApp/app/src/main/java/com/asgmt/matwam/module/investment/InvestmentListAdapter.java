package com.asgmt.matwam.module.investment;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ProgressBar;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.recyclerview.widget.DiffUtil;
import androidx.recyclerview.widget.RecyclerView;

import com.asgmt.matwam.R;
import com.asgmt.matwam.module.base.BaseListAdapter;
import com.asgmt.matwam.store.Store;
import com.asgmt.matwam.store.local.investment.Investment;
import com.asgmt.matwam.store.local.weather.Weather;

import java.util.Objects;

public class InvestmentListAdapter extends BaseListAdapter<Investment, InvestmentListAdapter.InvestmentViewHolder> {

    public InvestmentListAdapter(Context context) {
        super(context, new DiffUtil.ItemCallback<Investment>() {
            @Override
            public boolean areItemsTheSame(@NonNull Investment oldItem, @NonNull Investment newItem) {
                return Objects.equals(oldItem.id, newItem.id);
            }

            @Override
            public boolean areContentsTheSame(@NonNull Investment oldItem, @NonNull Investment newItem) {
                return oldItem.equals(newItem);
            }
        });
    }

    public void fetchInvestments() {
        for (int i = 0; i < getItemCount(); i++) {
            fetchInvestment(i);
        }
    }

    public void fetchInvestment(final int position) {
        final Investment investment = getItem(position);
        investment.isLoading = true;
        notifyItemChanged(position);
        Store.getInstance(_context).fetchInvestment(investment, new Store.Callback<Investment>() {
            @Override
            public void onResponse(Investment data) {
                investment.isLoading = false;
                investment.open = data.open;
                investment.high = data.high;
                investment.low = data.low;
                investment.close = data.close;
                notifyItemChanged(position);
            }

            @Override
            public void onError(String msg) {
                investment.isLoading = false;
                notifyItemChanged(position);
            }
        });
    }


    @NonNull
    @Override
    public InvestmentViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_investment, parent, false);
        return new InvestmentViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull InvestmentViewHolder holder, int position) {
        final Investment investment = getItem(position);
        holder.clContent.setVisibility(investment.isLoading ? View.INVISIBLE : View.VISIBLE);
        holder.pbLoading.setVisibility(investment.isLoading ? View.VISIBLE : View.INVISIBLE);
        if (!investment.isLoading) {
            holder.tvSymbol.setText(investment.name);
            holder.tvOpen.setText(investment.open);
            holder.tvHigh.setText(investment.high);
            holder.tvLow.setText(investment.low);
            holder.tvClose.setText(investment.close);
        }
    }

    static class InvestmentViewHolder extends RecyclerView.ViewHolder {

        ConstraintLayout clContent;
        ProgressBar pbLoading;
        TextView tvSymbol;
        TextView tvOpen;
        TextView tvHigh;
        TextView tvLow;
        TextView tvClose;

        public InvestmentViewHolder(@NonNull View itemView) {
            super(itemView);
            clContent = itemView.findViewById(R.id.ii_cl_content);
            pbLoading = itemView.findViewById(R.id.ii_pb_loading);
            tvSymbol = itemView.findViewById(R.id.ii_tv_symbol);
            tvOpen = itemView.findViewById(R.id.ii_tv_open);
            tvHigh = itemView.findViewById(R.id.ii_tv_high);
            tvLow = itemView.findViewById(R.id.ii_tv_low);
            tvClose = itemView.findViewById(R.id.ii_tv_close);
        }
    }
}
