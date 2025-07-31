// This file is to prove correctness of the C implementation
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include "kernel.c"

#define LENGTH 4

void verify_c(double Z_c[], double Z_expected[], int length)
{
    double margin = 0.00001; // 10^-5
    double diff;
    int isAllInRange = 1;
    for (int i = 0; i < length; i++)
    {
        diff = Z_c[i] - Z_expected[i];
        if (margin < diff || diff < -margin)
        {
            printf("%2d: implementation=%.8lf, expected=%.8lf --- MISMATCH\n", i, Z_c[i], Z_expected[i]);
            isAllInRange = 0;
        }
        else
            printf("%2d: implementation=%.8lf, expected=%.8lf\n", i, Z_c[i], Z_expected[i]);
    }
    if (isAllInRange)
        printf("\nAll results are within the margin of 10^-5.\n");
}

int main()
{
    double X_1[LENGTH] = {1.5, 4.0, 3.5, 2.0};
    double X_2[LENGTH] = {3.0, 2.5, 2.5, 1.0};
    double Y_1[LENGTH] = {4.0, 3.0, 3.5, 3.0};
    double Y_2[LENGTH] = {2.0, 2.5, 1.0, 1.5};

    double Z_c[LENGTH];
    double Z_expected[LENGTH] = {2.5, 1.58113883, 2.692582404, 1.802775638};

    printf("\nN = %d\n", LENGTH);
    euclidean_distance_c(X_1, X_2, Y_1, Y_2, Z_c, LENGTH);
    verify_c(Z_c, Z_expected, LENGTH);

    return 0;
}