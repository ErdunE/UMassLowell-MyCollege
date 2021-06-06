package com.asgmt.matwam.module.fact;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.DiffUtil;
import androidx.recyclerview.widget.RecyclerView;

import com.asgmt.matwam.R;
import com.asgmt.matwam.store.local.fact.Fact;
import com.asgmt.matwam.module.base.BaseListAdapter;

public class FactListAdapter extends BaseListAdapter<Fact, FactListAdapter.FactViewHolder> {

    public FactListAdapter(Context context) {
        super(context, new DiffUtil.ItemCallback<Fact>() {
            @Override
            public boolean areItemsTheSame(@NonNull Fact oldItem, @NonNull Fact newItem) {
                return false;
            }

            @Override
            public boolean areContentsTheSame(@NonNull Fact oldItem, @NonNull Fact newItem) {
                return false;
            }
        });
    }

    @NonNull
    @Override
    public FactViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_fact, parent, false);
        return new FactViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull FactViewHolder holder, final int position) {
        final Fact fact = _differ.getCurrentList().get(position);
        holder.tvLabel.setText(fact.label);
        holder.tvContent.setText(fact.content);
        holder.itemView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (_onItemClickListener != null) {
                    _onItemClickListener.onItemClick(position);
                }
            }
        });
    }

    static class FactViewHolder extends RecyclerView.ViewHolder {

        TextView tvLabel;
        TextView tvContent;

        public FactViewHolder(@NonNull View itemView) {
            super(itemView);
            tvLabel = itemView.findViewById(R.id.if_tv_label);
            tvContent = itemView.findViewById(R.id.if_tv_content);
        }
    }
}
