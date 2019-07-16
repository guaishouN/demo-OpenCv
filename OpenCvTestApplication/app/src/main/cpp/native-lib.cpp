
#include <vector>
#include "native-lib.h"
#define ER_ZHI_HUA 1
#define PENG_ZHANG 2
#define TI_QU_ID 3
#define DEFAULT_CARD_WIDTH 640
#define DEFAULT_CARD_HEIGHT 400
#define  FIX_IDCARD_SIZE Size(DEFAULT_CARD_WIDTH,DEFAULT_CARD_HEIGHT)
using namespace std;
extern "C" JNIEXPORT jobject JNICALL Java_com_example_opencvtestapplication_MainActivity_findIdNumber
        (JNIEnv * env, jobject mainActivity, jobject bitmap, jobject bitmap_configure,jint type){
        //将bitmap转化为矩阵
        Mat src_img;
        Mat dst_img;
        bitmap2Mat(env,bitmap,&src_img,0);
        //归一化 处理逻辑
        Mat dst;
        resize(src_img,dst,FIX_IDCARD_SIZE);
        //灰度化
        cvtColor(src_img,dst,COLOR_RGB2GRAY);
        //二值化
        threshold(dst,dst,100,255,THRESH_BINARY);
        if(type == ER_ZHI_HUA){
            return createBimap(env,dst,bitmap_configure);
        }
        //膨胀处理
        Mat erodeElement  = getStructuringElement(MORPH_RECT,Size(40,15));
        erode(dst,dst,erodeElement);
        if(type == PENG_ZHANG){
            return createBimap(env,dst,bitmap_configure);
        }
        //轮廓检测
        vector<vector<Point>> conturs;
        findContours(dst,conturs,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));
        //找出合适的矩形区
        vector<Rect> rects;
        for (int i = 0; i < conturs.size(); ++i) {
            Rect rect  = boundingRect(conturs.at(i));
            //根据经验找出较长的矩形
            if(rect.width > rect.height*10){
                rects.push_back(rect);
            }
        }
        //获取坐标最长的矩形区
        int lowPoint =0;
        Rect finalRect;
        for (int i = 0; i < rects.size(); ++i) {
            Rect rect = rects.at(i);
            Point point = rect.tl();
            if (point.y>lowPoint){
                lowPoint = point.y;
                finalRect = rect;
            }
        }
        //抠出身份证号码区
        dst_img = src_img(finalRect);

        //这里可以做内存回收 todo

        return createBimap(env,dst_img,bitmap_configure);
}