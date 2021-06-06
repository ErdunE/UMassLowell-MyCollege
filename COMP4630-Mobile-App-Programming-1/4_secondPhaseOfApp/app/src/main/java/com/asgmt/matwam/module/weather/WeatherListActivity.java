package com.asgmt.matwam.module.weather;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

import com.asgmt.matwam.R;
import com.asgmt.matwam.module.base.BaseActivity;
import com.asgmt.matwam.store.Store;
import com.asgmt.matwam.store.local.Database;
import com.asgmt.matwam.store.local.weather.Weather;
import com.asgmt.matwam.module.base.BaseListAdapter;

import java.util.List;

public class WeatherListActivity extends BaseActivity {

    private static final String TAG = "WeatherListActivity";
    private WeatherListAdapter _weatherListAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_weather);

        final RecyclerView recyclerView = findViewById(R.id.w_recycler_view);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));
        _weatherListAdapter = new WeatherListAdapter(this);
        recyclerView.setAdapter(_weatherListAdapter);
        _weatherListAdapter.setOnItemClickListener(new BaseListAdapter.OnItemClickListener<Weather>() {
            @Override
            public void onItemClick(int position) {
                Weather weather = _weatherListAdapter.getItem(position);
                WeatherDetailActivity.startFromWeatherForResult(WeatherListActivity.this, position, weather, 0);
            }
        });
        _weatherListAdapter.setOnItemChildClickListener(new BaseListAdapter.OnItemChildClickListener<Weather>() {
            @Override
            public void onItemChildClick(final int position) {
                _weatherListAdapter.fetchWeather(position);
            }
        });

        Store.getInstance(this).getWeathers(new Store.Callback<List<Weather>>() {
            @Override
            public void onResponse(List<Weather> data) {
                _weatherListAdapter.submitList(data);
                _weatherListAdapter.fetchWeathers();
            }

            @Override
            public void onError(String msg) {

            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (resultCode == RESULT_OK) {
            int position = data.getIntExtra(WeatherDetailActivity.ARG_POSITION, -1);
            Weather weather = data.getParcelableExtra(WeatherDetailActivity.ARG_WEATHER);
            Log.d(TAG, "onActivityResult: " + data.getExtras());
            if (position != -1) {
                _weatherListAdapter.getItem(position).place = weather.place;
                _weatherListAdapter.fetchWeather(position);
            }
        }
    }
}