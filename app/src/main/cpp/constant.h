//
// Created by Hieu Huynh on 3/22/17.
//

#ifndef FINAL_PROJECT_CONSTANT_H
#define FINAL_PROJECT_CONSTANT_H

#include <math.h>



static double const K_CONST = (pow(2.0, 1.0/2.0)); // 2.0 = NUM_LEVEL_PER_OCT - 3
static double const INIT_SIGMA = sqrt(2);
static double const SIGMA = sqrt(2);
static int const NUM_OCT = 4;
static int const NUM_LEVEL_PER_OCT = 5;
static int const NUM_DOG_PER_OCT = NUM_LEVEL_PER_OCT-1;
static double const CONTRAST_THRES = 0.03;
static double const MAX_STEP = 5;




#endif //FINAL_PROJECT_CONSTANT_H
