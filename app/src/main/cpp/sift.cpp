//
// Created by Hieu Huynh on 3/22/17.
//

#include "sift.h"




//
//if (matches.size() == 0 )
//return (jboolean) false;
//
//double max_dist = 0.0;
//double min_dist = 100.0;
////-- Quick calculation of max and min distances between keypoints
//for (int i = 0 ; i < matches.size(); i ++){
//double dist = matches[i].distance;
//if(max_dist < dist)
//max_dist = dist;
//if (min_dist > dist && dist >=0){
//min_dist = dist;
//}
//}
//
//if(min_dist >= 50)
//return (jboolean) false;
//
//
//double threshold = 3 * min_dist;
//
//if(min_dist > 25)
//threshold = 75;
//else if (min_dist*2 >= max_dist)
//threshold = min_dist * 1.1;
//else if(min_dist*3 >= max_dist)
//threshold = threshold * 2.4;
//
//
//for (int i = 0 ; i < matches.size(); i ++){
//if (matches[i].distance < threshold)
//good_matches.push_back( matches[i]);
//}
//
//int good_matches_size = good_matches.size();
//double match_percentage = 100.0*matches.size()/v.size();
//double good_match_percentage = 100.0*good_matches_size/matches.size();
//
////????
//if (good_matches_size >= 10) {
//return (jboolean )true;
//}
//return (jboolean )false;







Sift::Sift(Image& _baseImg){

    octave_arrays = new Octave*[NUM_OCT];
    dog_arrays = new Octave*[NUM_OCT];
    baseImg = NULL;
    img_init(_baseImg);
    create_oct_pyramid();
    create_dog_pyramid();

}

Sift::~Sift(){
    for (int i = 0 ; i < NUM_OCT; i ++){
        delete octave_arrays[i];
        delete dog_arrays[i];
    }
    delete [] octave_arrays;
    delete [] dog_arrays;
}



void Sift::create_oct_pyramid(){
    octave_arrays[0] = new Octave(false,baseImg->getWidth(), baseImg->getHeight());

    octave_arrays[0]->set_image(*baseImg,0);    //Not sure!!

    double sigma = SIGMA;
    for (int oct_idx = 0; oct_idx < NUM_OCT; oct_idx++){
        for (int level_idx = 1; level_idx < NUM_LEVEL_PER_OCT; level_idx++){
            sigma = sigma * K_CONST;        //Not sure!!

            Image * temp_img = octave_arrays[oct_idx]->get_image(level_idx-1);

            Mat img_mat(temp_img->getHeight(), temp_img->getWidth(),CV_64F, temp_img->get_pixel_ptr());
            Mat filtered_mat;
            GaussianBlur(img_mat, filtered_mat , Size(0,0), sigma, sigma, BORDER_CONSTANT);

            Image * filtered_img = new Image(filtered_mat);
            octave_arrays[oct_idx]->set_image(*filtered_img,level_idx);

        }

        if(oct_idx+1< NUM_OCT){
            //Create base for next octave
            Image * temp_img = octave_arrays[oct_idx]->get_image(NUM_LEVEL_PER_OCT - 3); // Not sure!!
            Mat temp_img_mat(temp_img->getHeight(), temp_img->getWidth(),CV_64F, temp_img->get_pixel_ptr());
            Mat new_base_mat;

            resize(temp_img_mat, new_base_mat, Size(0,0), 0.5,0.5,INTER_LINEAR);

            Image * new_base_img = new Image(new_base_mat);

            octave_arrays[oct_idx+1] = new Octave(false,new_base_img->getWidth(), new_base_img->getHeight());
            octave_arrays[oct_idx+1]->set_image(*new_base_img, 0);
        }
        sigma = SIGMA;      //Not sure!!
    }

}

void Sift::create_dog_pyramid(){
    for (int oct_idx = 0; oct_idx < NUM_OCT; oct_idx++){
        dog_arrays[oct_idx] = new Octave(true, octave_arrays[oct_idx]->getWidth(), octave_arrays[oct_idx]->getHeight());
        for (int dog_level = 0 ; dog_level < NUM_DOG_PER_OCT; dog_level++){
            Image * img_src1 = octave_arrays[oct_idx]->get_image(dog_level);
            Image * img_src2 = octave_arrays[oct_idx]->get_image(dog_level+1);

            Mat mat_scr1(img_src1->getHeight(), img_src2->getWidth(), CV_64F,img_src1->get_pixel_ptr());
            Mat mat_scr2(img_src2->getHeight(), img_src2->getWidth(), CV_64F,img_src2->get_pixel_ptr());

            Mat mat_des;
            subtract(mat_scr2,mat_scr1, mat_des);
            Image * dog = new Image(mat_des);
            dog_arrays[oct_idx]->set_image(*dog,dog_level);
        }
    }

}

//Filter with gaussian with sigma = 0.5 to prevent alaising when double the size
//Double the size
//Filter with gaussian with sigma = ??? --> Base image
void Sift::img_init(Image& img){
    Mat img_mat(img.getHeight(), img.getWidth(),CV_64F, img.get_pixel_ptr());
    Mat resize_mat;
    Mat filtered_mat;
    Mat base_mat;


    /*
    //filter by sigma = 0.5
    GaussianBlur(img_mat, filtered_mat , Size(0,0), 0.5, 0.5, BORDER_CONSTANT);

    //http://docs.opencv.org/2.4/modules/imgproc/doc/geometric_transformations.html?highlight=resize#resize
    resize(filtered_mat, resize_mat, Size(0,0), 2, 2, CV_INTER_LINEAR);

    GaussianBlur(resize_mat, base_mat, Size(0,0),1.0,1.0, BORDER_CONSTANT  ); // not sure about sigma = 1.0???
    baseImg = new Image(base_mat);
    */

    //OR
    GaussianBlur(img_mat, filtered_mat , Size(0,0), 1, 1, BORDER_CONSTANT);
    resize(filtered_mat, base_mat, Size(0,0), 2,2,INTER_LINEAR);
    Image * temp_img = new Image(base_mat);
//    baseImg = new Image(base_mat);
    baseImg = temp_img;

}


void Sift::find_keys(){

    double prelim_contr_thr = 0.5 * CONTRAST_THRES / (NUM_DOG_PER_OCT-2);

    for (int oct_idx = 0; oct_idx < NUM_OCT; oct_idx++){
        for (int dog_level = 1; dog_level < NUM_DOG_PER_OCT-1; dog_level++){
            for (int y = 1; y < dog_arrays[oct_idx]->getHeight()-1; y++){
                for (int x = 1; x < dog_arrays[oct_idx]->getWidth() -1 ; x++){
                    double pixel_val = *((*(dog_arrays[oct_idx]->get_image(dog_level)))(x,y));
                    if (abs(pixel_val) <= prelim_contr_thr)
                        continue;

                    Key * key = NULL;
                    if (is_Max_Min(x,y, oct_idx, dog_level)) {
                        checkContrast(x, y, oct_idx, dog_level, &key);
                        if (key != NULL) {
                            if (!checkEdge(x,y, oct_idx, dog_level)) {
                                keys_vec.push_back(*key);
                            }
                            else {
                                delete key;
                                key = NULL;
                            }
                        }
                    }
                }
            }
        }
    }

}

bool Sift::checkEdge(int x, int y, int oct_idx, int dog_level ){

    double val, dxx, dyy, dxy;
    Image* cur_img = dog_arrays[oct_idx]->get_image(dog_level);

    val = *(*cur_img)(x,y) ;
    dxx = (*((*cur_img)(x+1,y)) - *((*cur_img)(x-1,y))) - 2.0*val;
    dyy = (*((*cur_img)(x,y+1)) - *((*cur_img)(x,y-1))) - 2.0*val;
    dxy = (*((*cur_img)(x+1,y+1)) - *((*cur_img)(x-1,y+1)) - *((*cur_img)(x+1,y-1)) + *((*cur_img)(x-1,y-1)))/4.0;


    double tr = dxx + dyy;
    double det = dxx * dyy - dxy * dxy;

    double temp = 11.0*11.0/10.0;
    double temp1 = tr * tr / det;
    if( det <= 0 )
        return true;
    if( temp1< temp)
        return false;


    return true;
}

void Sift::checkContrast(int x, int y, int oct_idx, int dog_level, Key** key){
    int step = 0;

    double x_offset, y_offset, sig_offset ;
    x_offset = y_offset = sig_offset = 0;

    while(step < MAX_STEP-1){
        calculate_location(x, y, oct_idx, dog_level, x_offset, y_offset, sig_offset);
        if(x_offset > 0.5 && y_offset>0.5 && sig_offset > 0.5)
            break;
        x = x + (int)round(x_offset);
        y = y + (int)round(y_offset);
        dog_level = dog_level + (int)round(sig_offset);

        if( dog_level < 1  ||
            dog_level > NUM_DOG_PER_OCT-2  ||
            x < 1  ||
            y < 1  ||
            x >= dog_arrays[oct_idx]->getWidth() - 1  ||
            y >= dog_arrays[oct_idx]->getWidth() - 1 )
        {
            return ;
        }
        step ++;
    }
    if(step == 0)
        return;

    Image* cur_img = dog_arrays[oct_idx]->get_image(dog_level);
    Image* above_img = dog_arrays[oct_idx]->get_image(dog_level+1);
    Image* below_img = dog_arrays[oct_idx]->get_image(dog_level-1);


    double dx = (*((*cur_img)(x+1,y)) - *((*cur_img)(x-1,y)))/2.0 ;
    double dy = (*((*cur_img)(x,y+1)) - *((*cur_img)(x,y-1)))/2.0 ;
    double ds = (*((*above_img)(x,y)) - *((*below_img)(x,y)))/2.0 ;

    double d[3] ={dx,dy,ds};
    double t[3] = {x_offset, y_offset, sig_offset};

    double contr = 0;
    for (int i = 0 ; i< 3; i++) {
        contr += t[i] * d[i];
    }
    contr = (*(*cur_img)(x,y)) + contr/2.0;

    if(abs(contr) < CONTRAST_THRES)
        return;

    double x_d = (x + x_offset) * pow(2.0,oct_idx);     //Not sure!!
    double y_d = (y + y_offset) * pow(2.0,oct_idx);     //Not sure!!


    Key * temp = new Key(x_d, y_d, x, y, oct_idx, dog_level, sig_offset);
    *key = temp;

    return;
}



void Sift::calculate_location(int x, int y, int oct_idx, int dog_level, double& x_offset, double& y_offset, double& sig_offset){
    double d_array [3];
    double h_array[3][3];

    getDerivative(x,y,oct_idx, dog_level, d_array, h_array);

    Mat mat_h(3,3,CV_64FC1,h_array);

    invert(mat_h, mat_h, CV_SVD);

    Mat mat_d(3,1,CV_64FC1,d_array);
    Mat mat_desc;

    gemm(mat_h,mat_d,-1,NULL,0, mat_desc);

    x_offset = mat_desc.at<double>(0,0);
    x_offset = mat_desc.at<double>(1,0);
    x_offset = mat_desc.at<double>(2,0);

}


void Sift::getDerivative(int x, int y, int oct_idx, int dog_level, double (&d_array)[3], double (&h_array)[3][3]){

    Image* cur_img = dog_arrays[oct_idx]->get_image(dog_level);
    Image* above_img = dog_arrays[oct_idx]->get_image(dog_level+1);
    Image* below_img = dog_arrays[oct_idx]->get_image(dog_level-1);
    double cur_pixel = *((*cur_img)(x,y));

    double dx = (*((*cur_img)(x+1,y)) - *((*cur_img)(x-1,y)))/2.0 ;
    double dy = (*((*cur_img)(x,y+1)) - *((*cur_img)(x,y-1)))/2.0 ;
    double ds = (*((*above_img)(x,y)) - *((*below_img)(x,y)))/2.0 ;

    d_array[0] = dx;
    d_array[1] = dy;
    d_array[2] = ds;

    double dxx = dx*2.0 - 2*cur_pixel;
    double dyy = dy*2.0 - 2*cur_pixel;
    double dss = ds*2.0 - 2*cur_pixel;
    double dxy = (*((*cur_img)(x+1,y+1)) - *((*cur_img)(x-1,y+1)) - *((*cur_img)(x+1,y-1)) + *((*cur_img)(x-1,y-1)))/4.0;
    double dxs = (*((*above_img)(x+1,y)) - *((*above_img)(x-1,y)) - *((*below_img)(x+1,y)) + *((*below_img)(x-1,y)))/4.0;
    double dys = (*((*above_img)(x,y+1)) - *((*above_img)(x,y-1)) - *((*below_img)(x,y+1)) + *((*below_img)(x,y-1)))/4.0;

    h_array[0][0] = dxx;
    h_array[0][1] = dxy;
    h_array[0][2] = dxs;
    h_array[1][0] = dxy;
    h_array[1][1] = dyy;
    h_array[1][2] = dys;

    h_array[2][0] = dxs;
    h_array[2][1] = dys;
    h_array[2][2] = dss;

    return ;
}



bool Sift::is_Max_Min(int x, int y, int oct_idx, int dog_level ){

    double pixel_val = *((*(dog_arrays[oct_idx]->get_image(dog_level)))(x,y));

    if(pixel_val > 0){
        for (int k = -1; k <2; k ++){
            Image *temp = dog_arrays[oct_idx]->get_image(dog_level+k);
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if((pixel_val < *((*temp)(x+i,y+j))) && (i | k | j) != 0)    //Not sure??
                        return false;
                }
            }
        }
    }
    else{
        for (int k = -1; k <2; k ++){
            Image *temp = dog_arrays[oct_idx]->get_image(dog_level+k);
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if((pixel_val > *((*temp)(x+i,y+j))) && (i | k | j) != 0)    //Not sure??
                        return false;
                }
            }
        }
    }

    return true;
}




