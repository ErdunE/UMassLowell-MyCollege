package com.asgmt.matwam.module.shared;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.webkit.WebSettings;
import android.webkit.WebView;

import com.asgmt.matwam.R;

public class WebViewActivity extends AppCompatActivity {

    private static final String ARG_URL = "ARG_URL";

    public static void start(Context context, String url) {
        Intent intent = new Intent(context, WebViewActivity.class);
        intent.putExtra(ARG_URL, url);
        context.startActivity(intent);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_web_view);

        String url = getIntent().getStringExtra(ARG_URL);
        WebView webView = findViewById(R.id.awv_web_view);
        webView.getSettings().setUseWideViewPort(true);
        webView.loadUrl(url);
    }
}