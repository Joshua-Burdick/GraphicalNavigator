#pragma once
#include "Config.h"
#include <math.h>

class MathController {
    public:
        static void rotatePoint(double a[3], double theta, double p[3]) {
            double temp[3];

            // Temp values for manipulating in calculations
            temp[0] = p[0];
            temp[1] = p[1];
            temp[2] = p[2];

            // Multiplying terms of individual vectors
            temp[0] = -a[2] * p[1] + a[1] * p[2];
            temp[1] = a[2] * p[0] - a[0] * p[2];
            temp[2] = -a[1] * p[0] + a[0] * p[1];

            // Computing each term of arbitrary axis rotation formula
            temp[0] *= sin(theta);
            temp[1] *= sin(theta);
            temp[2] *= sin(theta);

            temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
            temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
            temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

            temp[0] += cos(theta) * p[0];
            temp[1] += cos(theta) * p[1];
            temp[2] += cos(theta) * p[2];

            if (temp[1] < Y_ROT_MIN || temp[1] > Y_ROT_MAX) return;

            // Point becomes new point
            p[0] = temp[0];
            p[1] = temp[1];
            p[2] = temp[2];
        };

        static void crossProduct(double a[3], double b[3], double c[3]) {
            c[0] = a[1] * b[2] - a[2] * b[1];
            c[1] = a[2] * b[0] - a[0] * b[2];
            c[2] = a[0] * b[1] - a[1] * b[0];
        };

        static void normalize(double a[3]) {
            double norm;

            norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
            norm = sqrt(norm);

            a[0] /= norm;
            a[1] /= norm;
            a[2] /= norm;
        };
};