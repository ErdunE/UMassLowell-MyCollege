package com.example.qoutelibyary.quote.videoSelect.callback;

import com.example.qoutelibyary.quote.videoSelect.beans.BaseFile;
import com.example.qoutelibyary.quote.videoSelect.beans.Directory;

import java.util.List;


public interface FilterResultCallback<T extends BaseFile> {
    void onResult(List<Directory<T>> directories);
}
