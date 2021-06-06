package com.example.mysmartcamera.mycamera;

import android.app.Application;
import android.content.Context;
import android.util.DisplayMetrics;

import com.danikula.videocache.HttpProxyCacheServer;


public class MyApp extends Application {
    public static boolean DEBUG = true;
    private static Context mContext;
    public static int screenWidth;
    public static int screenHeight;
    @Override
    public void onCreate() {
        super.onCreate();
        mContext = this;
        DisplayMetrics mDisplayMetrics = getApplicationContext().getResources()
                .getDisplayMetrics();
        screenWidth = mDisplayMetrics.widthPixels;
        screenHeight = mDisplayMetrics.heightPixels;
        app = this;
    }

    public static Context getContext() {
        return mContext;
    }

    public static MyApp app;
    public static MyApp getInstance() {
        return app;
    }

    //=====================================================缓存区
    private HttpProxyCacheServer proxy;

    public static HttpProxyCacheServer getProxy() {
        MyApp app = getInstance();
        return app.proxy == null ? (app.proxy = app.newProxy()) : app.proxy;
    }

    private HttpProxyCacheServer newProxy() {
        return new HttpProxyCacheServer(this);
    }

}
