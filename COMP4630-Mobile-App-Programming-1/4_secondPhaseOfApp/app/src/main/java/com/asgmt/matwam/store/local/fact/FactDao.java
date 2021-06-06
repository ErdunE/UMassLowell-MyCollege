package com.asgmt.matwam.store.local.fact;

import androidx.room.Dao;
import androidx.room.Insert;
import androidx.room.OnConflictStrategy;
import androidx.room.Query;

import java.util.List;

@Dao
public interface FactDao {
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    Long insertOrUpdate(Fact fact);

    @Query("SELECT * FROM fact")
    List<Fact> list();

    @Query("SELECT * FROM fact WHERE id = :id")
    Fact one(Long id);
}
