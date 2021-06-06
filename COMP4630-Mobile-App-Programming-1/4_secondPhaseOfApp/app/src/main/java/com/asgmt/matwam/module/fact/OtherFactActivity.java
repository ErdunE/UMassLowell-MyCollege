package com.asgmt.matwam.module.fact;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;

import com.asgmt.matwam.R;
import com.asgmt.matwam.module.base.BaseActivity;
import com.asgmt.matwam.module.shared.WebViewActivity;

public class OtherFactActivity extends BaseActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_other_fact);

        findViewById(R.id.aof_btn_go).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                WebViewActivity.start(_context, "https://erdune.github.io/ErdunE/");
            }
        });
    }
}