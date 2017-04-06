//
// Created by Hieu Huynh on 3/24/17.
//

#ifndef FINAL_PROJECT_KEY_H
#define FINAL_PROJECT_KEY_H

class Key{
public:

    Key() { }
    Key(double x_d, double y_d, int x_i, int y_i, int oct_idx, int dog_level, double sigma) : x_d(x_d),
                                                                                           y_d(y_d),
                                                                                           x_i(x_i),
                                                                                           y_i(y_i),
                                                                                           oct_idx(oct_idx),
                                                                                           dog_level(
                                                                                                   dog_level),
                                                                                           sigma(sigma) { }


private:
    double  x_d;
    double  y_d;
    int     x_i;
    int     y_i;
    int     oct_idx;
    int     dog_level;
    double     sigma;
};

#endif //FINAL_PROJECT_KEY_H
