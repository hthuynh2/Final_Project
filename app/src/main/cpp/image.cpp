//
// Created by Hieu Huynh on 3/22/17.
//

#include "image.h"
using namespace std;
using namespace cv;

Image::Image()
{
    pixel_ptr = new double;
    width = 1;
    height = 1;
}

Image::Image(unsigned int _width, unsigned int _height){
    pixel_ptr = new double[_width * _height];
    width = _width;
    height = _height;
}

//NOT SURE!!!
Image::Image(Mat &_mat) {
    width = (unsigned int) _mat.cols;
    height = (unsigned int) _mat.rows;
    pixel_ptr = new double[width * height];

    unsigned char * temp = _mat.data;
    for (int i = 0; i < width*height; i++){
        pixel_ptr[i] =  temp[i];
    }
}

void Image::_clear()
{
    if(pixel_ptr != NULL)
        delete[] pixel_ptr;
    pixel_ptr = NULL;
    width = 0;
    height = 0;
}

Image::~Image(){
    _clear();
}


void Image::_copy(Image const & other)
{
    width = other.width;
    height = other.height;
    pixel_ptr = new double[height * width];
    for (unsigned int y = 0; y < height; y++)
    {
        for (unsigned int x = 0; x < width; x++)
        {
            pixel_ptr[_getLoc(x,y)] = other.pixel_ptr[_getLoc(x,y)];
        }
    }
}


double * Image::operator()( int x,  int y)
{
    if(x >=0 && x <width && y>=0 && y<height)
        return & pixel_ptr[_getLoc(x,y)];
    return NULL;
}



Image const & Image::operator=(Image const & other)
{
    if (this != &other)
    {
        _clear();
        _copy(other);
    }
    return *this;
}


void Image::convolve_with_gaussian(double sigma){
    int kernel_size = (int) floor(3*sigma -1);

    if (kernel_size % 2 == 0)
        kernel_size ++;

    Mat img_mat(height, width,CV_64F, pixel_ptr);


    GaussianBlur(img_mat, img_mat , Size(kernel_size,kernel_size), sigma, sigma, BORDER_CONSTANT);


   // GaussianBlur( img_mat, temp_mat, Size( 5, 5 ), 0, 0 );

/*
    int kernel_x_center = kernel_size/2 +1;
    int kernel_y_center = kernel_size/2 +1;

    for(unsigned int img_x = 0; img_x <width; img_x ++){
        for(unsigned int img_y = 0; img_y<height; img_y++){
            int sum = 0;
            for (unsigned int ker_x = 0; ker_x <  kernel_size; ker_x++){
                for (unsigned int ker_y = 0; ker_y< kernel_size; ker_y++){
                    if (((img_x + ker_x - kernel_x_center < 0) || ((img_x + ker_x - kernel_x_center) >= width)))
                        continue;
                    else if ((img_y + ker_y - kernel_y_center < 0) || (img_y + ker_y - kernel_y_center >= height))
                        continue;
                    else{
                        sum += pixel_ptr[_getLoc(img_x + ker_x - kernel_x_center, img_y + ker_y - kernel_y_center)] * kernel[ker_x*kernel_size + ker_y];
                    }
                }
            }
            pixel_ptr[_getLoc(img_x,img_y)] = sum;
        }
    }
*/

}
//buildPyramid
unsigned int Image::getWidth() const {
    return width;
}

unsigned int Image::getHeight() const {
    return height;
}

int  Image::_getLoc(unsigned int x, unsigned int y){
    return y*width + x;
}

