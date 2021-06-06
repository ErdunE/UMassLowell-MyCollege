package com.example.mysmartcamera.mycamera.utils;

import android.os.Environment;

import com.example.qoutelibyary.quote.videoRecord.other.MagicFilterType;


public class StaticFinalValues {

    public static final int RECORD_MIN_TIME = 5 * 1000;
    public static final int EMPTY = 0;
    public static final int DELAY_DETAL = 1;
    public static final int CHANGE_IMAGE = 10;
    public static final int OVER_CLICK = 11;
    public static final String ISSAVEVIDEOTEMPEXIST = "/storage/emulated/0/aserbaoCamera/";
    public static final String VIDEOTEMP = "/storage/emulated/0/aserbaoCamera/videotemp/";
    public static final String STORAGE_TEMP_VIDEO_PATH = Environment.getExternalStorageDirectory().getAbsolutePath() + "/123.mp4";

    public static final String MAX_NUMBER = "MaxNumber";
    public static final String RESULT_PICK_VIDEO = "ResultPickVideo";
    public static final String VIDEOFILEPATH = "VideoFilePath";
    public static final String MISNOTCOMELOCAL = "mIsNotComeLocal";//0表示本地视频，1表示非本地视频
    public static final String BUNDLE = "bundle";
    public static final String CUT_TIME = "cut_time";

    public static final int COMR_FROM_SEL_COVER_TIME_ACTIVITY = 1;
    public static final int COMR_FROM_VIDEO_EDIT_TIME_ACTIVITY = 2;

    public static final int REQUEST_CODE_PICK_VIDEO = 0x200;
    public static final int REQUEST_CODE_TAKE_VIDEO = 0x201;
    public static float VIDEO_WIDTH_HEIGHT = 0.85f;



    public static MagicFilterType[] types = new MagicFilterType[]{
            MagicFilterType.NONE,
            MagicFilterType.WARM,
            MagicFilterType.COOL,
            MagicFilterType.HUDSON,
            MagicFilterType.WARM,
            MagicFilterType.N1977,
    };
}
