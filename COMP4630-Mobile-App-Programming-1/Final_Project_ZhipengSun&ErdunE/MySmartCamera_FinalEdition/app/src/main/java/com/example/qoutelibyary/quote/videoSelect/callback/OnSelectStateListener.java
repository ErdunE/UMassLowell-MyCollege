package com.example.qoutelibyary.quote.videoSelect.callback;

public interface OnSelectStateListener<T> {
        void OnSelectStateChanged(boolean state, T file);
    }