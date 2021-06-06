package com.example.mysmartcamera.views;

import android.content.Context;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;
import android.widget.RelativeLayout;

import com.example.mysmartcamera.objects.JZMediaManager;
import com.example.mysmartcamera.utils.DisplayUtil;


public class PublicVideoJZVideo extends JZVideoPlayerStandard {
    private boolean mIsExit = false;

    public PublicVideoJZVideo(Context context) {
        super(context);
    }

    public PublicVideoJZVideo(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    public void init(Context context) {
        super.init(context);
        initPosition();
    }

    private void initPosition() {
        RelativeLayout.LayoutParams layoutParams = (RelativeLayout.LayoutParams)bottomProgressBar.getLayoutParams();
        int i = DisplayUtil.dp2px(getContext(), -10);
        layoutParams.setMargins(0,0,0,i);
        bottomProgressBar.setLayoutParams(layoutParams);
    }

    @Override
    public void onClick(View v) {
        super.onClick(v);
        int i = v.getId();

    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        return true;
    }


    @Override
    public void startVideo() {
        super.startVideo();
    }

    /**
     * onPrepared
     */
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

    }
    @Override
    public void handlerOnStart() {

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
    public void clostVoice(){
        isCloseVoice = true;
    }
    //    AudioManager audioManager=(AudioManager)getSystemService(Service.AUDIO_SERVICE);
    public void OpenVolume(AudioManager audioManager){
        isCloseVoice = false;
        MediaPlayer mediaPlayer = JZMediaManager.instance().mediaPlayer;
        mediaPlayer.setAudioStreamType(AudioManager.STREAM_SYSTEM);
        mediaPlayer.setVolume(audioManager.getStreamVolume(AudioManager.STREAM_SYSTEM), audioManager.getStreamVolume(AudioManager.STREAM_SYSTEM));
        mediaPlayer.start();
    }

    public interface IPlayFinish{
        void playfinish();
    }
}
