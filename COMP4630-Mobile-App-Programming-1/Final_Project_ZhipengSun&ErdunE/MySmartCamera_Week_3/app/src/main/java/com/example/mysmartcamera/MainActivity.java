package com.example.mysmartcamera;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.graphics.Point;
import android.hardware.Camera;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.example.mysmartcamera.objects.MediaObject;
import com.example.mysmartcamera.views.CameraView;
import com.example.mysmartcamera.views.CustomRecordImageView;
import com.example.mysmartcamera.views.FocusImageView;
import com.example.mysmartcamera.views.ProgressView;
import com.example.mysmartcamera.views.SlideGpuFilterGroup;

import java.lang.ref.WeakReference;
import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import Jni.FileUtils;
import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;

import static com.example.mysmartcamera.StaticFinalValues.CHANGE_IMAGE;
import static com.example.mysmartcamera.StaticFinalValues.DELAY_DETAL;
import static com.example.mysmartcamera.StaticFinalValues.OVER_CLICK;
import static com.example.mysmartcamera.StaticFinalValues.RECORD_MIN_TIME;

public class MainActivity extends AppCompatActivity implements View.OnTouchListener, SlideGpuFilterGroup.OnFilterChangeListener{
    private static final int VIDEO_MAX_TIME = 30 * 1000;
    @BindView(R.id.record_camera_view)
    CameraView mRecordCameraView;
    @BindView(R.id.video_record_progress_view)
    ProgressView mVideoRecordProgressView;
    @BindView(R.id.matching_back)
    LinearLayout mMatchingBack;
    @BindView(R.id.video_record_finish_iv)
    Button mVideoRecordFinishIv;
    @BindView(R.id.switch_camera)
    ImageView mMeetCamera;
    @BindView(R.id.index_delete)
    LinearLayout mIndexDelete;
    @BindView(R.id.index_album)
    TextView mIndexAlbum;
    @BindView(R.id.custom_record_image_view)
    CustomRecordImageView mCustomRecordImageView;
    @BindView(R.id.count_down_tv)
    TextView mCountDownTv;
    @BindView(R.id.record_btn_ll)
    FrameLayout mRecordBtnLl;
    @BindView(R.id.meet_mask)
    ImageView mMeetMask;
    @BindView(R.id.video_filter)
    ImageView mVideoFilter;
    @BindView(R.id.recorder_focus_iv)
    FocusImageView mRecorderFocusIv;
    @BindView(R.id.count_time_down_iv)
    ImageView mCountTimeDownIv;
    public int mNum = 0;
    private long mLastTime = 0;
    public float mRecordTimeInterval;
    ExecutorService executorService;
    private MediaObject mMediaObject;

    private MyHandler mMyHandler =new MyHandler(this);
    private boolean isRecording = false;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ButterKnife.bind(this);
        initView();
    }

    @SuppressLint("ClickableViewAccessibility")
    private void initView() {
        if (mMediaObject == null) {
            mMediaObject = new MediaObject();
        }
        executorService = Executors.newSingleThreadExecutor();
        mRecordCameraView.setOnTouchListener(this);
        setBackAlpha(mVideoRecordFinishIv,127);
    }

    @Override
    protected void onResume() {
        super.onResume();
        //mVideoRecordProgressView.setData(mMediaObject);
    }
    @OnClick({R.id.matching_back, R.id.video_record_finish_iv, R.id.switch_camera,  R.id.index_delete, R.id.index_album, R.id.custom_record_image_view, R.id.count_down_tv, R.id.meet_mask, R.id.video_filter})
    public void onViewClicked(View view) {
        if (System.currentTimeMillis() - mLastTime < 500) {
            return;
        }
        mLastTime = System.currentTimeMillis();
        if (view.getId() != R.id.index_delete) {
            if (mMediaObject != null) {
                MediaObject.MediaPart part = mMediaObject.getCurrentPart();
                if (part != null) {
                    if (part.remove) {
                        part.remove = false;
                        if (mVideoRecordProgressView != null)
                            mVideoRecordProgressView.invalidate();
                    }
                }
            }
        }
        switch (view.getId()) {
            case R.id.matching_back:
                onBackPressed();
                break;
            case R.id.video_record_finish_iv:
                break;
            case R.id.switch_camera:

                break;
            case R.id.index_delete:

                break;
            case R.id.index_album:

                break;
            case R.id.custom_record_image_view:
                if(!isRecording) {
                    onStartRecording();
                }else{
                    onStopRecording();
                }
                break;
            case R.id.count_down_tv:

                break;
            case R.id.meet_mask:

                break;
            case R.id.video_filter:

                break;
        }
    }

    private void onStartRecording(){

    }

    private void onStopRecording() {

    }

    private void setBackAlpha(Button view ,int alpha) {
        if(alpha > 127){
            view.setClickable(true);
        }else{
            view.setClickable(false);
        }
        view.getBackground().setAlpha(alpha);
    }

    private void showOtherView() {
        if (mMediaObject != null && mMediaObject.getMedaParts().size() == 0) {
            mIndexDelete.setVisibility(View.GONE);
            mIndexAlbum.setVisibility(View.VISIBLE);
        } else {
            mIndexDelete.setVisibility(View.VISIBLE);
            mIndexAlbum.setVisibility(View.GONE);
        }
        mMeetMask.setVisibility(View.VISIBLE);
        mVideoFilter.setVisibility(View.VISIBLE);
        mCountDownTv.setVisibility(View.VISIBLE);
        mMatchingBack.setVisibility(View.VISIBLE);
        mCustomRecordImageView.setVisibility(View.VISIBLE);
    }
    private void hideOtherView() {
        mIndexAlbum.setVisibility(View.INVISIBLE);
        mIndexDelete.setVisibility(View.INVISIBLE);
        mMeetMask.setVisibility(View.INVISIBLE);
        mVideoFilter.setVisibility(View.INVISIBLE);
        mCountDownTv.setVisibility(View.INVISIBLE);
        mMatchingBack.setVisibility(View.INVISIBLE);
        mCustomRecordImageView.setVisibility(View.INVISIBLE);
    }

    public void alterStatus(){
        if(isRecording){
            mIndexAlbum.setVisibility(View.INVISIBLE);
            mIndexDelete.setVisibility(View.INVISIBLE);
            mMeetMask.setVisibility(View.INVISIBLE);
            mVideoFilter.setVisibility(View.INVISIBLE);
            mCountDownTv.setVisibility(View.INVISIBLE);
            mMatchingBack.setVisibility(View.INVISIBLE);
        }else{
            if (mMediaObject != null && mMediaObject.getMedaParts().size() == 0) {
                mIndexDelete.setVisibility(View.GONE);
                mIndexAlbum.setVisibility(View.VISIBLE);
            } else {
                mIndexDelete.setVisibility(View.VISIBLE);
                mIndexAlbum.setVisibility(View.GONE);
            }
            mMeetMask.setVisibility(View.VISIBLE);
            mVideoFilter.setVisibility(View.VISIBLE);
            mCountDownTv.setVisibility(View.VISIBLE);
            mMatchingBack.setVisibility(View.VISIBLE);
            mMeetCamera.setVisibility(View.VISIBLE);
            mVideoRecordFinishIv.setVisibility(View.VISIBLE);
            mVideoRecordProgressView.setVisibility(View.VISIBLE);
        }
    }

    private void hideAllView() {
        hideOtherView();
        mVideoRecordFinishIv.setVisibility(View.GONE);
        mVideoRecordProgressView.setVisibility(View.GONE);
        mMeetCamera.setVisibility(View.GONE);
    }


    @Override
    public boolean onTouch(View v, MotionEvent event) {

        return true;
    }

    @Override
    public void onFilterChange(final MagicFilterType type) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (type == MagicFilterType.NONE){
                    Toast.makeText(MainActivity.this,"当前没有设置滤镜--"+type,Toast.LENGTH_SHORT).show();
                }else {
                    Toast.makeText(MainActivity.this,"当前滤镜切换为--"+type,Toast.LENGTH_SHORT).show();
                }
            }
        });
    }
    private static class MyHandler extends Handler {

        private WeakReference<MainActivity> mVideoRecordActivity;

        public MyHandler(MainActivity videoRecordActivity) {
            mVideoRecordActivity = new WeakReference<>(videoRecordActivity);
        }

        @Override
        public void handleMessage(Message msg) {
            MainActivity activity = mVideoRecordActivity.get();
            if (activity != null) {
                switch (msg.what){
                    case DELAY_DETAL:
                        activity.mMediaObject.stopRecord(activity,activity.mMediaObject);
                        break;
                    case CHANGE_IMAGE:
                        switch (activity.mNum){
                            case 0:
                                activity.mCountTimeDownIv.setVisibility(View.VISIBLE);
                                activity.mCountTimeDownIv.setImageResource(R.drawable.bigicon_3);
                                activity.mMyHandler.sendEmptyMessageDelayed(CHANGE_IMAGE,1000);
                                break;
                            case 1:
                                activity.mCountTimeDownIv.setImageResource(R.drawable.bigicon_2);
                                activity.mMyHandler.sendEmptyMessageDelayed(CHANGE_IMAGE,1000);
                                break;
                            case 2:
                                activity.mCountTimeDownIv.setImageResource(R.drawable.bigicon_1);
                                activity.mMyHandler.sendEmptyMessageDelayed(CHANGE_IMAGE,1000);
                                break;
                            default:
                                activity.mMyHandler.removeCallbacks(null);
                                activity.mCountTimeDownIv.setVisibility(View.GONE);
                                activity.mVideoRecordProgressView.setVisibility(View.VISIBLE);
                                activity.mCustomRecordImageView.setVisibility(View.VISIBLE);
                                activity.mCustomRecordImageView.performClick();
                                //activity.mVideoRecordProgressView.setCountDownTime(activity.mRecordTimeInterval);
                                break;
                        }
                        if(activity.mNum >= 3){
                            activity.mNum = 0;
                        }else {
                            activity.mNum++;
                        }
                        break;
                    case OVER_CLICK:
                        activity.mCustomRecordImageView.performClick(); //定时结束
                        break;
                }
            }
        }
    }

    private static final String TAG = "MainActivity";

    String videoFileName;
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        switch (requestCode) {
            case StaticFinalValues.REQUEST_CODE_PICK_VIDEO:
                if (resultCode == RESULT_OK) {
                    //这一段用来判断视频时间的
                    try {
                        MediaPlayer player = new MediaPlayer();
                        player.setDataSource(videoFileName);
                        player.prepare();
                        int duration = player.getDuration();
                        player.release();
                        int s = duration / 1000;
                        int hour = s / 3600;
                        int minute = s % 3600 / 60;
                        int second = s % 60;
                        Log.e(TAG, "视频文件长度,分钟: " + minute + "视频有" + s + "秒");
                        if (s >= 120) {
                            Toast.makeText(this, "视频剪辑不能超过2分钟", Toast.LENGTH_LONG).show();
                            return;
                        } else if (s < 5) {
                            Toast.makeText(this, "视频剪辑不能少于5秒", Toast.LENGTH_LONG).show();
                            return;
                        }else{

                        }
                    } catch (Exception e) {
                        e.printStackTrace();
                    }


                }
                break;
        }
    }
}