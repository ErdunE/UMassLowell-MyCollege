package com.example.mysmartcamera.mycamera.utils;

import android.os.Environment;
import android.util.Log;

import java.io.File;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Vector;


public class FileUtils {
    private static final String MAIN_DIR_NAME = "/aserbao";
    private static final String BASE_EXT = ".mp4";
    public  static final String VIDEO_PATH = Environment.getExternalStorageDirectory().getPath() + MAIN_DIR_NAME ;

    private SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy_MM_dd_HH_mm");
    private String currentFileName = "-";
    private String nextFileName;

    public FileUtils() {
    }

    public boolean requestSwapFile() {
        return requestSwapFile(false);
    }

    public boolean requestSwapFile(boolean force) {
        String fileName = getFileName();
        boolean isChanged = false;

        if (!currentFileName.equalsIgnoreCase(fileName)) {
            isChanged = true;
        }

        if (isChanged || force) {
            nextFileName = getSaveFilePath(fileName);
            return true;
        }

        return false;
    }

    public String getNextFileName() {
        return nextFileName;
    }

    private String getFileName() {
        String format = simpleDateFormat.format(System.currentTimeMillis());
        return format;
    }

    private String getSaveFilePath(String fileName) {
        currentFileName = fileName;
        StringBuilder fullPath = new StringBuilder();
        fullPath.append(getExternalStorageDirectory());

        fullPath.append(MAIN_DIR_NAME);
        fullPath.append(fileName);
        fullPath.append(BASE_EXT);

        String string = fullPath.toString();
        File file = new File(string);
        File parentFile = file.getParentFile();
        if (!parentFile.exists()) {
            parentFile.mkdirs();
        }

        return string;
    }



    /**
     * 获取sdcard路径
     */
    public static String getExternalStorageDirectory() {
        return Environment.getExternalStorageDirectory().getPath();
    }



    public static String getStorageMp4(String s){
        File file;
        String parent = Environment.getExternalStorageDirectory().getAbsolutePath() + "/aserbao";
        File file1 = new File(parent);
        if (!file1.exists()) {
            file1.mkdir();
        }
        file = new File(parent, s + ".mp4");

        return file.getPath();
    }
}
