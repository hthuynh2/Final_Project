//
// Created by Hieu Huynh on 3/22/17.
//


#include <cassert>
#include <cstring>
#include <jni.h>
#include <ctime>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <android/log.h>



#include <vector>
#include "image.h"
#include "octave.h"
#include "constant.h"
#include "sift.h"
using namespace cv;
using namespace std;

extern "C" {

JNIEXPORT jint JNICALL
Java_com_example_hthieu_final_1project_MainActivity_checkImg(JNIEnv *env, jobject instance,
                                                             jlong matAddrGr, jlong descAddr0,
                                                             jlong descAddr1, jlong descAddr2,
                                                             jlong descAddr3, jlong descAddr4,
                                                             jlong descAddr5, jlong descAddr6,
                                                             jlong descAddr7, jlong descAddr8,
                                                             jlong descAddr9, jlong descAddr10,
                                                             jlong descAddr11, jlong descAddr12,
                                                             jlong descAddr13, jlong descAddr14,
                                                             jlong descAddr15, jlong descAddr16,
                                                             jlong descAddr17, jlong descAddr18,
                                                             jlong descAddr19, jlong descAddr20) {

    // TODO

    int num = 3;
    Mat& mGr  = *(Mat*)matAddrGr;
    Mat desc_query ;
    Mat& desc0 =  *(Mat*) descAddr0;
    Mat& desc1 =  *(Mat*) descAddr1;
    Mat& desc2 =  *(Mat*) descAddr2;

    vector<KeyPoint> v;

    Ptr<BRISK> detector = BRISK::create();
    detector->detectAndCompute(mGr, NULL, v, desc_query);

    BFMatcher matcher(NORM_HAMMING);

    std::vector< std::vector<DMatch> > matches_vector;
    std::vector< std::vector<DMatch> > good_matches_vector;


    if(desc_query.empty())
        return -1;

    std::vector<DMatch>  matches0;
    std::vector<DMatch>  matches1;
    std::vector<DMatch>  matches2;

    //matcher.match( desc_query, desc_source, matches );
    matcher.match( desc_query, desc0, matches0 );
    matcher.match( desc_query, desc1, matches1 );
    matcher.match( desc_query, desc2, matches2);

    matches_vector.push_back(matches0);
    matches_vector.push_back(matches1);
    matches_vector.push_back(matches2);


//    matches_vector[0] = matches0;
//    matches_vector[1] = matches1;
//    matches_vector[2] = matches2;


//    matcher.match( desc_query, desc0, matches_vector[0] );
//    matcher.match( desc_query, desc1, matches_vector[1] );
//    matcher.match( desc_query, desc2, matches_vector[2] );

    for (int i = 0; i <num; i ++){
        std::vector<DMatch>  good_match;

        if (matches_vector[i].size() == 0 ) {
            good_matches_vector.push_back(good_match);
            continue;
        }

        double max_dist = 0.0;
        double min_dist = 100.0;
        //-- Quick calculation of max and min distances between keypoints
        for (int j = 0 ; j < matches_vector[i].size(); j ++){
            double dist = (matches_vector[i])[j].distance;
            if(max_dist < dist)
                max_dist = dist;
            if (min_dist > dist && dist >=0){
                min_dist = dist;
            }
        }


        if(min_dist >= 50){
            good_matches_vector.push_back(good_match);
            continue;
        }

        double threshold = 3 * min_dist;

        if(min_dist > 25)
            threshold = 75;
        else if (min_dist*2 >= max_dist)
            threshold = min_dist * 1.1;
        else if(min_dist*3 >= max_dist)
            threshold = threshold * 2.4;



        for (int j= 0 ; j < matches_vector[i].size(); j ++){
            if (matches_vector[i][j].distance < threshold)
                good_match.push_back(matches_vector[i][j]);
            //    good_matches_vector[i].push_back( matches_vector[i][j]);
        }
        good_matches_vector.push_back(good_match);
    }


    int max_idx = -1;
    long max_size = -1;

    if(good_matches_vector.size() == 0 )
        return -1;

    for(int i = 0; i < num; i ++){
        int temp = (int) good_matches_vector[i].size();
        if( temp > max_size){
            max_size = good_matches_vector[i].size();
            max_idx  = i;
        }
    }
    if(max_size <= 10)
        return -1;
    return  max_idx;
}


jint JNICALL
Java_com_example_hthieu_final_1project_MainActivity_callcheckImg(JNIEnv *env, jobject thisobject,
                                                                 jint vec_num) {

    // TODO

    // Find the required classes
    jclass thisclass = env->GetObjectClass(thisobject);
    jclass matclass = env->FindClass("org/opencv/core/Mat");

    // Get methods and fields
    jmethodID getPtrMethod = env->GetMethodID(matclass, "getNativeObjAddr", "()J");
    jfieldID mgrayfieldid = env->GetFieldID(thisclass, "mGray", "Lorg/opencv/core/Mat;");
    jfieldID bufimgsfieldid = env->GetFieldID(thisclass, "bufImgs", "[Lorg/opencv/core/Mat;");


    // Let's start: Get the fields
    jobject mgray = env->GetObjectField(thisobject, mgrayfieldid);
    jobjectArray bufimgsArray = (jobjectArray)env->GetObjectField(thisobject, bufimgsfieldid);

    // Convert the array
    cv::Mat nativeBufImgs[vec_num];
    for (int i = 0; i < vec_num; i++)
        nativeBufImgs[i] = *(cv::Mat*)env->CallLongMethod(env->GetObjectArrayElement(bufimgsArray, i), getPtrMethod);

    // Get the address for mRgba
    cv::Mat* mgrayptr = (cv::Mat*)env->CallLongMethod(mgray, getPtrMethod);

    // We're done! Call the method and return!
    //
    // return nativeCode(mgrayptr, nativeBufImgs);
    return 0;
}



void JNICALL
Java_com_example_hthieu_final_1project_MainActivity_getDesc(JNIEnv *env, jobject instance,
                                                            jlong addrImg, jlong addDesc) {


    Mat& mGr  = *(Mat*)addrImg;
    Mat& desc =  *(Mat*) addDesc;

    vector<KeyPoint> v;
    Ptr<BRISK> detector = BRISK::create();

    detector->detectAndCompute(mGr, NULL, v, desc);
    return;
}



jboolean JNICALL
Java_com_example_hthieu_final_1project_MainActivity_createImg(JNIEnv *env, jobject instance,
                                                              jlong matAddrGr, jlong addrRgba, jlong desc) {

    Mat& mGr  = *(Mat*)matAddrGr;
    //Image  img(mGr);
    __android_log_print(ANDROID_LOG_DEBUG, "MainActivity", "HELOOOOOOOOOOOOOOOO ");

    __android_log_write(ANDROID_LOG_DEBUG, "MainActivity", "asdasd");

    Mat& mRgb = *(Mat*)addrRgba;
    Mat desc_query ;
    Mat desc_source;

    Mat& desc_source1 =  *(Mat*) desc;
    vector<KeyPoint> v;
    vector<KeyPoint> v1;


    Ptr<BRISK> detector = BRISK::create();

    detector->detectAndCompute(mGr, NULL, v, desc_query);
    detector->detectAndCompute(mRgb, NULL, v1, desc_source);


    BFMatcher matcher(NORM_HAMMING);
    std::vector< DMatch > matches;
    std::vector< DMatch > good_matches;

    if(desc_query.empty() || desc_source.empty())
        return (jboolean) false;


    //matcher.match( desc_query, desc_source, matches );
    matcher.match( desc_query, desc_source1, matches );



    if (matches.size() == 0 )
        return (jboolean) false;

    double max_dist = 0.0;
    double min_dist = 100.0;
    //-- Quick calculation of max and min distances between keypoints
    for (int i = 0 ; i < matches.size(); i ++){
        double dist = matches[i].distance;
        if(max_dist < dist)
            max_dist = dist;
        if (min_dist > dist && dist >=0){
            min_dist = dist;
        }
    }

    if(min_dist >= 50)
        return (jboolean) false;


    double threshold = 3 * min_dist;

    if(min_dist > 25)
        threshold = 75;
    else if (min_dist*2 >= max_dist)
        threshold = min_dist * 1.1;
    else if(min_dist*3 >= max_dist)
        threshold = threshold * 2.4;


    for (int i = 0 ; i < matches.size(); i ++){
        if (matches[i].distance < threshold)
            good_matches.push_back( matches[i]);
    }
    __android_log_print(ANDROID_LOG_DEBUG, "NDK_TAG", "test int = %d", (int)good_matches.size());

    int good_matches_size = good_matches.size();
    double match_percentage = 100.0*matches.size()/v.size();
    double good_match_percentage = 100.0*good_matches_size/matches.size();

    //????
    if (good_matches_size >= 10) {
        return (jboolean )true;
    }
    return (jboolean )false;



/*
    Ptr<FeatureDetector> detector = FastFeatureDetector::create(50);
    detector->detect(mGr, v);
    for (unsigned int i = 0; i < v.size(); i++) {
        const KeyPoint& kp = v[i];
        circle(mRgb, Point(kp.pt.x, kp.pt.y), 10, Scalar(255,0,0,255));
        circle(mGr, Point(kp.pt.x, kp.pt.y), 10, Scalar(255,0,0,255));
    }
*/



//    add_library( lib_opencv SHARED IMPORTED )
    //   set_target_properties(lib_opencv PROPERTIES IMPORTED_LOCATION ${pathToProject}/app/src/main/jniLibs/${ANDROID_ABI}/libopencv_java3.so)


    //   test_img.convolve_with_gaussian(sqrt(2));
//    mGr = Mat(test_img.getHeight(), test_img.getWidth(), test_img.get_pixel_ptr());


    // Mat_<double> img_mat(height, width, pixel_ptr);

// Record end time
/*
    clock_t begin = clock();

    Sift s(img);
    s.find_keys();
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
*/
    /*b
     Mat img_mat(img.getHeight(), img.getWidth(),CV_64F, img.get_pixel_ptr());
     Mat base_img_mat;


     resize(img_mat, base_img_mat, Size(0,0), 2, 2, CV_INTER_LINEAR);
     //http://docs.opencv.org/2.4/modules/imgproc/doc/geometric_transformations.html?highlight=resize#resize
     Image * baseImg = new Image(base_img_mat);
 */

    // GaussianBlur(mGr, mGr, Size(0,0), 5,5 , BORDER_CONSTANT);
    //   GaussianBlur(img_mat, mGr , Size(0,0), 5, 5, BORDER_CONSTANT);



    /*
    for (unsigned int i = 0 ; i <test_img.getWidth(); i++){
        for (unsigned int j = 0; j < test_img.getHeight(); j ++){
            unsigned char temp = mGr.at<uchar>(j,i);
            double temp1 = *test_img(i,j);
            if(temp1  != temp)
                count++;
        }
    }*/
    // int p ;
    //p = 0;



}


}










/*
 *
 *          Test if gaussianBlur can change image or not?
 *
 *  Mat img_mat(480, 640,CV_64F, test_img.get_pixel_ptr());
    GaussianBlur(img_mat, img_mat , Size(0,0), 5, 5, BORDER_CONSTANT);
       int count = 0;
    for (unsigned int i = 0 ; i <test_img.getWidth(); i++){
        for (unsigned int j = 0; j < test_img.getHeight(); j ++){
            double temp = *test_img(i,j);
            double temp1 = img_mat.at<double>(j,i);
            if(temp1 != temp)
                count++;
        }
    }
 *
 *
 *
 */