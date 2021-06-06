package com.asgmt.matwam.module.base;

import android.annotation.SuppressLint;
import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.text.TextUtils;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Filter;
import android.widget.Filterable;

import androidx.annotation.NonNull;
import androidx.appcompat.widget.SearchView;
import androidx.appcompat.widget.SearchView.SearchAutoComplete;

import androidx.annotation.Nullable;

import com.asgmt.matwam.R;
import com.asgmt.matwam.store.Store;

import java.util.ArrayList;
import java.util.List;

public abstract class BaseSearchActivity extends BaseActivity {

    private static final String TAG = "BaseSearchActivity";

    private static final int REQUEST_SEARCH = 0x1;
    private static final int MESSAGE_SEARCH = 0x11;
    private static final int DELAY_SEARCH = 300;

    private Handler _handler;

    private SearchAutoComplete _searchAC;
    private SearchAdapter _searchAdapter;

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater mi = getMenuInflater();
        mi.inflate(R.menu.menu_detail, menu);
        SearchView searchView = (SearchView) menu.findItem(R.id.action_search).getActionView();
        initSearchView(searchView);
        return true;
    }

    @SuppressLint("RestrictedApi")
    private void initSearchView(SearchView searchView) {
        searchView.setOnQueryTextListener(new SearchView.OnQueryTextListener() {
            @Override
            public boolean onQueryTextSubmit(String s) {

                return true;
            }

            @Override
            public boolean onQueryTextChange(String s) {
                _handler.removeMessages(MESSAGE_SEARCH);
                _handler.sendEmptyMessageDelayed(MESSAGE_SEARCH, DELAY_SEARCH);
                return true;
            }
        });

        _searchAC = searchView.findViewById(androidx.appcompat.R.id.search_src_text);
        _searchAC.setDropDownBackgroundResource(R.color.cardview_light_background);
        _searchAC.setThreshold(2);
        _searchAdapter = new SearchAdapter(_context, android.R.layout.simple_list_item_1);
        _searchAC.setAdapter(_searchAdapter);
        _searchAC.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int position, long viewId) {
                onSearchItemClick(_searchAdapter.getItem(position));
            }
        });

        _handler = new Handler(new Handler.Callback() {
            @Override
            public boolean handleMessage(@NonNull Message message) {
                if (message.what == MESSAGE_SEARCH) {
                    String input = _searchAC.getText().toString();
                    if (!TextUtils.isEmpty(input)) {
                        Store.getInstance(_context).fetchAddress(input, new Store.Callback<List<String>>() {
                            @Override
                            public void onResponse(List<String> data) {
                                Log.d(TAG, "onResponse: " + data.size());
                                _searchAdapter.setStrings(data);
                            }

                            @Override
                            public void onError(String msg) {

                            }
                        });
                    }
                }
                return false;
            }
        });
    }

    protected abstract void onSearchItemClick(String string);

    static class SearchAdapter extends ArrayAdapter<String> implements Filterable {

        private final List<String> _strings;

        public SearchAdapter(@NonNull Context context, int resource) {
            super(context, resource);
            _strings = new ArrayList<>();
        }

        public void setStrings(List<String> strings) {
            _strings.clear();
            _strings.addAll(strings);
            notifyDataSetChanged();
        }

        @Override
        public int getCount() {
            return _strings.size();
        }

        @Nullable
        @Override
        public String getItem(int position) {
            return _strings.get(position);
        }

        public Filter getFilter() {
            return new Filter() {
                @Override
                protected FilterResults performFiltering(CharSequence constraint) {
                    FilterResults results = new FilterResults();
                    if (constraint != null) {
                        results.values = _strings;
                        results.count = _strings.size();
                    }
                    return results;
                }

                @Override
                protected void publishResults(CharSequence constraint, FilterResults results) {
                    if (results != null && results.count > 0) {
                        notifyDataSetChanged();
                    } else {
                        notifyDataSetInvalidated();
                    }
                }
            };
        }
    }
}
