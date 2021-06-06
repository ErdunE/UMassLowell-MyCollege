package com.asgmt.matwam.module.investment;

import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Bundle;
import android.widget.RadioButton;
import android.widget.RadioGroup;

import com.asgmt.matwam.R;
import com.asgmt.matwam.module.base.BaseActivity;
import com.asgmt.matwam.module.base.BaseListAdapter;
import com.asgmt.matwam.store.Store;
import com.asgmt.matwam.store.local.investment.Investment;

import java.util.List;

public class InvestmentListActivity extends BaseActivity {

    private InvestmentListAdapter _investmentListAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_investment_list);

        initView();
    }

    private void initView() {
        final RecyclerView recyclerView = findViewById(R.id.il_recycler_view);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));
        _investmentListAdapter = new InvestmentListAdapter(this);
        recyclerView.setAdapter(_investmentListAdapter);
        _investmentListAdapter.setOnItemClickListener(new BaseListAdapter.OnItemClickListener<Investment>() {
            @Override
            public void onItemClick(int position) {

            }
        });


        RadioGroup rgSegment = findViewById(R.id.il_rg_segment);
        rgSegment.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup radioGroup, int i) {
                int id = radioGroup.getCheckedRadioButtonId();
                RadioButton rb = findViewById(id);
                Store.getInstance(InvestmentListActivity.this).getInvestments(rb.getText().toString(),
                        new Store.Callback<List<Investment>>() {
                            @Override
                            public void onResponse(List<Investment> data) {
                                _investmentListAdapter.submitList(data, new Runnable() {
                                    @Override
                                    public void run() {
                                        _investmentListAdapter.fetchInvestments();
                                    }
                                });
                            }

                            @Override
                            public void onError(String msg) {

                            }
                        });
            }
        });

        RadioButton rbMe = findViewById(R.id.il_rb_me);
        rbMe.setChecked(true);
    }

}