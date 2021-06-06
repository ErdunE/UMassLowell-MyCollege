package com.asgmt.matwam.module;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.SwitchCompat;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

import com.asgmt.matwam.R;
import com.asgmt.matwam.module.base.BaseActivity;
import com.asgmt.matwam.module.fact.FactListActivity;
import com.asgmt.matwam.module.fact.OtherFactActivity;
import com.asgmt.matwam.module.feature.COVID19Activity;
import com.asgmt.matwam.module.investment.InvestmentListActivity;
import com.asgmt.matwam.module.shared.WebViewActivity;
import com.asgmt.matwam.module.weather.WeatherListActivity;

public class MainActivity extends BaseActivity {

    private ImageView _ivBackground;
    private TextView _tvSelfIntro;
    private EditText _etSelfIntro;
    private Button _btnSubmit;

    private boolean _editing;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        _ivBackground = findViewById(R.id.m_iv_background);
        _tvSelfIntro = findViewById(R.id.m_tv_self_intro);
        _etSelfIntro = findViewById(R.id.m_et_self_intro);
        SwitchCompat _scShowBg = findViewById(R.id.m_sc_show_bg);
        _btnSubmit = findViewById(R.id.m_btn_submit);

        _scShowBg.setChecked(true);
        setEditing(false);

        _scShowBg.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                _ivBackground.setVisibility(b ? View.VISIBLE : View.INVISIBLE);
            }
        });
        _btnSubmit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                setEditing(!_editing);
            }
        });

        findViewById(R.id.m_btn_weather).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(MainActivity.this, WeatherListActivity.class));
            }
        });
        findViewById(R.id.m_btn_fact).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(MainActivity.this, FactListActivity.class));
            }
        });
        findViewById(R.id.m_btn_invest).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(MainActivity.this, InvestmentListActivity.class));
            }
        });
        findViewById(R.id.m_btn_resume).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                WebViewActivity.start(MainActivity.this, "file:///android_asset/resume.html");
            }
        });
        findViewById(R.id.m_btn_other_fact).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(MainActivity.this, OtherFactActivity.class));
            }
        });
        findViewById(R.id.m_btn_more_feature).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(MainActivity.this, COVID19Activity.class));
            }
        });
        requestPermission();
    }


    public void setEditing(boolean editing) {
        _editing = editing;

        if (editing) {
            _tvSelfIntro.setVisibility(View.INVISIBLE);
            _etSelfIntro.setVisibility(View.VISIBLE);
            _btnSubmit.setText(R.string.shared_btn_submit);
        } else {
            if (!TextUtils.isEmpty(getSelfIntro())) {
                _tvSelfIntro.setText(getSelfIntro());
            }
            _tvSelfIntro.setVisibility(View.VISIBLE);
            _etSelfIntro.setVisibility(View.INVISIBLE);
            _btnSubmit.setText(R.string.am_btn_submit_normal);
        }
    }

    private String getSelfIntro() {
        return _etSelfIntro.getText().toString().trim();
    }

    private void requestPermission() {
        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.M) {
            return;
        }
        if (ActivityCompat.checkSelfPermission(_context, Manifest.permission.ACCESS_COARSE_LOCATION)
                != PackageManager.PERMISSION_GRANTED
                && ActivityCompat.checkSelfPermission(_context, Manifest.permission.ACCESS_FINE_LOCATION)
                != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[] { Manifest.permission.ACCESS_COARSE_LOCATION, Manifest.permission.ACCESS_FINE_LOCATION }, 0);
        }
    }
}