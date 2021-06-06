package com.example.mysmartcamera.mycamera.adapter;

import android.content.Context;
import android.graphics.Bitmap;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import com.example.mysmartcamera.R;

import java.util.List;

import butterknife.BindView;
import butterknife.ButterKnife;




public class Adapter extends RecyclerView.Adapter<Adapter.MyViewHolder> {

    private Context mContext;
    private List<Bitmap> mBitmapList;

    public Adapter(Context context) {
        mContext = context;

    }
    public void addBitmapList(List<Bitmap> bitmapList){
        mBitmapList = bitmapList;
        notifyDataSetChanged();
    }
    @Override
    public MyViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(mContext).inflate(R.layout.sel_cover_item, parent, false);
        return new MyViewHolder(view);
    }

    @Override
    public void onBindViewHolder(MyViewHolder holder, int position) {
        if(position < mBitmapList.size()) {
            holder.mSelCoverIv.setImageBitmap(mBitmapList.get(position));
        }
    }

    @Override
    public int getItemCount() {
        int ret = 0;
        if (mBitmapList != null) {
            ret = mBitmapList.size();
        }
        return ret;
    }

    class MyViewHolder extends RecyclerView.ViewHolder {
        @BindView(R.id.sel_cover_iv)
        ImageView mSelCoverIv;
        public MyViewHolder(View itemView) {
            super(itemView);
            ButterKnife.bind(this, itemView);
        }
    }
}
