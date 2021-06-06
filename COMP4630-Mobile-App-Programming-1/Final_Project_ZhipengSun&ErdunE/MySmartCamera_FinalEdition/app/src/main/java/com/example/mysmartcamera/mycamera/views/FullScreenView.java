package com.example.mysmartcamera.mycamera.views;

import android.content.Context;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.widget.VideoView;



public class FullScreenView extends VideoView {
    public FullScreenView(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
    }

    public FullScreenView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public FullScreenView(Context context) {
        super(context);
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);
        int width = getDefaultSize(0, widthMeasureSpec);
        int height = getDefaultSize(0, heightMeasureSpec);
        setMeasuredDimension(width, height);
    }

    @Override
    public boolean onTouchEvent(MotionEvent ev) {   //不执行父类的toggleMediaControlsVisiblity();方法  弹出默认进度条
        return true;
    }
}
