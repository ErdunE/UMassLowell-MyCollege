package com.example.mysmartcamera;

import android.app.Application;
import android.content.Context;

public class App extends Application {

    private static Context mContext;

    public static App app;
    public static App getInstance() {
        return app;
    }
    @Override
    public void onCreate() {
        super.onCreate();
        mContext = this;
        app = this;
    }

    public static Context getContext() {
        return mContext;
    }


}
