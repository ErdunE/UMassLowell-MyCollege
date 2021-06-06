package com.asgmt.matwam.store.local;

import android.content.Context;
import android.telecom.Call;

import com.asgmt.matwam.store.Store;
import com.asgmt.matwam.store.local.fact.Fact;
import com.asgmt.matwam.store.local.investment.Investment;
import com.asgmt.matwam.store.local.weather.Weather;
import com.asgmt.matwam.store.local.weather.WeatherDao;

import java.util.List;
import java.util.concurrent.Executor;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class LocalStore {

    private final Context _context;
    private final ExecutorService _executorService;

    public LocalStore(Context context) {
        _context = context;
        _executorService = Executors.newFixedThreadPool(4);
    }

    public void insertOrUpdateWeather(final Weather weather) {
        _executorService.execute(new Runnable() {
            @Override
            public void run() {
                Database.getInstance(_context).weatherDao().insertOrUpdate(weather);
            }
        });
    }

    public void insertOrUpdateFact(final Fact fact) {
        _executorService.execute(new Runnable() {
            @Override
            public void run() {
                Database.getInstance(_context).factDao().insertOrUpdate(fact);
            }
        });
    }

    public void insertOrUpdateInvestment(final Investment investment) {
        _executorService.execute(new Runnable() {
            @Override
            public void run() {
                Database.getInstance(_context).investmentDao().insertOrUpdate(investment);
            }
        });
    }

    public void getWeathers(final Store.Callback<List<Weather>> callback) {
        _executorService.execute(new Runnable() {
            @Override
            public void run() {
                try {
                    List<Weather> weathers = Database.getInstance(_context).weatherDao().list();
                    callback.onResponse(weathers);
                } catch (Exception e) {
                    callback.onError(e.getMessage());
                }
            }
        });
    }

    public void getFacts(final Store.Callback<List<Fact>> callback) {
        _executorService.execute(new Runnable() {
            @Override
            public void run() {
                try {
                    List<Fact> facts = Database.getInstance(_context).factDao().list();
                    callback.onResponse(facts);
                } catch (Exception e) {
                    callback.onError(e.getMessage());
                }
            }
        });
    }

    public void getInvestments(final String holder, final Store.Callback<List<Investment>> callback) {
        _executorService.execute(new Runnable() {
            @Override
            public void run() {
                try {
                    List<Investment> investments = Database.getInstance(_context).investmentDao().list(holder);
                    callback.onResponse(investments);
                } catch (Exception e) {
                    callback.onError(e.getMessage());
                }
            }
        });
    }
}
