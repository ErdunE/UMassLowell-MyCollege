package com.asgmt.matwam.store.local.weather;

import androidx.lifecycle.LiveData;
import androidx.room.Dao;
import androidx.room.Insert;
import androidx.room.OnConflictStrategy;
import androidx.room.Query;

import java.util.List;

@Dao
public interface WeatherDao {
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    void insertOrUpdate(Weather weather);

    @Query("SELECT * FROM weather")
    List<Weather> list();

    @Query("SELECT * FROM weather WHERE id = :id")
    Weather one(Long id);
}
