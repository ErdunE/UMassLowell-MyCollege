package com.example.mysmartcamera.views;

import android.content.Context;
import android.graphics.SurfaceTexture;
import android.media.MediaPlayer;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.Surface;
import android.view.SurfaceHolder;

import com.example.mysmartcamera.objects.VideoDrawer;
import com.example.mysmartcamera.objects.VideoInfo;
import com.example.mysmartcamera.utils.MediaPlayerWrapper;

import java.io.IOException;
import java.util.List;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;



public class VideoPreviewView extends GLSurfaceView implements GLSurfaceView.Renderer, MediaPlayerWrapper.IMediaCallback {
    private MediaPlayerWrapper mMediaPlayer;
    private VideoDrawer mDrawer;

    private MediaPlayerWrapper.IMediaCallback callback;

    public VideoPreviewView(Context context) {
        super(context,null);
    }

    public VideoPreviewView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }


    private void init(Context context) {
        setEGLContextClientVersion(2);
        setRenderer(this);
        setRenderMode(RENDERMODE_WHEN_DIRTY);
        setPreserveEGLContextOnPause(false);
        setCameraDistance(100);

        //初始化Drawer和VideoPlayer
        mMediaPlayer = new MediaPlayerWrapper();
        mMediaPlayer.setOnCompletionListener(this);
    }

    /**设置视频的播放地址*/
    public void setVideoPath(List<String> paths){
        mMediaPlayer.setDataSource(paths);
    }



    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
//        onDestroy();
        super.surfaceDestroyed(holder);
        Log.e("Atest", "surfaceDestroyed: ");
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

        SurfaceTexture surfaceTexture = null;
        surfaceTexture.setOnFrameAvailableListener(new SurfaceTexture.OnFrameAvailableListener() {
            @Override
            public void onFrameAvailable(SurfaceTexture surfaceTexture) {
                requestRender();
            }
        });
        Surface surface = new Surface(surfaceTexture);
        mMediaPlayer.setSurface(surface);
        try {
            mMediaPlayer.prepare();
        } catch (IOException e) {
            e.printStackTrace();
        }
        mMediaPlayer.start();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

    }


    @Override
    public void onDrawFrame(GL10 gl) {
        Log.e("a", "onDrawFrame: " );

    }
    public void onDestroy(){
        if (mMediaPlayer != null) {
            if(mMediaPlayer.isPlaying()){
                mMediaPlayer.stop();
            }
            mMediaPlayer.release();
        }
    }
    public void onTouch(final MotionEvent event){
        queueEvent(new Runnable() {
            @Override
            public void run() {

            }
        });
    }
    public void setOnFilterChangeListener(SlideGpuFilterGroup.OnFilterChangeListener listener){

    }

    @Override
    public void onVideoPrepare() {
        if (callback!= null){
            callback.onVideoPrepare();
        }
    }

    @Override
    public void onVideoStart() {
        if(callback!=null){
            callback.onVideoStart();
        }
    }

    @Override
    public void onVideoPause() {
        if (callback != null){
            callback.onVideoPause();
        }
    }

    @Override
    public void onCompletion(MediaPlayer mp) {
        if (callback != null){
            callback.onCompletion(mp);
        }
    }

    @Override
    public void onVideoChanged(final VideoInfo info) {

        if(callback!=null){
            callback.onVideoChanged(info);
        }
    }
    /**
     * isPlaying now
     * */
    public boolean isPlaying(){
        return mMediaPlayer.isPlaying();
    }
    /**
     * pause play
     * */
    public void pause(){
        if (mMediaPlayer != null) {
            mMediaPlayer.pause();
        }
    }
    /**
     * start play video
     * */
    public void start(){
        mMediaPlayer.start();
    }
    /**
     * 跳转到指定的时间点，只能跳到关键帧
     * */
    public void seekTo(int time){
        requestRender();
        mMediaPlayer.seekTo(time);
    }

    public int getVideoDuration(){
        return mMediaPlayer.getCurVideoDuration();




    }
}
