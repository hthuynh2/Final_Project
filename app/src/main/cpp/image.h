//
// Created by Hieu Huynh on 3/22/17.
//

#ifndef FINAL_PROJECT_IMAGE_H
#define FINAL_PROJECT_IMAGE_H
#include <stdlib.h>
#include <opencv2/core/core.hpp>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>

using namespace cv;
class Image{
public:
    Image();
    Image(unsigned int _width, unsigned int _height);
    Image(Mat& _mat);

    ~Image();

    double * operator()( int x,  int y);
    Image const & operator=(Image const & other);

    void convolve_with_gaussian(double sigma);
    unsigned int getHeight() const ;
    unsigned int getWidth() const ;

    double * get_pixel_ptr(){
        return pixel_ptr;
    }

private:
    unsigned int width;
    unsigned int height;
    double * pixel_ptr;


    int  _getLoc(unsigned int x, unsigned int y);
    void _copy(Image const & other);
    void _clear();
};

#endif //FINAL_PROJECT_IMAGE_H
