package com.asgmt.matwam;

import android.app.Application;

import com.asgmt.matwam.store.Store;
import com.asgmt.matwam.store.remote.Network;

public class App extends Application {
    @Override
    public void onCreate() {
        super.onCreate();

        Store.getInstance(this).init();
    }
}
