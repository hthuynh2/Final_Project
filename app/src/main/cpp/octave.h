//
// Created by Hieu Huynh on 3/23/17.
//

#ifndef FINAL_PROJECT_OCTAVE_H
#define FINAL_PROJECT_OCTAVE_H

#include "constant.h"
#include "image.h"
class Octave{
public:

    Octave(bool _dog,unsigned int _width, unsigned int _height);

    ~Octave();

    double getScale() const ;

    void setScale(double scale);

    bool isDog() const ;


    unsigned int getWidth() const {
        return width;
    }


    unsigned int getHeight() const {
        return height;
    }

    void set_image(Image& img, int index);
    Image* get_image(int index);

private:
    Image ** image_ptr;
    double scale;
    bool dog;
    unsigned int width;
    unsigned int height;

    void _clear();
};



#endif //FINAL_PROJECT_OCTAVE_H
