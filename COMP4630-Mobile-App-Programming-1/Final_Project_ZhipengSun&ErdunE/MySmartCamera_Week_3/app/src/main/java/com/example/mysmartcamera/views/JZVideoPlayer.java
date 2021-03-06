package com.example.mysmartcamera.views;

import android.content.Context;
import android.content.pm.ActivityInfo;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.os.Handler;
import android.provider.Settings;
import android.text.TextUtils;
import android.util.AttributeSet;
import android.util.Log;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.view.WindowManager;
import android.widget.AbsListView;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;

import com.example.mysmartcamera.R;
import com.example.mysmartcamera.objects.JZMediaManager;
import com.example.mysmartcamera.objects.JZVideoPlayerManager;
import com.example.mysmartcamera.utils.JZUtils;

import java.lang.reflect.Constructor;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;

public abstract class JZVideoPlayer extends FrameLayout implements View.OnClickListener, SeekBar.OnSeekBarChangeListener, View.OnTouchListener {

    public static final String TAG = "JiaoZiVideoPlayer";
    public static final int THRESHOLD = 80;
    public static final int FULL_SCREEN_NORMAL_DELAY = 3000;

    public static final int SCREEN_LAYOUT_NORMAL = 0;
    public static final int SCREEN_LAYOUT_LIST = 1;
    public static final int SCREEN_WINDOW_FULLSCREEN = 2;
    public static final int SCREEN_WINDOW_TINY = 3;

    public static final int CURRENT_STATE_NORMAL = 0;
    public static final int CURRENT_STATE_PREPARING = 1;
    public static final int CURRENT_STATE_PREPARING_CHANGING_URL = 2;
    public static final int CURRENT_STATE_PLAYING = 3;
    public static final int CURRENT_STATE_PAUSE = 5;
    public static final int CURRENT_STATE_AUTO_COMPLETE = 6;
    public static final int CURRENT_STATE_ERROR = 7;

    public static final String URL_KEY_DEFAULT = "URL_KEY_DEFAULT";
    public static boolean ACTION_BAR_EXIST = true;
    public static boolean TOOL_BAR_EXIST = true;
    public static int FULLSCREEN_ORIENTATION = ActivityInfo.SCREEN_ORIENTATION_SENSOR;
    public static int NORMAL_ORIENTATION = ActivityInfo.SCREEN_ORIENTATION_PORTRAIT;
    public static boolean SAVE_PROGRESS = true;
    public static boolean WIFI_TIP_DIALOG_SHOWED = false;
    public static long CLICK_QUIT_FULLSCREEN_TIME = 0;
    public static long lastAutoFullscreenTime = 0;
    public static AudioManager.OnAudioFocusChangeListener onAudioFocusChangeListener = new AudioManager.OnAudioFocusChangeListener() {//???????????????class??????????????????????????????????????????????????????
        @Override
        public void onAudioFocusChange(int focusChange) {
            switch (focusChange) {
                case AudioManager.AUDIOFOCUS_GAIN:
                    break;
                case AudioManager.AUDIOFOCUS_LOSS:
                    releaseAllVideos();
                    Log.e("Atest", "releaseAllVideos onAudioFocusChange: JZVideoPlayer");
                    Log.e(TAG, "AUDIOFOCUS_LOSS [" + this.hashCode() + "]");
                    break;
                case AudioManager.AUDIOFOCUS_LOSS_TRANSIENT:

                    break;
                case AudioManager.AUDIOFOCUS_LOSS_TRANSIENT_CAN_DUCK:
                    break;
            }
        }
    };

    protected static Timer UPDATE_PROGRESS_TIMER;
    public int currentState = -1;
    public int currentScreen = -1;
    public boolean loop = true;//??????????????????
    public Map<String, String> headData;
    //    public String url = "";
    public Object[] objects = null;
    public int seekToInAdvance = 0;
    public ImageView startButton;
    public SeekBar progressBar;
    public ImageView fullscreenButton;
    public TextView currentTimeTextView, totalTimeTextView;
    public ViewGroup textureViewContainer;
    public ViewGroup topContainer, bottomContainer;
    public int widthRatio = 0;
    public int heightRatio = 0;
    protected boolean isVideoRendingStart = false;
    protected int mScreenWidth;
    protected int mScreenHeight;
    protected AudioManager mAudioManager;
    protected Handler mHandler;
    protected ProgressTimerTask mProgressTimerTask;
    protected boolean mTouchingProgressBar;
    protected float mDownX;
    protected float mDownY;
    protected boolean mChangeVolume;
    protected boolean mChangePosition;
    protected boolean mChangeBrightness;
    protected int mGestureDownPosition;
    protected int mGestureDownVolume;
    protected float mGestureDownBrightness;
    protected int mSeekTimePosition;
    public LinkedHashMap urlMap;
    public int currentUrlMapIndex = 0;
    public int positionInList = -1;

    public JZVideoPlayer(Context context) {
        super(context);
        init(context);
    }

    public JZVideoPlayer(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    public static void releaseAllVideos() {
        if ((System.currentTimeMillis() - CLICK_QUIT_FULLSCREEN_TIME) > FULL_SCREEN_NORMAL_DELAY) {

        }
    }

    public static void startFullscreen(Context context, Class _class, String url, Object... objects) {
        LinkedHashMap map = new LinkedHashMap();
        map.put(URL_KEY_DEFAULT, url);
        startFullscreen(context, _class, map, 0, objects);
    }

    public static void startFullscreen(Context context, Class _class, LinkedHashMap urlMap, int defaultUrlMapIndex, Object... objects) {
        hideSupportActionBar(context);
        JZUtils.setRequestedOrientation(context, FULLSCREEN_ORIENTATION);
        ViewGroup vp = (ViewGroup) (JZUtils.scanForActivity(context))//.getWindow().getDecorView();
                .findViewById(Window.ID_ANDROID_CONTENT);
        View old = vp.findViewById(R.id.jz_fullscreen_id);
        if (old != null) {
            vp.removeView(old);
        }
        try {
            Constructor<JZVideoPlayer> constructor = _class.getConstructor(Context.class);
            final JZVideoPlayer jzVideoPlayer = constructor.newInstance(context);
            jzVideoPlayer.setId(R.id.jz_fullscreen_id);
            LayoutParams lp = new LayoutParams(
                    ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
            vp.addView(jzVideoPlayer, lp);
//            final Animation ra = AnimationUtils.loadAnimation(context, R.anim.start_fullscreen);
//            jzVideoPlayer.setAnimation(ra);
            jzVideoPlayer.setUp(urlMap, defaultUrlMapIndex, JZVideoPlayerStandard.SCREEN_WINDOW_FULLSCREEN, objects);
            CLICK_QUIT_FULLSCREEN_TIME = System.currentTimeMillis();
            jzVideoPlayer.startButton.performClick();
        } catch (InstantiationException e) {
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public String getCurrentUrl() {
        return JZUtils.getCurrentUrlFromMap(urlMap, currentUrlMapIndex);
    }

    public static boolean backPress() {
        Log.e(TAG, "backPress");
        if ((System.currentTimeMillis() - CLICK_QUIT_FULLSCREEN_TIME) < FULL_SCREEN_NORMAL_DELAY)
            return false;
        if (JZVideoPlayerManager.getSecondFloor() != null) {
            CLICK_QUIT_FULLSCREEN_TIME = System.currentTimeMillis();
            if (JZVideoPlayerManager.getFirstFloor().getCurrentUrl().equals(JZMediaManager.CURRENT_PLAYING_URL)) {
                JZVideoPlayer jzVideoPlayer = JZVideoPlayerManager.getSecondFloor();

                JZVideoPlayerManager.getFirstFloor().playOnThisJzvd();
            } else {
                //???????????????????????????
                JZVideoPlayerManager.getCurrentJzvd().currentState = CURRENT_STATE_NORMAL;
                JZVideoPlayerManager.getFirstFloor().clearFloatScreen();
                JZMediaManager.instance().releaseMediaPlayer();
                JZVideoPlayerManager.setFirstFloor(null);
            }
            return true;
        } else if (JZVideoPlayerManager.getFirstFloor() != null &&
                (JZVideoPlayerManager.getFirstFloor().currentScreen == SCREEN_WINDOW_FULLSCREEN ||
                        JZVideoPlayerManager.getFirstFloor().currentScreen == SCREEN_WINDOW_TINY)) {//?????????????????????????????????????????????????????????????????????????????????
            CLICK_QUIT_FULLSCREEN_TIME = System.currentTimeMillis();
            //???????????????????????????
            JZVideoPlayerManager.getCurrentJzvd().currentState = CURRENT_STATE_NORMAL;
            JZVideoPlayerManager.getFirstFloor().clearFloatScreen();
            JZMediaManager.instance().releaseMediaPlayer();
            JZVideoPlayerManager.setFirstFloor(null);
            return true;
        }
        return false;
    }

    public static void showSupportActionBar(Context context) {
        if (ACTION_BAR_EXIST && JZUtils.getAppCompActivity(context) != null) {
            ActionBar ab = JZUtils.getAppCompActivity(context).getSupportActionBar();
            if (ab != null) {
                ab.setShowHideAnimationEnabled(false);
                ab.show();
            }
        }
        if (TOOL_BAR_EXIST) {
            JZUtils.getWindow(context).clearFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
        }
    }

    public static void hideSupportActionBar(Context context) {
        if (ACTION_BAR_EXIST && JZUtils.getAppCompActivity(context) != null) {
            ActionBar ab = JZUtils.getAppCompActivity(context).getSupportActionBar();
            if (ab != null) {
                ab.setShowHideAnimationEnabled(false);
                ab.hide();
            }
        }
        if (TOOL_BAR_EXIST) {
            JZUtils.getWindow(context).setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                    WindowManager.LayoutParams.FLAG_FULLSCREEN);
        }
    }

    public static void clearSavedProgress(Context context, String url) {
        JZUtils.clearSavedProgress(context, url);
    }



    public static void goOnPlayOnResume() {
        if (JZVideoPlayerManager.getCurrentJzvd() != null) {
            JZVideoPlayer jzvd = JZVideoPlayerManager.getCurrentJzvd();
            if (jzvd.currentState == JZVideoPlayer.CURRENT_STATE_PAUSE) {
                jzvd.onStatePlaying();
                JZMediaManager.instance().mediaPlayer.start();
            }
        }
    }

    public static void goOnPlayOnPause() {
        if (JZVideoPlayerManager.getCurrentJzvd() != null) {
            JZVideoPlayer jzvd = JZVideoPlayerManager.getCurrentJzvd();
            if (jzvd.currentState == JZVideoPlayer.CURRENT_STATE_AUTO_COMPLETE ||
                    jzvd.currentState == JZVideoPlayer.CURRENT_STATE_NORMAL) {
//                JZVideoPlayer.releaseAllVideos();
            } else {
                jzvd.onStatePause();
                JZMediaManager.instance().mediaPlayer.pause();
            }
        }
    }

    public abstract int getLayoutId();

    public void init(Context context) {
        View.inflate(context, getLayoutId(), this);
        startButton = (ImageView) findViewById(R.id.start);


//        startButton.setOnClickListener(this);
        fullscreenButton.setOnClickListener(this);
        progressBar.setOnSeekBarChangeListener(this);
        bottomContainer.setOnClickListener(this);
        textureViewContainer.setOnClickListener(this);
        textureViewContainer.setOnTouchListener(this);

        mScreenWidth = getContext().getResources().getDisplayMetrics().widthPixels;
        mScreenHeight = getContext().getResources().getDisplayMetrics().heightPixels;
        mAudioManager = (AudioManager) getContext().getSystemService(Context.AUDIO_SERVICE);
        mHandler = new Handler();

        try {
            if (isCurrentPlay()) {
                NORMAL_ORIENTATION = ((AppCompatActivity) context).getRequestedOrientation();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void setUp(String url, int screen, Object... objects) {
        LinkedHashMap map = new LinkedHashMap();
        map.put(URL_KEY_DEFAULT, url);
        setUp(map, 0, screen, objects);
    }

    public void setUp(LinkedHashMap urlMap, int defaultUrlMapIndex, int screen, Object... objects) {
        if (this.urlMap != null && !TextUtils.isEmpty(JZUtils.getCurrentUrlFromMap(urlMap, currentUrlMapIndex)) &&
                TextUtils.equals(JZUtils.getCurrentUrlFromMap(this.urlMap, currentUrlMapIndex), JZUtils.getCurrentUrlFromMap(urlMap, currentUrlMapIndex))) {
            return;
        }
        //setUp???????????????
        if (isCurrentJZVD() && urlMap.containsValue(JZMediaManager.CURRENT_PLAYING_URL)) {//????????????
            //???????????????????????? -- ???????????????releaseAllVideos?????? ?????????????????????
            int position = 0;
            try {
                position = JZMediaManager.instance().mediaPlayer.getCurrentPosition();
            } catch (IllegalStateException e) {
                e.printStackTrace();
            }
            if (position != 0) {
                JZUtils.saveProgress(getContext(), JZMediaManager.CURRENT_PLAYING_URL, position);
            }
            JZMediaManager.instance().releaseMediaPlayer();
        } else if (isCurrentJZVD() && !urlMap.containsValue(JZMediaManager.CURRENT_PLAYING_URL)) {//????????????
            Log.e("jzvd", "setUp: ????????????");//??????releaseAllVideos?????????????????????
//            JZVideoPlayer.releaseAllVideos();
            startWindowTiny();
        } else if (!isCurrentJZVD() && urlMap.containsValue(JZMediaManager.CURRENT_PLAYING_URL)) {//???????????? ????????????????????????????????????
            Log.e("jzvd", "setUp: ???????????? ????????????");//????????????????????????????????????????????????????????????
            if (JZVideoPlayerManager.getCurrentJzvd() != null &&
                    JZVideoPlayerManager.getCurrentJzvd().currentScreen == JZVideoPlayer.SCREEN_WINDOW_TINY) {
                //????????????????????????????????????????????????????????????
                tmp_test_back = true;
                Log.e("jzvd", "setUp: tmp_test_back=true");
            }
        } else if (!isCurrentJZVD() && !urlMap.containsValue(JZMediaManager.CURRENT_PLAYING_URL)) {//?????????

        }
        this.urlMap = urlMap;
        this.currentUrlMapIndex = defaultUrlMapIndex;
        this.currentScreen = screen;
        this.objects = objects;
        this.headData = null;
        isVideoRendingStart = false;
        onStateNormal();

    }

    boolean tmp_test_back = false;

    @Override
    public void onClick(View v) {
        int i = v.getId();
        if (i == R.id.start) {
            Log.e(TAG, "onClick start [" + this.hashCode() + "] ");
            if (urlMap == null || TextUtils.isEmpty(JZUtils.getCurrentUrlFromMap(urlMap, currentUrlMapIndex))) {
                Toast.makeText(getContext(), "No url", Toast.LENGTH_LONG).show();
                return;
            }
            if (currentState == CURRENT_STATE_NORMAL || currentState == CURRENT_STATE_ERROR) {
                if (!JZUtils.getCurrentUrlFromMap(urlMap, currentUrlMapIndex).startsWith("file") && !
                        JZUtils.getCurrentUrlFromMap(urlMap, currentUrlMapIndex).startsWith("/") &&
                        !JZUtils.isWifiConnected(getContext()) && !WIFI_TIP_DIALOG_SHOWED) {

                    return;
                }
                startVideo();

            } else if (currentState == CURRENT_STATE_PLAYING) {

                Log.e(TAG, "pauseVideo [" + this.hashCode() + "] ");
                JZMediaManager.instance().mediaPlayer.pause();
                onStatePause();
            } else if (currentState == CURRENT_STATE_PAUSE) {

                JZMediaManager.instance().mediaPlayer.start();
                onStatePlaying();
            } else if (currentState == CURRENT_STATE_AUTO_COMPLETE) {

                startVideo();
            }
        }
    }
    public void handlerOnPause(){}
    public void handlerOnStart(){};
    @Override
    public boolean onTouch(View v, MotionEvent event) {
        float x = event.getX();
        float y = event.getY();
        int id = v.getId();
        return false;
    }
    public boolean isNeedVoice = false;
    public void setNeedVoice(boolean isNeed){
        isNeedVoice = isNeed;
    }
    public void setNeedLoop(boolean l){//????????????????????????
        loop = l;
    }
    public void startVideo() {
        JZMediaManager.instance().setIsNeedVoice(isNeedVoice);
        JZVideoPlayerManager.completeAll();
        Log.e(TAG, "startVideo [" + this.hashCode() + "] ");
        initTextureView();
        addTextureView();
        AudioManager mAudioManager = (AudioManager) getContext().getSystemService(Context.AUDIO_SERVICE);
        mAudioManager.requestAudioFocus(onAudioFocusChangeListener, AudioManager.STREAM_MUSIC, AudioManager.AUDIOFOCUS_GAIN_TRANSIENT);
        JZUtils.scanForActivity(getContext()).getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        JZMediaManager.CURRENT_PLAYING_URL = JZUtils.getCurrentUrlFromMap(urlMap, currentUrlMapIndex);
        JZMediaManager.CURRENT_PLING_LOOP = loop;
        JZMediaManager.MAP_HEADER_DATA = headData;
        onStatePreparing();
        JZVideoPlayerManager.setFirstFloor(this);
        JZMediaManager.instance().positionInList = positionInList;
    }


    public void onPrepared() {
        Log.e(TAG, "onPrepared " + " [" + this.hashCode() + "] ");
        if (JZUtils.getCurrentUrlFromMap(urlMap, currentUrlMapIndex).toLowerCase().contains("mp3")) {
            onVideoRendingStart();
        }
    }

    public void onVideoRendingStart() {
        Log.e(TAG, "onVideoRendingStart " + " [" + this.hashCode() + "] ");
        isVideoRendingStart = true;
        if (currentState != CURRENT_STATE_PREPARING && currentState != CURRENT_STATE_PREPARING_CHANGING_URL)
            return;
        if (seekToInAdvance != 0) {
            JZMediaManager.instance().mediaPlayer.seekTo(seekToInAdvance);
            seekToInAdvance = 0;
        } else {
            try {
                int position = JZUtils.getSavedProgress(getContext(), JZUtils.getCurrentUrlFromMap(urlMap, currentUrlMapIndex));
                if (position != 0) {
                    JZMediaManager.instance().mediaPlayer.seekTo(position);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        startProgressTimer();
        onStatePlaying();
    }

    public void setState(int state) {
        setState(state, 0, 0);
    }

    public void setState(int state, int urlMapIndex, int seekToInAdvance) {
        switch (state) {
            case CURRENT_STATE_NORMAL:
                onStateNormal();
                break;
            case CURRENT_STATE_PREPARING:
                onStatePreparing();
                break;
            case CURRENT_STATE_PREPARING_CHANGING_URL:
                onStatePreparingChangingUrl(urlMapIndex, seekToInAdvance);
                break;
            case CURRENT_STATE_PLAYING:
                onStatePlaying();
                break;
            case CURRENT_STATE_PAUSE:
                onStatePause();
                break;
            case CURRENT_STATE_ERROR:
                onStateError();
                break;
            case CURRENT_STATE_AUTO_COMPLETE:
                onStateAutoComplete();
                break;
        }
    }

    public void onStateNormal() {
        Log.e(TAG, "onStateNormal " + " [" + this.hashCode() + "] ");
        currentState = CURRENT_STATE_NORMAL;
        cancelProgressTimer();
    }

    public void onStatePreparing() {
        Log.e(TAG, "onStatePreparing " + " [" + this.hashCode() + "] ");
        currentState = CURRENT_STATE_PREPARING;
        resetProgressAndTime();
    }

    public void onStatePreparingChangingUrl(int urlMapIndex, int seekToInAdvance) {
        currentState = CURRENT_STATE_PREPARING_CHANGING_URL;
        this.currentUrlMapIndex = urlMapIndex;
        this.seekToInAdvance = seekToInAdvance;
        JZMediaManager.CURRENT_PLAYING_URL = JZUtils.getCurrentUrlFromMap(urlMap, this.currentUrlMapIndex);
        JZMediaManager.CURRENT_PLING_LOOP = this.loop;
        JZMediaManager.MAP_HEADER_DATA = this.headData;
        JZMediaManager.instance().prepare();
    }

    public void onStatePlaying() {
        Log.e(TAG, "onStatePlaying " + " [" + this.hashCode() + "] ");
        currentState = CURRENT_STATE_PLAYING;
        startProgressTimer();
    }

    public void onStatePause() {
        Log.e(TAG, "onStatePause " + " [" + this.hashCode() + "] ");
        currentState = CURRENT_STATE_PAUSE;
        startProgressTimer();
    }

    public void onStateError() {
        Log.e(TAG, "onStateError " + " [" + this.hashCode() + "] ");
        currentState = CURRENT_STATE_ERROR;
        cancelProgressTimer();
    }

    public void onStateAutoComplete() {
        Log.e(TAG, "onStateAutoComplete " + " [" + this.hashCode() + "] ");
        currentState = CURRENT_STATE_AUTO_COMPLETE;
        cancelProgressTimer();
        progressBar.setProgress(100);
        currentTimeTextView.setText(totalTimeTextView.getText());
    }

    public void onInfo(int what, int extra) {
        Log.e(TAG, "onInfo what - " + what + " extra - " + extra);
        if (what == MediaPlayer.MEDIA_INFO_VIDEO_RENDERING_START) {
            onVideoRendingStart();
        }
    }

    public void onError(int what, int extra) {
        Log.e(TAG, "onError " + what + " - " + extra + " [" + this.hashCode() + "] ");
        if (what != 38 && what != -38 && extra != -38) {
            onStateError();
            if (isCurrentPlay()) {
                JZMediaManager.instance().releaseMediaPlayer();
            }
        }
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        if (currentScreen == SCREEN_WINDOW_FULLSCREEN || currentScreen == SCREEN_WINDOW_TINY) {
            super.onMeasure(widthMeasureSpec, heightMeasureSpec);
            return;
        }
        if (widthRatio != 0 && heightRatio != 0) {
            int specWidth = MeasureSpec.getSize(widthMeasureSpec);
            int specHeight = (int) ((specWidth * (float) heightRatio) / widthRatio);
            setMeasuredDimension(specWidth, specHeight);

            int childWidthMeasureSpec = MeasureSpec.makeMeasureSpec(specWidth, MeasureSpec.EXACTLY);
            int childHeightMeasureSpec = MeasureSpec.makeMeasureSpec(specHeight, MeasureSpec.EXACTLY);
            getChildAt(0).measure(childWidthMeasureSpec, childHeightMeasureSpec);
        } else {
            super.onMeasure(widthMeasureSpec, heightMeasureSpec);
        }

    }

    public void onAutoCompletion() {
        //?????????????????????????????????video?????????????????????????????????
        Runtime.getRuntime().gc();
        Log.e(TAG, "onAutoCompletion " + " [" + this.hashCode() + "] ");

        dismissVolumeDialog();
        dismissProgressDialog();
        dismissBrightnessDialog();
        cancelProgressTimer();
        onStateAutoComplete();

        if (currentScreen == SCREEN_WINDOW_FULLSCREEN || currentScreen == SCREEN_WINDOW_TINY) {
            backPress();
        }
        JZMediaManager.instance().mediaPlayer.release();
        JZUtils.saveProgress(getContext(), JZUtils.getCurrentUrlFromMap(urlMap, currentUrlMapIndex), 0);
    }

    public void onCompletion() {
        Log.e(TAG, "onCompletion " + " [" + this.hashCode() + "] ");
        //save position
        if (currentState == CURRENT_STATE_PLAYING || currentState == CURRENT_STATE_PAUSE) {
            int position = getCurrentPositionWhenPlaying();
            JZUtils.saveProgress(getContext(), JZUtils.getCurrentUrlFromMap(urlMap, currentUrlMapIndex), position);
        }
        cancelProgressTimer();
        onStateNormal();
        // ??????????????????

        JZMediaManager.instance().currentVideoWidth = 0;
        JZMediaManager.instance().currentVideoHeight = 0;

        AudioManager mAudioManager = (AudioManager) getContext().getSystemService(Context.AUDIO_SERVICE);
        mAudioManager.abandonAudioFocus(onAudioFocusChangeListener);
        JZUtils.scanForActivity(getContext()).getWindow().clearFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        clearFullscreenLayout();
        JZUtils.setRequestedOrientation(getContext(), NORMAL_ORIENTATION);

        JZMediaManager.savedSurfaceTexture = null;
        isVideoRendingStart = false;
    }

    public void release() {
        if (JZUtils.getCurrentUrlFromMap(urlMap, currentUrlMapIndex).equals(JZMediaManager.CURRENT_PLAYING_URL) &&
                (System.currentTimeMillis() - CLICK_QUIT_FULLSCREEN_TIME) > FULL_SCREEN_NORMAL_DELAY) {
            //??????????????????????????????backPress()
            if (JZVideoPlayerManager.getSecondFloor() != null &&
                    JZVideoPlayerManager.getSecondFloor().currentScreen == SCREEN_WINDOW_FULLSCREEN) {//????????????
            } else if (JZVideoPlayerManager.getSecondFloor() == null && JZVideoPlayerManager.getFirstFloor() != null &&
                    JZVideoPlayerManager.getFirstFloor().currentScreen == SCREEN_WINDOW_FULLSCREEN) {//????????????
            } else {
                Log.e(TAG, "release [" + this.hashCode() + "]");
                releaseAllVideos();
                Log.e("Atest", "release:  JZVideoPlayer ==== releaseAllVideo");
            }
        }
    }

    public void initTextureView() {
        removeTextureView();

    }

    public void addTextureView() {
        Log.e(TAG, "addTextureView [" + this.hashCode() + "] ");
        LayoutParams layoutParams =
                new LayoutParams(
                        ViewGroup.LayoutParams.MATCH_PARENT,
                        ViewGroup.LayoutParams.MATCH_PARENT,
                        Gravity.CENTER);

    }

    public void removeTextureView() {
        JZMediaManager.savedSurfaceTexture = null;

    }

    public void clearFullscreenLayout() {
        ViewGroup vp = (ViewGroup) (JZUtils.scanForActivity(getContext()))//.getWindow().getDecorView();
                .findViewById(Window.ID_ANDROID_CONTENT);
        View oldF = vp.findViewById(R.id.jz_fullscreen_id);
        View oldT = vp.findViewById(R.id.jz_tiny_id);
        if (oldF != null) {
            vp.removeView(oldF);
        }
        if (oldT != null) {
            vp.removeView(oldT);
        }
        showSupportActionBar(getContext());
    }

    public void clearFloatScreen() {
        JZUtils.setRequestedOrientation(getContext(), NORMAL_ORIENTATION);
        showSupportActionBar(getContext());
        JZVideoPlayer currJzvd = JZVideoPlayerManager.getCurrentJzvd();

        ViewGroup vp = (ViewGroup) (JZUtils.scanForActivity(getContext()))//.getWindow().getDecorView();
                .findViewById(Window.ID_ANDROID_CONTENT);
        vp.removeView(currJzvd);
        JZVideoPlayerManager.setSecondFloor(null);
    }

    public void onVideoSizeChanged() {

    }

    public void startProgressTimer() {
        cancelProgressTimer();
        UPDATE_PROGRESS_TIMER = new Timer();
        mProgressTimerTask = new ProgressTimerTask();
        UPDATE_PROGRESS_TIMER.schedule(mProgressTimerTask, 0, 300);
    }

    public void cancelProgressTimer() {
        if (UPDATE_PROGRESS_TIMER != null) {
            UPDATE_PROGRESS_TIMER.cancel();
        }
        if (mProgressTimerTask != null) {
            mProgressTimerTask.cancel();
        }
    }

    public void setProgressAndText(int progress, int position, int duration) {
        if (!mTouchingProgressBar) {
            if (progress != 0) progressBar.setProgress(progress);
        }
        if (position != 0) currentTimeTextView.setText(JZUtils.stringForTime(position));
        totalTimeTextView.setText(JZUtils.stringForTime(duration));
    }

    public void setBufferProgress(int bufferProgress) {
        if (bufferProgress != 0) progressBar.setSecondaryProgress(bufferProgress);
    }

    public void resetProgressAndTime() {
        progressBar.setProgress(0);
        progressBar.setSecondaryProgress(0);
        currentTimeTextView.setText(JZUtils.stringForTime(0));
        totalTimeTextView.setText(JZUtils.stringForTime(0));
    }

    public int getCurrentPositionWhenPlaying() {
        int position = 0;
        if (JZMediaManager.instance().mediaPlayer == null)
            return position;//???????????????????????????????????????????????????????????????????????????????????????
        if (currentState == CURRENT_STATE_PLAYING ||
                currentState == CURRENT_STATE_PAUSE) {
            try {
                position = JZMediaManager.instance().mediaPlayer.getCurrentPosition();
            } catch (IllegalStateException e) {
                e.printStackTrace();
                return position;
            }
        }
        return position;
    }

    public int getDuration() {
        int duration = 0;
        if (JZMediaManager.instance().mediaPlayer == null) return duration;
        try {
            duration = JZMediaManager.instance().mediaPlayer.getDuration();
        } catch (IllegalStateException e) {
            e.printStackTrace();
            return duration;
        }
        return duration;
    }

    @Override
    public void onStartTrackingTouch(SeekBar seekBar) {
        Log.e(TAG, "bottomProgress onStartTrackingTouch [" + this.hashCode() + "] ");
        cancelProgressTimer();
       /* ViewParent vpdown = getParent();
        while (vpdown != null) {
            vpdown.requestDisallowInterceptTouchEvent(true);
            vpdown = vpdown.getParent();
        }*/
    }

    @Override
    public void onStopTrackingTouch(SeekBar seekBar) {
        Log.e(TAG, "bottomProgress onStopTrackingTouch [" + this.hashCode() + "] ");

        startProgressTimer();
      /*  ViewParent vpup = getParent();
        while (vpup != null) {
            vpup.requestDisallowInterceptTouchEvent(false);
            vpup = vpup.getParent();
        }*/
        if (currentState != CURRENT_STATE_PLAYING &&
                currentState != CURRENT_STATE_PAUSE) return;
        int time = seekBar.getProgress() * getDuration() / 100;
        JZMediaManager.instance().mediaPlayer.seekTo(time);
        Log.e(TAG, "seekTo " + time + " [" + this.hashCode() + "] ");
    }

    @Override
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
    }

    public void startWindowFullscreen() {
        Log.e(TAG, "startWindowFullscreen " + " [" + this.hashCode() + "] ");
        hideSupportActionBar(getContext());
        JZUtils.setRequestedOrientation(getContext(), FULLSCREEN_ORIENTATION);

        ViewGroup vp = (ViewGroup) (JZUtils.scanForActivity(getContext()))//.getWindow().getDecorView();
                .findViewById(Window.ID_ANDROID_CONTENT);
        View old = vp.findViewById(R.id.jz_fullscreen_id);
        if (old != null) {
            vp.removeView(old);
        }

        try {
            Constructor<JZVideoPlayer> constructor = (Constructor<JZVideoPlayer>) JZVideoPlayer.this.getClass().getConstructor(Context.class);
            JZVideoPlayer jzVideoPlayer = constructor.newInstance(getContext());
            jzVideoPlayer.setId(R.id.jz_fullscreen_id);
            LayoutParams lp = new LayoutParams(
                    ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
            vp.addView(jzVideoPlayer, lp);
            jzVideoPlayer.setUp(urlMap, currentUrlMapIndex, JZVideoPlayerStandard.SCREEN_WINDOW_FULLSCREEN, objects);
            jzVideoPlayer.setState(currentState);
            jzVideoPlayer.addTextureView();
            JZVideoPlayerManager.setSecondFloor(jzVideoPlayer);
//            final Animation ra = AnimationUtils.loadAnimation(getContext(), R.anim.start_fullscreen);
//            jzVideoPlayer.setAnimation(ra);
            onStateNormal();
            jzVideoPlayer.progressBar.setSecondaryProgress(progressBar.getSecondaryProgress());
            jzVideoPlayer.startProgressTimer();
            CLICK_QUIT_FULLSCREEN_TIME = System.currentTimeMillis();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void startWindowTiny() {
        Log.e(TAG, "startWindowTiny " + " [" + this.hashCode() + "] ");

        if (currentState == CURRENT_STATE_NORMAL || currentState == CURRENT_STATE_ERROR) return;
        ViewGroup vp = (ViewGroup) (JZUtils.scanForActivity(getContext()))//.getWindow().getDecorView();
                .findViewById(Window.ID_ANDROID_CONTENT);
        View old = vp.findViewById(R.id.jz_tiny_id);
        if (old != null) {
            vp.removeView(old);
        }

        new Handler().post(new Runnable() {
            @Override
            public void run() {

            }
        });

        try {
            Constructor<JZVideoPlayer> constructor = (Constructor<JZVideoPlayer>) JZVideoPlayer.this.getClass().getConstructor(Context.class);
            JZVideoPlayer jzVideoPlayer = constructor.newInstance(getContext());
            jzVideoPlayer.setId(R.id.jz_tiny_id);
            LayoutParams lp = new LayoutParams(400, 400);
            lp.gravity = Gravity.RIGHT | Gravity.BOTTOM;
            vp.addView(jzVideoPlayer, lp);
            jzVideoPlayer.setUp(urlMap, currentUrlMapIndex, JZVideoPlayerStandard.SCREEN_WINDOW_TINY, objects);
            jzVideoPlayer.setState(currentState);
            jzVideoPlayer.addTextureView();
            JZVideoPlayerManager.setSecondFloor(jzVideoPlayer);
            onStateNormal();
        } catch (InstantiationException e) {
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    //isCurrentPlay and isCurrenPlayUrl should be two logic methods,isCurrentPlay is for different jzvd with same
    //url when fullscreen or tiny screen. isCurrenPlayUrl is to find where is myself when back from tiny screen.
    //Sometimes they are overlap.
    public boolean isCurrentPlay() {//????????????????????????????????????????????????
        if (urlMap != null) {
            return isCurrentJZVD()
                    && urlMap.containsValue(JZMediaManager.CURRENT_PLAYING_URL);//?????????????????????url???????????????????????????????????????????????????
        }else{
            return false;
        }
    }

    public boolean isCurrentJZVD() {//?????????????????????
        return JZVideoPlayerManager.getCurrentJzvd() != null
                && JZVideoPlayerManager.getCurrentJzvd() == this;
    }

    //??????????????????????????????
    public void playOnThisJzvd() {
        Log.e(TAG, "playOnThisJzvd " + " [" + this.hashCode() + "] ");
        //1.????????????????????????jzvd
        currentState = JZVideoPlayerManager.getSecondFloor().currentState;
        currentUrlMapIndex = JZVideoPlayerManager.getSecondFloor().currentUrlMapIndex;
        clearFloatScreen();
        //2.??????jzvd?????????
        Log.e("jzvd", "jklf: " + currentState);
        setState(currentState);
        addTextureView();
    }

    //???????????????????????????????????????
    public void autoFullscreen(float x) {
        if (isCurrentPlay()
                && currentState == CURRENT_STATE_PLAYING
                && currentScreen != SCREEN_WINDOW_FULLSCREEN
                && currentScreen != SCREEN_WINDOW_TINY) {
            if (x > 0) {
                JZUtils.setRequestedOrientation(getContext(), ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
            } else {
                JZUtils.setRequestedOrientation(getContext(), ActivityInfo.SCREEN_ORIENTATION_REVERSE_LANDSCAPE);
            }

            startWindowFullscreen();
        }
    }

    public void autoQuitFullscreen() {
        if ((System.currentTimeMillis() - lastAutoFullscreenTime) > 2000
                && isCurrentPlay()
                && currentState == CURRENT_STATE_PLAYING
                && currentScreen == SCREEN_WINDOW_FULLSCREEN) {
            lastAutoFullscreenTime = System.currentTimeMillis();
            backPress();
        }
    }

    public void onEvent(int type) {

    }

    public static void onScrollAutoTiny(AbsListView view, int firstVisibleItem, int visibleItemCount, int totalItemCount) {
        int lastVisibleItem = firstVisibleItem + visibleItemCount;
        int currentPlayPosition = JZMediaManager.instance().positionInList;
        if (currentPlayPosition >= 0) {
            if ((currentPlayPosition < firstVisibleItem || currentPlayPosition > (lastVisibleItem - 1))) {
                //???????????? ??????release ??????????????????
                //JZVideoPlayer.releaseAllVideos();
                if (JZVideoPlayerManager.getCurrentJzvd() != null &&
                        JZVideoPlayerManager.getCurrentJzvd().currentScreen != JZVideoPlayer.SCREEN_WINDOW_TINY) {
                    Log.e("jzvd", "onScroll: ????????????");
                    JZVideoPlayerManager.getCurrentJzvd().startWindowTiny();
                }
            } else {
                //???????????????????????????????????????????????????????????????
                if (JZVideoPlayerManager.getCurrentJzvd() != null &&
                        JZVideoPlayerManager.getCurrentJzvd().currentScreen == JZVideoPlayer.SCREEN_WINDOW_TINY) {
                    Log.e("jzvd", "onScroll: ????????????");
                    JZVideoPlayer.backPress();
                }
            }
        }
    }
    public static void onScrollReleaseAllVideos(int firstVisibleItem,int lastVisibleItem,int currentscreen){
        if(currentscreen == JZVideoPlayer.SCREEN_WINDOW_FULLSCREEN){
            return;
        }
        int currentPlayPosition = JZMediaManager.instance().positionInList;
        if(currentPlayPosition >= 0 ){
            if(currentPlayPosition <= firstVisibleItem || currentPlayPosition >= lastVisibleItem){
                JZVideoPlayer.releaseAllVideos();
                Log.e("Atest", "onScrollReleaseAllVideos:  JZVideoPlayer  ==== releaseAllVideo");
            }
        }
    }
    public static void onScrollReleaseAllVideos(View view, int firstVisibleItem, int visibleItemCount, int totalItemCount) {
        int lastVisibleItem = firstVisibleItem + visibleItemCount;
        int currentPlayPosition = JZMediaManager.instance().positionInList;
        if (currentPlayPosition >= 0) {
            if ((currentPlayPosition < firstVisibleItem || currentPlayPosition > (lastVisibleItem - 1))) {
                //???????????? ??????release ??????????????????
                JZVideoPlayer.releaseAllVideos();
//                if (JZVideoPlayerManager.getCurrentJzvd() != null &&
//                        JZVideoPlayerManager.getCurrentJzvd().currentScreen != JZVideoPlayer.SCREEN_WINDOW_TINY) {
//                    Log.e("jzvd", "onScroll: ????????????");
//                    JZVideoPlayerManager.getCurrentJzvd().startWindowTiny();
//                }
            } else {
                //???????????????????????????????????????????????????????????????
//                if (JZVideoPlayerManager.getCurrentJzvd() != null &&
//                        JZVideoPlayerManager.getCurrentJzvd().currentScreen == JZVideoPlayer.SCREEN_WINDOW_TINY) {
//                    Log.e("jzvd", "onScroll: ????????????");
//                    JZVideoPlayer.backPress();
//                }
            }
        }
    }

    //TODO ????????????
    public void onSeekComplete() {

    }

    public void showWifiDialog(int event) {
    }

    public void showProgressDialog(float deltaX,
                                   String seekTime, int seekTimePosition,
                                   String totalTime, int totalTimeDuration) {
    }

    public void dismissProgressDialog() {

    }

    public void showVolumeDialog(float deltaY, int volumePercent) {

    }

    public void dismissVolumeDialog() {

    }

    public void showBrightnessDialog(int brightnessPercent) {

    }

    public void dismissBrightnessDialog() {

    }

    public static class JZAutoFullscreenListener implements SensorEventListener {
        @Override
        public void onSensorChanged(SensorEvent event) {//???????????????????????????????????????????????????
            final float x = event.values[SensorManager.DATA_X];
            float y = event.values[SensorManager.DATA_Y];
            float z = event.values[SensorManager.DATA_Z];
            //???????????????????????????????????????????????????
            if (((x > -15 && x < -10) || (x < 15 && x > 10)) && Math.abs(y) < 1.5) {
                if ((System.currentTimeMillis() - lastAutoFullscreenTime) > 2000) {
                    if (JZVideoPlayerManager.getCurrentJzvd() != null) {
                        JZVideoPlayerManager.getCurrentJzvd().autoFullscreen(x);
                    }
                    lastAutoFullscreenTime = System.currentTimeMillis();
                }
            }
        }

        @Override
        public void onAccuracyChanged(Sensor sensor, int accuracy) {
        }
    }

    public class ProgressTimerTask extends TimerTask {
        @Override
        public void run() {
            if (currentState == CURRENT_STATE_PLAYING || currentState == CURRENT_STATE_PAUSE) {
//                Log.v(TAG, "onProgressUpdate " + position + "/" + duration + " [" + this.hashCode() + "] ");
                mHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        int position = getCurrentPositionWhenPlaying();
                        int duration = getDuration();
                        int progress = position * 100 / (duration == 0 ? 1 : duration);
                        setProgressAndText(progress, position, duration);
                    }
                });
            }
        }
    }
}
