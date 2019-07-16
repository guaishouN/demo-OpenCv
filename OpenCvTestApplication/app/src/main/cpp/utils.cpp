//
// Created by GuaishouN on 2019/7/16.
//

#include <opencv2/imgproc/types_c.h>
#include "utils.h"

    void bitmap2Mat(JNIEnv *env, jobject bitmap,Mat* mat, bool needPremultiplyAlpha){

        AndroidBitmapInfo bitmap_info;
        void *pPixel = NULL;
        Mat &taget = *mat;
        AndroidBitmap_getInfo(env, bitmap, &bitmap_info);

        AndroidBitmap_lockPixels(env, bitmap, &pPixel);

        //判断传入的图片是什么类型
        if (bitmap_info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {//32
            //对应opncv Mat 类型  CV_8UC4
            cv::Mat temp(bitmap_info.height, bitmap_info.width, CV_8UC4, pPixel);
            temp.copyTo(taget);


        } else if (bitmap_info.format == ANDROID_BITMAP_FORMAT_RGB_565) {//16
            //对应opncv Mat 类型  CV_8UC2

            cv::Mat temp(bitmap_info.height, bitmap_info.width, CV_8UC2, pPixel);

            cv::cvtColor(temp, taget, CV_BGRA2BGR565);

        }


        AndroidBitmap_unlockPixels(env, bitmap);
    }

    void mat2Bitmap(JNIEnv *env, Mat mat , jobject bitmap, bool needPremultiplyAlpha =0){
        AndroidBitmapInfo bitmap_info;
        void *pPixel = NULL;
        AndroidBitmap_lockPixels(env, bitmap, &pPixel);
        AndroidBitmap_getInfo(env, bitmap, &bitmap_info);
        //判断传入的图片是什么类型
        if (bitmap_info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {//32
            cv::Mat tmp(bitmap_info.height, bitmap_info.width, CV_8UC4, pPixel);
            //对应opncv Mat 类型  CV_8UC4
            if (mat.type() == CV_8UC4) {
                //对应bitmap   RGBA_8888
                mat.copyTo(tmp);

            } else if (mat.type() == CV_8UC2) {
                //对应bitmap   RGB_565
                cv::cvtColor(mat, tmp, CV_BGR5652BGRA);

            } else if (mat.type() == CV_8UC1) {
                //单通道 0-255 的灰度图
                cv::cvtColor(mat, tmp, CV_GRAY2BGRA);
            }

        } else if (bitmap_info.format == ANDROID_BITMAP_FORMAT_RGB_565) {//16
            cv::Mat tmp(bitmap_info.height, bitmap_info.width, CV_8UC2, pPixel);
            //对应opncv Mat 类型  CV_8UC2
            if (mat.type() == CV_8UC4) {
                //对应bitmap   RGBA_8888
                cv::cvtColor(mat, tmp, CV_BGRA2BGR565);
            } else if (mat.type() == CV_8UC2) {
                //对应bitmap   RGB_565
                mat.copyTo(tmp);

            } else if (mat.type() == CV_8UC1) {
                //单通道 0-255 的灰度图
                cv::cvtColor(mat, tmp, CV_GRAY2BGR565);
            }

        }
        AndroidBitmap_unlockPixels(env, bitmap);
    }



    jobject createBimap(JNIEnv *env, Mat srcData,jobject config){
        jclass java_bitmap_class = (jclass)env->FindClass("android/graphics/Bitmap");
        jmethodID mid = env->GetStaticMethodID(java_bitmap_class,
                                               "createBitmap",
                                               "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");
        jobject bitmap = env->CallStaticObjectMethod(java_bitmap_class,
                mid,
                srcData.cols,
                srcData.rows,
                config);
         mat2Bitmap(env,srcData,bitmap,0);
        return bitmap;
    }
