package com.asgmt.matwam.store.remote;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.util.Log;
import android.util.LruCache;

import com.android.volley.AuthFailureError;
import com.android.volley.DefaultRetryPolicy;
import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.toolbox.ImageLoader;
import com.android.volley.toolbox.NetworkImageView;
import com.android.volley.toolbox.Volley;
import com.asgmt.matwam.R;
import com.asgmt.matwam.store.local.Database;
import com.asgmt.matwam.store.local.fact.Fact;
import com.asgmt.matwam.store.local.weather.Weather;


public class Network {

    private static final String TAG = "Store";

    private static volatile Network INSTANCE;
    private final RequestQueue _requestQueue;
    private final ImageLoader _imageLoader;

    public static Network getInstance(Context context) {
        if (INSTANCE == null) {
            synchronized (Network.class) {
                if (INSTANCE == null) {
                    INSTANCE = new Network(context);
                }
            }
        }
        return INSTANCE;
    }
    
    public void fetchImage(NetworkImageView imageView, String url) {
        if (url != null) {
            _imageLoader.get(url, ImageLoader.getImageListener(imageView, R.drawable.im_loading, R.drawable.im_loading));
            imageView.setImageUrl(url, _imageLoader);
        }
    }

    public <T> void addToRequestQueue(Request<T> request) {
        Log.d(TAG, "addToRequestQueue: " + request.getUrl());
        request.setRetryPolicy(new DefaultRetryPolicy(
                DefaultRetryPolicy.DEFAULT_TIMEOUT_MS,
                DefaultRetryPolicy.DEFAULT_MAX_RETRIES,
                DefaultRetryPolicy.DEFAULT_BACKOFF_MULT));
        _requestQueue.add(request);
    }

    private Network(Context context) {
        context = context.getApplicationContext();
        _requestQueue = Volley.newRequestQueue(context);
        _imageLoader = new ImageLoader(_requestQueue, new ImageLoader.ImageCache() {
            private final LruCache<String, Bitmap> _cache = new LruCache<>(20);

            @Override
            public Bitmap getBitmap(String url) {
                return _cache.get(url);
            }

            @Override
            public void putBitmap(String url, Bitmap bitmap) {
                _cache.put(url, bitmap);
            }
        });
    }
}
