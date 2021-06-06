package com.example.mysmartcamera;

import android.app.Application;
import android.content.Context;
import android.util.DisplayMetrics;

public class App extends Application {

    private static Context mContext;

    public static App app;
    public static App getInstance() {
        return app;
    }

    public static int screenWidth;
    public static int screenHeight;
    @Override
    public void onCreate() {
        super.onCreate();
        mContext = this;
        app = this;
        DisplayMetrics mDisplayMetrics = getApplicationContext().getResources()
                .getDisplayMetrics();
        screenWidth = mDisplayMetrics.widthPixels;
        screenHeight = mDisplayMetrics.heightPixels;
    }

    public static Context getContext() {
        return mContext;
    }


}
