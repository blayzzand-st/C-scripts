#include <stdio.h>
#include <math.h>
#include "for_lab11.h"

struct Parallellogram {
    double p1_x, p1_y;
    double p2_x, p2_y;
    double p3_x, p3_y;
    double p4_x, p4_y;
} figure;

int main() {

    figure.p1_x = -3;
    figure.p1_y = 11;
    figure.p2_x = 12;
    figure.p2_y = -4;
    figure.p3_x = 1;
    figure.p3_y = -7;
    figure.p4_x = -14;
    figure.p4_y = 8;

    double side1 = sqrt(pow((figure.p3_x - figure.p1_x), 2) + pow((figure.p3_y - figure.p1_y), 2));
    double side2 = sqrt(pow((figure.p2_x - figure.p1_x), 2) + pow((figure.p2_y - figure.p1_y), 2));
    double side1_x = figure.p3_x - figure.p1_x;
    double side1_y = figure.p3_y - figure.p1_y;
    double side2_x = figure.p2_x - figure.p1_x;
    double side2_y = figure.p2_y - figure.p1_y;

    double p = perimeter(side1, side2);
    double s = square(side1_x, side1_y, side2_x, side2_y);

    printf("%.2lf \n", p);
    printf("%.2lf \n", s);

    return 0;
}
