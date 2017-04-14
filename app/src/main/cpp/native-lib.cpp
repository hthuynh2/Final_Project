#include <jni.h>
#include <string>
#include <opencv2/core.hpp>
#include <cassert>
#include <cstring>
#include <jni.h>
#include <ctime>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <android/log.h>



//JNIEXPORT



extern "C" {
jstring
Java_com_example_hthieu_final_1project_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


jstring JNICALL
Java_com_example_hthieu_final_1project_MainActivity_validate(JNIEnv *env, jobject instance,
                                                             jlong matAddrGr, jlong matAddrRgba) {
    cv::Rect();
    cv::Mat();
    std::string hello2 = "Hello from validate";
    return env->NewStringUTF(hello2.c_str());
}


}
