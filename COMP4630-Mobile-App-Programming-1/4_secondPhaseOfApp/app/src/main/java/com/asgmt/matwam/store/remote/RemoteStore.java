package com.asgmt.matwam.store.remote;

import android.content.Context;
import android.util.Log;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.asgmt.matwam.store.Store;
import com.asgmt.matwam.store.local.investment.Investment;
import com.asgmt.matwam.store.local.weather.Weather;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class RemoteStore {

    private static final String TAG = "Store";
    private final Context _context;

    public RemoteStore(Context context) {
        _context = context;
    }

    public void fetchWeather(final Weather weather, final Store.Callback<Weather> callback) {
        String url = String.format("http://api.weatherapi.com/v1/current.json?key=64cc0e3bd27e4306bda55617202510&q=%s", weather.place);
        StringRequest request = new StringRequest(Request.Method.GET, url, new Response.Listener<String>() {
            @Override
            public void onResponse(String response) {
                Weather.update(response, weather);
                callback.onResponse(weather);
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                callback.onError(error.getMessage());
            }
        });
        Network.getInstance(_context).addToRequestQueue(request);
    }

    public void fetchAddress(String input, final Store.Callback<List<String>> callback) {
        final String url = String.format("https://wft-geo-db.p.rapidapi.com/v1/geo/cities?limit=10&keys=name&namePrefix=%s", input);
        StringRequest request = new StringRequest(Request.Method.GET, url, new Response.Listener<String>() {
            @Override
            public void onResponse(String response) {
                try {
                    Log.d(TAG, "onResponse: " + response);
                    List<String> data = new ArrayList<>();
                    JSONObject jo = new JSONObject(response);
                    JSONArray jaData = jo.getJSONArray("data");
                    for (int i = 0; i < jaData.length(); i++) {
                        JSONObject joData = jaData.getJSONObject(i);
                        String city = joData.getString("city");
                        String region = joData.getString("region");
                        String country = joData.getString("country");
                        if (region.contains(city)) {
                            data.add(String.format("%s, %s", city, country));
                        } else {
                            data.add(String.format("%s, %s, %s", city, region, country));
                        }
                    }
                    callback.onResponse(data);
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                callback.onError(error.getMessage());
            }
        }) {
            @Override
            public Map<String, String> getHeaders() {
                Map<String, String> headers = new HashMap<>();
                headers.put("x-rapidapi-host", "wft-geo-db.p.rapidapi.com");
                headers.put("x-rapidapi-key", "8b295cc7e1mshf7cef2ce98e1588p1a76a2jsnd6d20d32e0a8");
                return headers;
            }
        };

        Network.getInstance(_context).addToRequestQueue(request);
    }

    public void fetchStock(final Investment investment, final Store.Callback<Investment> callback) {
        final String url = String.format("https://apidojo-yahoo-finance-v1.p.rapidapi.com/stock/v3/get-historical-data?region=US&symbol=%s", investment.symbol);
        StringRequest request = new StringRequest(Request.Method.GET, url, new Response.Listener<String>() {
            @Override
            public void onResponse(String response) {
                Log.d(TAG, "onResponse: " + response);
                Investment.update(response, investment);
                callback.onResponse(investment);
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.d(TAG, "onErrorResponse: " + error);
                callback.onError(error.getMessage());
            }
        }) {
            @Override
            public Map<String, String> getHeaders() {
                Map<String, String> headers = new HashMap<>();
                headers.put("x-rapidapi-host", "apidojo-yahoo-finance-v1.p.rapidapi.com");
                headers.put("x-rapidapi-key", "8b295cc7e1mshf7cef2ce98e1588p1a76a2jsnd6d20d32e0a8");
                return headers;
            }
        };

        Network.getInstance(_context).addToRequestQueue(request);
    }

    public void fetchCOVID19(final Store.Callback<String> callback) {
        final String url = "https://covid-19-data.p.rapidapi.com/totals";
        StringRequest request = new StringRequest(Request.Method.GET, url, new Response.Listener<String>() {
            @Override
            public void onResponse(String response) {
                callback.onResponse(response);
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                callback.onError(error.getMessage());
            }
        }) {
            @Override
            public Map<String, String> getHeaders() {
                Map<String, String> headers = new HashMap<>();
                headers.put("x-rapidapi-host", "covid-19-data.p.rapidapi.com");
                headers.put("x-rapidapi-key", "8b295cc7e1mshf7cef2ce98e1588p1a76a2jsnd6d20d32e0a8");
                return headers;
            }
        };
        Network.getInstance(_context).addToRequestQueue(request);
    }

}
