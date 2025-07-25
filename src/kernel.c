#include <stdio.h>
#include <math.h>

void euclidean_distance_c(
    double X_1[],
    double X_2[],
    double Y_1[],
    double Y_2[],
    double Z[],
    int length)
{
    for (int i = 0; i < length; i++)
    {
        double x_part = (X_2[i] - X_1[i]);
        x_part = x_part * x_part;
        double y_part = (Y_2[i] - Y_1[i]);
        y_part = y_part * y_part;
        Z[i] = sqrt(x_part + y_part);
    }
}