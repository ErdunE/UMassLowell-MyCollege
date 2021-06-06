package com.assignment.a3_firstapp;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.SwitchCompat;

import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private ImageView _ivBackground;
    private TextView _tvSelfIntro;
    private EditText _etSelfIntro;
    private SwitchCompat _scShowBg;
    private Button _btnSubmit;

    private boolean _editing;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        _ivBackground = findViewById(R.id.m_iv_background);
        _tvSelfIntro = findViewById(R.id.m_tv_self_intro);
        _etSelfIntro = findViewById(R.id.m_et_self_intro);
        _scShowBg = findViewById(R.id.m_sc_show_bg);
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
    }


    public void setEditing(boolean editing) {
        _editing = editing;

        if (editing) {
            _tvSelfIntro.setVisibility(View.INVISIBLE);
            _etSelfIntro.setVisibility(View.VISIBLE);
            _btnSubmit.setText(R.string.m_btn_submit_editing);
        } else {
            if (!TextUtils.isEmpty(getSelfIntro())) {
                _tvSelfIntro.setText(getSelfIntro());
            }
            _tvSelfIntro.setVisibility(View.VISIBLE);
            _etSelfIntro.setVisibility(View.INVISIBLE);
            _btnSubmit.setText(R.string.m_btn_submit_normal);
        }
    }

    private String getSelfIntro() {
        return _etSelfIntro.getText().toString().trim();
    }
}