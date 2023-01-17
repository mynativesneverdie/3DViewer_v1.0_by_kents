#include "parser.h"

void rotate(int len, float *src, float *res, double theta_x, double theta_y, double theta_z) {
    theta_x *= M_PI / 180;
    theta_y *= M_PI / 180;
    theta_z *= M_PI / 180;

    for (int k = 0; k < len; k += 3) {
        res[k + 0] = src[k + 0];
        res[k + 1] = src[k + 1] * cos(theta_x) - src[k + 2] * sin(theta_x);
        res[k + 2] = src[k + 1] * sin(theta_x) + src[k + 2] * cos(theta_x);

        res[k + 0] = res[k + 0] * cos(theta_y) - res[k + 2] * sin(theta_y);
        res[k + 2] = res[k + 0] * sin(theta_y) + res[k + 2] * cos(theta_y);

        res[k + 0] = res[k + 0] * cos(theta_z) - res[k + 1] * sin(theta_z);
        res[k + 1] = res[k + 0] * sin(theta_z) + res[k + 1] * cos(theta_z);
    }
    // printf("%f %f %f %lf\n", res[0],  res[1],  res[2], theta);
}


