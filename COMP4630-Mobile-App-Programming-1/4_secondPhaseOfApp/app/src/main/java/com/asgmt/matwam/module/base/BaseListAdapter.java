package com.asgmt.matwam.module.base;

import android.content.Context;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.AsyncListDiffer;
import androidx.recyclerview.widget.DiffUtil;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;
import java.util.Objects;

public abstract class BaseListAdapter<T, VH extends RecyclerView.ViewHolder> extends RecyclerView.Adapter<VH> {

    protected final Context _context;
    protected final AsyncListDiffer<T> _differ;
    protected OnItemClickListener<T> _onItemClickListener;
    protected OnItemChildClickListener<T> _onItemChildClickListener;

    public BaseListAdapter(Context context, DiffUtil.ItemCallback<T> callback) {
        _context = context;
        _differ = new AsyncListDiffer<T>(this, callback);
    }

    public void submitList(List<T> newList) {
        _differ.submitList(newList);
    }
    public void submitList(List<T> newList, Runnable commitCallback) {
        _differ.submitList(newList, commitCallback);
    }


    public T getItem(int position) { return _differ.getCurrentList().get(position); }
    public void setOnItemClickListener(OnItemClickListener<T> onItemClickListener) {
        _onItemClickListener = onItemClickListener;
    }
    public void setOnItemChildClickListener(OnItemChildClickListener<T> onItemChildClickListener) {
        _onItemChildClickListener = onItemChildClickListener;
    }

    @Override
    public int getItemCount() {
        return _differ.getCurrentList().size();
    }


    public interface OnItemClickListener<T> {
        void onItemClick(int position);
    }

    public  interface OnItemChildClickListener<T> {
        void onItemChildClick(int position);
    }
}
