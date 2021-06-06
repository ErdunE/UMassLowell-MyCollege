package com.example.mysmartcamera.mycamera.activity;

import android.app.Activity;
import android.content.Intent;
import android.text.TextUtils;
import android.widget.Toast;
import android.widget.VideoView;

import com.example.mysmartcamera.R;

import butterknife.BindView;

import static com.example.mysmartcamera.mycamera.utils.FileUtils.VIDEO_PATH;

public class PlayerActivity3 extends MyBasicActivity {


    @BindView(R.id.video_player_vv)
    VideoView mVideoPlayerVv;

    @Override
    protected int setLayoutId() {
        return R.layout.activity_video_view_player;
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        mVideoPlayerVv.resume();
        mVideoPlayerVv = null;
    }

    public void initView(){
        String stringExtra = getIntent().getStringExtra(VIDEO_PATH);
        if (TextUtils.isEmpty(stringExtra)) {
            Toast.makeText(this, "Text path error", Toast.LENGTH_SHORT).show();
        }else {
            mVideoPlayerVv.setVideoPath(stringExtra);
            mVideoPlayerVv.start();
        }
    }

}
