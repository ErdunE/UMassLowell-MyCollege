package com.asgmt.matwam.device;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.location.Criteria;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Build;
import android.text.TextUtils;

import androidx.annotation.NonNull;
import androidx.core.app.ActivityCompat;

public class LocationHelper {

    private final Context _context;
    private final LocationManager _locationManager;
    private LocationListener _locationListener;

    public LocationHelper(Context context) {
        _context = context.getApplicationContext();
        _locationManager = (LocationManager) _context.getSystemService(Context.LOCATION_SERVICE);
    }

    private Location getGPS(Context ctx) {
        Location location = null;
        LocationManager manager = (LocationManager) ctx.getSystemService(Context.LOCATION_SERVICE);
        if (ActivityCompat.checkSelfPermission(ctx, Manifest.permission.ACCESS_FINE_LOCATION)
                != PackageManager.PERMISSION_GRANTED) {
            return null;
        }
        if (manager.isProviderEnabled(LocationManager.GPS_PROVIDER)) {
            location = manager.getLastKnownLocation(LocationManager.GPS_PROVIDER);
        }
        return location;
    }

    public void addGPSLocationListener(LocationListener locationListener) {
        _locationListener = locationListener;
    }

    public void requestLocationUpdates() {
        if (ActivityCompat.checkSelfPermission(_context, Manifest.permission.ACCESS_FINE_LOCATION)
                != PackageManager.PERMISSION_GRANTED
                && ActivityCompat.checkSelfPermission(_context, Manifest.permission.ACCESS_COARSE_LOCATION)
                != PackageManager.PERMISSION_GRANTED) {
            return;
        }
        if (_locationListener != null) {
            String provider = LocationManager.GPS_PROVIDER;
            _locationManager.requestLocationUpdates(provider, 5000L, 0.0F, _locationListener);
        }
    }

    public void removeGPSLocationListener() {
        if (_locationManager != null && _locationListener != null) {
            _locationManager.removeUpdates(_locationListener);
        }
    }
}
