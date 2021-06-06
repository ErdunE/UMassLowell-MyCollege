package com.asgmt.matwam.module.feature;

import androidx.appcompat.app.AppCompatActivity;
import androidx.constraintlayout.widget.ConstraintLayout;

import android.os.Bundle;
import android.view.View;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

import com.asgmt.matwam.R;
import com.asgmt.matwam.module.base.BaseActivity;
import com.asgmt.matwam.store.Store;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class COVID19Activity extends BaseActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_covid19);

        final TextView tvConfirmed = findViewById(R.id.ac_tv_confirmed);
        final TextView tvCritical = findViewById(R.id.ac_tv_critial);
        final TextView tvDeaths = findViewById(R.id.ac_tv_deaths);
        final TextView tvRecovered = findViewById(R.id.ac_tv_recovered);
        final ConstraintLayout clContent = findViewById(R.id.ac_cl_content);
        final ProgressBar pbLoading = findViewById(R.id.ac_pb_loading);

        pbLoading.setVisibility(View.VISIBLE);
        clContent.setVisibility(View.INVISIBLE);
        Store.getInstance(_context).fetchCOVID19(new Store.Callback<String>() {
            @Override
            public void onResponse(String data) {
                pbLoading.setVisibility(View.GONE);
                clContent.setVisibility(View.VISIBLE);
                try {
                    JSONArray ja = new JSONArray(data);
                    JSONObject jo = ja.getJSONObject(0);
                    tvConfirmed.setText(jo.optString("confirmed"));
                    tvCritical.setText(jo.optString("critical"));
                    tvDeaths.setText(jo.optString("deaths"));
                    tvRecovered.setText(jo.optString("recovered"));
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }

            @Override
            public void onError(String msg) {
                pbLoading.setVisibility(View.GONE);
                clContent.setVisibility(View.VISIBLE);
                Toast.makeText(_context, msg, Toast.LENGTH_SHORT).show();
            }
        });
    }
}