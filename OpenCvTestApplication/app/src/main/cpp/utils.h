//
// Created by GuaishouN on 2019/7/16.
//
#include "jni.h"
#include "android/bitmap.h"
#include "opencv2/opencv.hpp"
using namespace cv;
#ifndef OPENCVTESTAPPLICATION_UTILS_H
#define OPENCVTESTAPPLICATION_UTILS_H

//OPENCVTESTAPPLICATION_UTILS_H

extern "C"{
    void bitmap2Mat(JNIEnv *env, jobject bitmap,Mat* mat, bool needPremultiplyAlpha );
    void mat2Bitmap(JNIEnv *env, Mat mat , jobject bitmap, bool needPremultiplyAlpha);
    jobject createBimap(JNIEnv *env, Mat srcData,jobject config);
};
#endif