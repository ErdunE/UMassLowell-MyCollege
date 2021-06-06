package com.asgmt.matwam.module.fact;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import com.asgmt.matwam.R;
import com.asgmt.matwam.module.base.BaseActivity;
import com.asgmt.matwam.module.weather.WeatherDetailActivity;
import com.asgmt.matwam.store.Store;
import com.asgmt.matwam.store.local.fact.Fact;
import com.asgmt.matwam.module.base.BaseListAdapter;
import com.asgmt.matwam.store.local.weather.Weather;

import java.util.List;

public class FactListActivity extends BaseActivity {

    private static final String TAG = "FactListActivity";

    private FactListAdapter _factListAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fact);

        initView();
    }

    private void initView() {
        RecyclerView recyclerView = findViewById(R.id.f_recycler_view);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));
        _factListAdapter = new FactListAdapter(this);
        recyclerView.setAdapter(_factListAdapter);
        _factListAdapter.setOnItemClickListener(new BaseListAdapter.OnItemClickListener<Fact>() {
            @Override
            public void onItemClick(int position) {
                Fact fact = _factListAdapter.getItem(position);
                FactDetailActivity.startFromFactForResult(FactListActivity.this, position, fact, 0);
            }
        });

        Store.getInstance(this).getFacts(new Store.Callback<List<Fact>>() {
            @Override
            public void onResponse(List<Fact> data) {
                _factListAdapter.submitList(data);
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
            int position = data.getIntExtra(FactDetailActivity.ARG_POSITION, -1);
            Fact fact = data.getParcelableExtra(FactDetailActivity.ARG_FACT);
            Log.d(TAG, "onActivityResult: " + data.getExtras());
            if (position != -1) {
                _factListAdapter.getItem(position).content = fact.content;
                _factListAdapter.notifyItemChanged(position);
            }
        }
    }
}