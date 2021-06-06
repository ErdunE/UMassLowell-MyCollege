package com.asgmt.matwam.store.local;

import android.content.Context;

import androidx.room.Room;
import androidx.room.RoomDatabase;

import com.asgmt.matwam.store.local.fact.Fact;
import com.asgmt.matwam.store.local.fact.FactDao;
import com.asgmt.matwam.store.local.investment.Investment;
import com.asgmt.matwam.store.local.investment.InvestmentDao;
import com.asgmt.matwam.store.local.weather.Weather;
import com.asgmt.matwam.store.local.weather.WeatherDao;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

@androidx.room.Database(entities = { Weather.class, Fact.class, Investment.class }, version = 1, exportSchema = false)
public abstract class Database extends RoomDatabase {
    public abstract WeatherDao weatherDao();
    public abstract FactDao factDao();
    public abstract InvestmentDao investmentDao();

    private static volatile Database INSTANCE;
    private final ExecutorService _executorService = Executors.newFixedThreadPool(4);

    public static Database getInstance(Context context) {
        if (INSTANCE == null) {
            synchronized (Database.class) {
                if (INSTANCE == null) {
                    INSTANCE = Room.databaseBuilder(context.getApplicationContext(),
                            Database.class, "matwam.db").build();
                }
            }
        }
        return INSTANCE;
    }
}
