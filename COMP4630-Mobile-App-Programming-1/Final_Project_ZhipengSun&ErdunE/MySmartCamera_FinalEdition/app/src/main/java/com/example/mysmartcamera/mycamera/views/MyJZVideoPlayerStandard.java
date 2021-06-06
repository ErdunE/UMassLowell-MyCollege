package com.example.mysmartcamera.mycamera.views;

import android.content.Context;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;
import android.widget.RelativeLayout;

import com.example.mysmartcamera.R;
import com.example.mysmartcamera.mycamera.utils.DisplayUtil;
import com.example.qoutelibyary.quote.videoPlayer.JZMediaManager;
import com.example.qoutelibyary.quote.videoPlayer.JZVideoPlayerStandard;

public class MyJZVideoPlayerStandard extends JZVideoPlayerStandard {
    private boolean mIsExit = false;
    private IPlayFinish mIPlayFinish;

    public MyJZVideoPlayerStandard(Context context) {
        super(context);
    }

    public MyJZVideoPlayerStandard(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    public void init(Context context) {
        super.init(context);
        initPosition();
    }
    public void setProgressBottom(){
        RelativeLayout.LayoutParams layoutParams = (RelativeLayout.LayoutParams)bottomProgressBar.getLayoutParams();
        layoutParams.setMargins(0,0,0,0);
        bottomProgressBar.setLayoutParams(layoutParams);
    }
    public void initPosition() {
        RelativeLayout.LayoutParams layoutParams = (RelativeLayout.LayoutParams)bottomProgressBar.getLayoutParams();
        int i = DisplayUtil.dp2px(getContext(), 50);
        layoutParams.setMargins(0,0,0,i);
        bottomProgressBar.setLayoutParams(layoutParams);
    }





    @Override
    public void startVideo() {
        setNeedLoop(true);
        super.startVideo();
        mIPlayFinish = null;
    }


    @Override
    public void onVideoRendingStart() {
        try {
            if(isCloseVoice){
                MediaPlayer mediaPlayer = JZMediaManager.instance().mediaPlayer;
                if (mediaPlayer != null) {
                    mediaPlayer.setVolume(0,0);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        if(mIsExit){
            JZVideoPlayerStandard.releaseAllVideos();
        }
        super.onVideoRendingStart();
    }
    public void setOnPrepared(boolean isExit){
        mIsExit = isExit;
    }

    @Override
    public void onStateNormal() {
        super.onStateNormal();
    }

    @Override
    public void onStatePreparing() {
        super.onStatePreparing();
    }

    @Override
    public void onStatePlaying() {
        super.onStatePlaying();
    }

    @Override
    public void onStatePause() {
        super.onStatePause();
    }



    @Override
    public void onStateError() {
        super.onStateError();
    }

    @Override
    public void onStateAutoComplete() {
        super.onStateAutoComplete();
        if (mIPlayFinish != null) {
            mIPlayFinish.playfinish();
        }
    }

    @Override
    public void onInfo(int what, int extra) {
        super.onInfo(what, extra);
    }

    @Override
    public void onError(int what, int extra) {
        super.onError(what, extra);
    }

    @Override
    public void startWindowFullscreen() {
        super.startWindowFullscreen();
    }

    @Override
    public void startWindowTiny() {
        super.startWindowTiny();
    }

    @Override
    public void handlerOnPause() {
        if (mHandlerClickVideoPauseListener != null) {
            mHandlerClickVideoPauseListener.handlerPause();
        }
    }
    @Override
    public void handlerOnStart() {
        if (mHandlerClickVideoPauseListener != null) {
            mHandlerClickVideoPauseListener.handlerStart();
        }
    }

    private HandlerClickVideoPauseListener mHandlerClickVideoPauseListener;
    public void setHandlerClickVideoPauseListener(HandlerClickVideoPauseListener mHandlerClickVideoPauseListener){
        this.mHandlerClickVideoPauseListener = mHandlerClickVideoPauseListener;
    }
    public interface HandlerClickVideoPauseListener{
        void handlerPause();
        void handlerStart();
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        WindowManager wm = (WindowManager) getContext()
                .getSystemService(Context.WINDOW_SERVICE);

        int width = wm.getDefaultDisplay().getWidth();
        int height = wm.getDefaultDisplay().getHeight();
        widthMeasureSpec = View.MeasureSpec.makeMeasureSpec(width, View.MeasureSpec.EXACTLY);
        heightMeasureSpec = View.MeasureSpec.makeMeasureSpec(height, View.MeasureSpec.EXACTLY);
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);
    }

    private boolean isCloseVoice = false;


    public interface IPlayFinish{
        void playfinish();
    }
}
