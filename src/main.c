#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "kernel.c"

#define LENGTH 4

extern void euclidean_distance_asm(double X_1[], double X_2[], double Y_1[], double Y_2[], double Z[], int length);

double getTimeElapsed(clock_t start)
{
    clock_t end = clock();
    return ((double)(end - start)) / (double)CLOCKS_PER_SEC;
}

void printOutput(double Z[], int length)
{
    printf("Z[%d] = {", length);
    for (int i = 0; i < length; i++)
    {
        printf("%.8lf", Z[i]);
        if (i < length - 1)
            printf(", ");
    }
    printf("}\n");
}

void verifyAssembly(double Z_asm[], double Z_c[], int length)
{
    double margin = 0.000001; // 2^-5
    double diff;
    int isAllInRange = 1;
    for (int i = 0; i < length; i++)
    {
        diff = Z_asm[i] - Z_c[i];
        if (margin < diff || diff < -margin)
        {
            printf("Mismatch at index %d: asm=%.8lf, c=%.8lf\n", i, Z_asm[i], Z_c[i]);
            isAllInRange = 0;
        }
    }
    if (isAllInRange)
        printf("All results are within the margin of 2^-5.\n");
}

int main()
{
    double X_1[LENGTH] = {1.5, 4.0, 3.5, 2.0};
    double X_2[LENGTH] = {3.0, 2.5, 2.5, 1.0};
    double Y_1[LENGTH] = {4.0, 3.0, 3.5, 3.0};
    double Y_2[LENGTH] = {2.0, 2.5, 1.0, 1.5};

    double Z_c[LENGTH];
    double Z_asm[LENGTH];

    clock_t start, totalTimeC, totalTimeAsm;

    start = clock();
    euclidean_distance_c(X_1, X_2, Y_1, Y_2, Z_c, LENGTH);
    totalTimeC = getTimeElapsed(start);

    start = clock();
    euclidean_distance_asm(X_1, X_2, Y_1, Y_2, Z_asm, LENGTH);
    totalTimeAsm = getTimeElapsed(start);

    verifyAssembly(Z_asm, Z_c, LENGTH);

    // printf("Total time taken: %ld seconds\n", totalTimeC);

    return 0;
}