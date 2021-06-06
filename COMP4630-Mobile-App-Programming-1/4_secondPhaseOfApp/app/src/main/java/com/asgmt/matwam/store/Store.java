package com.asgmt.matwam.store;

import android.content.Context;
import android.content.SharedPreferences;

import com.asgmt.matwam.R;
import com.asgmt.matwam.store.local.LocalStore;
import com.asgmt.matwam.store.local.fact.Fact;
import com.asgmt.matwam.store.local.investment.Investment;
import com.asgmt.matwam.store.local.weather.Weather;
import com.asgmt.matwam.store.remote.Network;
import com.asgmt.matwam.store.remote.RemoteStore;

import java.util.List;

public class Store {

    private static volatile Store INSTANCE;
    private final Context _context;
    private final RemoteStore _remoteStore;
    private final LocalStore _localStore;

    private Store(Context context) {
        _context = context.getApplicationContext();
        _remoteStore = new RemoteStore(_context);
        _localStore = new LocalStore(_context);
    }

    public static Store getInstance(Context context) {
        if (INSTANCE == null) {
            synchronized (Network.class) {
                if (INSTANCE == null) {
                    INSTANCE = new Store(context);
                }
            }
        }
        return INSTANCE;
    }

    public void init() {
        SharedPreferences sp = _context.getSharedPreferences("matwam", Context.MODE_PRIVATE);
        boolean hasLoad = sp.getBoolean("hasLoad", false);
        if (!hasLoad) {
            String[] placeKeys = _context.getResources().getStringArray(R.array.weather_keys);
            String[] placeValues = _context.getResources().getStringArray(R.array.weather_values);
            for (int i = 0; i < placeKeys.length; i++) {
                _localStore.insertOrUpdateWeather(Weather.create(i + 1, placeKeys[i], placeValues[i]));
            }

            String[] factKeys = _context.getResources().getStringArray(R.array.fact_keys);
            String[] factValues = _context.getResources().getStringArray(R.array.fact_values);
            for (int i = 0; i < factKeys.length; i++) {
                _localStore.insertOrUpdateFact(Fact.create(i + 1, factKeys[i], factValues[i]));
            }

            String[] stockHolders = _context.getResources().getStringArray(R.array.investment_holders);
            String[] stockSymbols = _context.getResources().getStringArray(R.array.investment_symbols);
            String[] stockNames = _context.getResources().getStringArray(R.array.investment_names);
            for (int i = 0; i < stockHolders.length; i++) {
                String[] symbols = stockSymbols[i].split(",");
                String[] names = stockNames[i].split(",");
                for (int j = 0; j < symbols.length; j++) {
                    _localStore.insertOrUpdateInvestment(Investment.create(stockHolders[i], symbols[j], names[j]));
                }
            }

            SharedPreferences.Editor editor = sp.edit();
            editor.putBoolean("hasLoad", true);
            editor.apply();
        }
    }

    public void insertOrUpdateWeather(Weather weather) {
        _localStore.insertOrUpdateWeather(weather);
    }

    public void insertOrUpdateFact(Fact fact) {
        _localStore.insertOrUpdateFact(fact);
    }

    public void insertOrUpdateInvestment(Investment investment) {
        _localStore.insertOrUpdateInvestment(investment);
    }

    public void fetchWeather(Weather weather, final Callback<Weather> callback) {
        _remoteStore.fetchWeather(weather, new Callback<Weather>() {
            @Override
            public void onResponse(Weather data) {
                callback.onResponse(data);
                _localStore.insertOrUpdateWeather(data);
            }

            @Override
            public void onError(String msg) {
                callback.onError(msg);
            }
        });
    }

    public void fetchAddress(String input, final Callback<List<String>> callback) {
        _remoteStore.fetchAddress(input, new Callback<List<String>>() {
            @Override
            public void onResponse(List<String> data) {
                callback.onResponse(data);
            }

            @Override
            public void onError(String msg) {
                callback.onError(msg);
            }
        });
    }

    public void fetchInvestment(Investment investment, final Callback<Investment> callback) {
        _remoteStore.fetchStock(investment, new Callback<Investment>() {
            @Override
            public void onResponse(Investment data) {
                callback.onResponse(data);
                _localStore.insertOrUpdateInvestment(data);
            }

            @Override
            public void onError(String msg) {
                callback.onError(msg);
            }
        });
    }

    public void fetchCOVID19(final Store.Callback<String> callback) {
        _remoteStore.fetchCOVID19(callback);
    }

    public void getWeathers(Callback<List<Weather>> callback) {
        _localStore.getWeathers(callback);
    }

    public void getFacts(Callback<List<Fact>> callback) {
        _localStore.getFacts(callback);
    }

    public void getInvestments(String holder, Callback<List<Investment>> callback) {
        _localStore.getInvestments(holder, callback);
    }

    public interface Callback<T> {
        void onResponse(T data);
        void onError(String msg);
    }
}
