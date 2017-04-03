//
// Created by Hieu Huynh on 3/23/17.
//

#include "octave.h"
Octave::Octave(bool _dog, unsigned int _width, unsigned int _height){
    dog = _dog;
    width = _width;
    height = _height;

    if(_dog) {
        image_ptr = new Image*[NUM_DOG_PER_OCT];
        /*
        for (int i = 0 ; i < NUM_DOG_PER_OCT; i++){
            image_ptr[i] = new Image(width,height);
        }
         */
    }
    else {
        image_ptr = new Image*[NUM_LEVEL_PER_OCT];

        /*
        for (int i = 0 ; i < NUM_LEVEL_PER_OCT; i++){
            image_ptr[i] = new Image(width,height);
        }
         */
    }
}

Octave::~Octave(){
    _clear();
    image_ptr = NULL;
}


void Octave:: _clear(){
    if (image_ptr == NULL)
        return;
    if (dog){
        for (int i = 0 ; i < NUM_DOG_PER_OCT; i++){
            delete image_ptr[i];
        }
    }
    else{
        for (int i = 0 ; i < NUM_LEVEL_PER_OCT; i++){
            delete image_ptr[i];
        }
    }
    delete[] image_ptr;
}


Image* Octave::get_image(int index){
    return image_ptr[index];

}
void Octave::set_image(Image& img, int index){
    image_ptr[index] = &img;
    return;
}


double Octave::getScale() const {
    return scale;
}

void Octave::setScale(double scale) {
    Octave::scale = scale;
}

bool Octave:: isDog() const {
    return dog;
}