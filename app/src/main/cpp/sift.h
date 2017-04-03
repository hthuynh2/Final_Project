//
// Created by Hieu Huynh on 3/22/17.
//

#ifndef FINAL_PROJECT_SIFT_H
#define FINAL_PROJECT_SIFT_H

#include "constant.h"
#include "octave.h"
#include "key.h"
#include <vector>

using namespace std;

class Sift {
public:
    Sift(Image &_baseImg);


    ~Sift();

private:

    Image *baseImg;
    Octave **octave_arrays;
    Octave **dog_arrays;
    vector<Key> keys_vec;


    void create_oct_pyramid();

    void create_dog_pyramid();

    void img_init(Image &img);

    void find_keys();

    bool is_Max_Min(int x, int y, int oct_idx, int dog_level);

    void checkContrast(int x, int y, int oct_idx, int dog_level, Key **key);
    void calculate_location(int x, int y, int oct_idx, int dog_level, double& x_offset, double& y_offset, double& sig_offset);
    void getDerivative(int x, int y, int oct_idx, int dog_level, double (&d_array)[3], double (&h_array)[3][3]);
    bool checkEdge( );







    };

#endif //FINAL_PROJECT_SIFT_H
