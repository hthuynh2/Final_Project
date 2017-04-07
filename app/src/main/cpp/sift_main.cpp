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



#include <vector>
#include "image.h"
#include "octave.h"
#include "constant.h"
#include "sift.h"
using namespace cv;
using namespace std;


extern "C" {
void JNICALL
Java_com_example_hthieu_final_1project_MainActivity_createImg(JNIEnv *env, jobject instance,
                                                              jlong matAddrGr) {

    Mat& mGr  = *(Mat*)matAddrGr;
    Image  img(mGr);





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
    int p ;
    p = 0;



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