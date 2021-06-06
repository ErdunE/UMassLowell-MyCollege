package com.example.mysmartcamera.mycamera.activity;

import android.content.Intent;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.SystemClock;
import android.provider.MediaStore;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.WindowManager;
import android.widget.Chronometer;
import android.widget.ImageView;
import android.widget.MediaController;

import com.example.mysmartcamera.R;
import com.example.qoutelibyary.quote.videoEdit.view.PopTopTipWindow;
import com.example.mysmartcamera.mycamera.views.FullScreenView;

import java.io.File;

import butterknife.BindView;
import butterknife.OnClick;

public class VideoPlayerActivity extends AppCompatActivity {

    @BindView(R.id.picture_close)
    ImageView pictureClose;
    @BindView(R.id.meet_download)
    ImageView meetDownload;
    private String TAG = VideoPlayerActivity.class.getSimpleName();
    @BindView(R.id.video_view)
    public FullScreenView fullScreenVideoView;

    private String videoFilePath;

    @BindView(R.id.timer)
    public Chronometer timer;
    private PopTopTipWindow popTopTipWindow;


    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        setContentView(R.layout.activity_video_player);
        initData();
    }


    protected void initData() {


        videoFilePath = getIntent().getStringExtra("videoFilePath");

        fullScreenVideoView.setVideoPath(videoFilePath);


        fullScreenVideoView.setMediaController(new MediaController(this));



        fullScreenVideoView.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
            @Override
            public void onCompletion(MediaPlayer mp) {
                timer.setBase(SystemClock.elapsedRealtime());//计时器清零
                int xiaoshi = (int) ((SystemClock.elapsedRealtime() - timer.getBase()) / 1000 / 60);
                timer.setFormat("0"+ String.valueOf(xiaoshi)+":%s");
                timer.start();
                fullScreenVideoView.start();
            }
        });


        fullScreenVideoView.setOnErrorListener(new MediaPlayer.OnErrorListener() {

            @Override
            public boolean onError(MediaPlayer mp, int what, int extra) {

                return false;
            }
        });

    }


    @Override
    protected void onResume() {
        super.onResume();
        timer.setBase(SystemClock.elapsedRealtime());//计时器清零
        int xiaoshi = (int) ((SystemClock.elapsedRealtime() - timer.getBase()) / 1000 / 60);
        timer.setFormat("0"+ String.valueOf(xiaoshi)+":%s");
        timer.start();
        fullScreenVideoView.start();
    }

    private int floatViewState = 4;



    @Override
    protected void onPause() {
        super.onPause();
        fullScreenVideoView.pause();
    }

    private boolean hasDownload = false;

    private Handler handler = new Handler(Looper.getMainLooper());

    @OnClick({R.id.picture_close, R.id.meet_download})
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.picture_close:
                finish();
                break;
            case R.id.meet_download:
                downloadVideoFile();
                break;
        }
    }

    private void downloadVideoFile() {
        hasDownload = true;
        popTopTipWindow = new PopTopTipWindow(VideoPlayerActivity.this, "Preservation successful");
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                popTopTipWindow.dimss();
            }
        }, 2000);

        File outFile = new File(videoFilePath);
        try {
            MediaStore.Images.Media.insertImage(getContentResolver(), outFile.getAbsolutePath(), outFile.getName(), "");
        } catch (Exception e) {
        }

        sendBroadcast(new Intent(Intent.ACTION_MEDIA_SCANNER_SCAN_FILE, Uri.parse("file://" + outFile.getAbsolutePath())));
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (!hasDownload) {
            File outFile = new File(videoFilePath);
            if (!outFile.exists()) {
            } else {
                outFile.delete();
            }
        }
    }

}
