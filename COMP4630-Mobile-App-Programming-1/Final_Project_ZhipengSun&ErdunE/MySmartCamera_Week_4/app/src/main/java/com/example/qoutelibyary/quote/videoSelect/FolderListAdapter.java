package com.example.qoutelibyary.quote.videoSelect;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.example.mysmartcamera.R;
import com.example.mysmartcamera.mycamera.adapter.BaseAdapter;
import com.example.qoutelibyary.quote.videoSelect.beans.Directory;

import java.util.ArrayList;



public class FolderListAdapter extends BaseAdapter<Directory, FolderListAdapter.FolderListViewHolder> {
    private FolderListListener mListener;

    public FolderListAdapter(Context ctx, ArrayList<Directory> list) {
        super(ctx, list);
    }

    @Override
    public FolderListViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View itemView = LayoutInflater.from(mContext).inflate(R.layout.vw_layout_item_folder_list,
                parent, false);
        return new FolderListViewHolder(itemView);
    }

    @Override
    public void onBindViewHolder(final FolderListViewHolder holder, int position) {
        holder.mTvTitle.setText(mList.get(position).getName());
        holder.itemView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (mListener != null) {
                    mListener.onFolderListClick(mList.get(holder.getAdapterPosition()));
                }
            }
        });
    }

    @Override
    public int getItemCount() {
        return mList.size();
    }

    class FolderListViewHolder extends RecyclerView.ViewHolder {
        private TextView mTvTitle;

        public FolderListViewHolder(View itemView) {
            super(itemView);

            mTvTitle = (TextView) itemView.findViewById(R.id.tv_folder_title);
        }
    }

    public interface FolderListListener {
        void onFolderListClick(Directory directory);
    }

    public void setListener(FolderListListener listener) {
        this.mListener = listener;
    }
}
