package com.asgmt.matwam.module.weather;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.location.Address;
import android.location.Geocoder;
import android.location.Location;
import android.location.LocationListener;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.core.app.ActivityCompat;

import com.asgmt.matwam.R;
import com.asgmt.matwam.device.LocationHelper;
import com.asgmt.matwam.module.base.BaseActivity;
import com.asgmt.matwam.module.base.BaseSearchActivity;
import com.asgmt.matwam.store.Store;
import com.asgmt.matwam.store.local.weather.Weather;

import java.io.IOException;
import java.util.List;
import java.util.Locale;

public class WeatherDetailActivity extends BaseSearchActivity {

    public static final String ARG_POSITION = "ARG_POSITION";
    public static final String ARG_WEATHER = "ARG_WEATHER";

    public static void startFromWeatherForResult(BaseActivity activity, int position, Weather weather, int requestCode) {
        Intent intent = new Intent(activity, WeatherDetailActivity.class);
        intent.putExtra(ARG_POSITION, position);
        intent.putExtra(ARG_WEATHER, weather);
        activity.startActivityForResult(intent, requestCode);
    }

    private LocationHelper _locationHelper;

    private EditText _etPlace;
    private Weather _weather;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_weather_detail);

        _weather = getIntent().getParcelableExtra(ARG_WEATHER);

        TextView tvTitle = findViewById(R.id.p_tv_label);
        tvTitle.setText(_weather.label);

        _etPlace = findViewById(R.id.p_et_place);
        _etPlace.setText(_weather.place);

        ImageView ivLocate = findViewById(R.id.p_iv_locate);
        ivLocate.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                _locationHelper.requestLocationUpdates();
            }
        });

        Button btnSubmit = findViewById(R.id.p_btn_submit);
        btnSubmit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                _weather.place = _etPlace.getText().toString().trim();
                Store.getInstance(_context).insertOrUpdateWeather(_weather);
                setResult(RESULT_OK, getIntent());
                finish();
            }
        });

        initLocationHelper();
    }

    private void initLocationHelper() {
        _locationHelper = new LocationHelper(_context);
        _locationHelper.addGPSLocationListener(new LocationListener() {
            @Override
            public void onLocationChanged(@NonNull Location location) {
                _etPlace.setText(decodedAddress(location.getLatitude(), location.getLongitude()));
            }
        });
    }

    private String decodedAddress(double lat, double lng) {
        Geocoder geocoder = new Geocoder(_context, Locale.getDefault());
        List<Address> addressList;
        try {
            addressList = geocoder.getFromLocation(lat, lng, 1);
            if (addressList != null && addressList.size() > 0) {
                Address address = addressList.get(0);
                if (address.getAdminArea().contains(address.getLocality())) {
                    return String.format("%s, %s", address.getLocality(), address.getCountryName());
                } else {
                    return String.format("%s, %s, %s", address.getLocality(), address.getAdminArea(), address.getCountryName());
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    protected void onSearchItemClick(String string) {
        _etPlace.setText(string);
    }
}