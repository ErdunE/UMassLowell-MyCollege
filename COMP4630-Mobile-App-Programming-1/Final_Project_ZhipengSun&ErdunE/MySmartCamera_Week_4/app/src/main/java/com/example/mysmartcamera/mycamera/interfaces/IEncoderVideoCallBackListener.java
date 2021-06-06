package com.example.mysmartcamera.mycamera.interfaces;


public interface IEncoderVideoCallBackListener {
    void success(String outputMeidaPath, float finalMediaTime);
    void failed();
}
