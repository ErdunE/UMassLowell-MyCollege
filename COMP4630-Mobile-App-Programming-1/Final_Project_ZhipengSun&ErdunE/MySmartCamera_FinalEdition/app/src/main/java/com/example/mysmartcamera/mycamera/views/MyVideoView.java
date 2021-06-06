package com.example.mysmartcamera.mycamera.views;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.VideoView;


public class MyVideoView extends VideoView {

    private int defaultWidth;
    private int defaultHeight;

    public MyVideoView(Context context) {
        this(context, null);
    }

    public MyVideoView(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public MyVideoView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        defaultWidth = context.getResources().getDisplayMetrics().widthPixels;
        defaultHeight = context.getResources().getDisplayMetrics().heightPixels;
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        int width = getDefaultSize(defaultWidth, widthMeasureSpec);
        int height = getDefaultSize(defaultHeight, heightMeasureSpec);
        setMeasuredDimension(width, height);
    }
}
