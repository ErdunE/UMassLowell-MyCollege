package com.asgmt.matwam.store.local.investment;

import androidx.room.Dao;
import androidx.room.Insert;
import androidx.room.OnConflictStrategy;
import androidx.room.Query;

import com.asgmt.matwam.store.local.fact.Fact;

import java.util.List;

@Dao
public interface InvestmentDao {

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    Long insertOrUpdate(Investment investment);

    @Query("SELECT * FROM investment WHERE holder = :holder")
    List<Investment> list(String holder);

    @Query("SELECT * FROM investment WHERE id = :id")
    Investment one(Long id);
}
