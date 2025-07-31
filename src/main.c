#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#include "kernel.c"

#define VERBOSE 0
#define EXPONENT 29 // modify to either 20, 24, and 29
#define LENGTH (1 << EXPONENT)

extern void euclidean_distance_asm(double X_1[], double X_2[], double Y_1[], double Y_2[], double Z[], int length);

double getTimeElapsed(clock_t start)
{
    clock_t end = clock();
    return ((double)(end - start)) / (double)CLOCKS_PER_SEC;
}

void verifyAssembly(double Z_asm[], double Z_c[], int length)
{
    double margin = 0.00001; // 10^-5
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
        printf("All results are within the margin of 10^-5.\n");
}

void propagate_vectors(double X_1[], double X_2[], double Y_1[], double Y_2[])
{
    for (int i = 0; i < LENGTH; i++)
    {
        X_1[i] = ((double)rand() / RAND_MAX) * (DBL_MAX - DBL_MIN) + DBL_MIN;
        X_2[i] = ((double)rand() / RAND_MAX) * (DBL_MAX - DBL_MIN) + DBL_MIN;
        Y_1[i] = ((double)rand() / RAND_MAX) * (DBL_MAX - DBL_MIN) + DBL_MIN;
        Y_2[i] = ((double)rand() / RAND_MAX) * (DBL_MAX - DBL_MIN) + DBL_MIN;
    }
}

int main()
{
    double *X_1 = (double *)malloc(sizeof(double) * LENGTH);
    double *X_2 = (double *)malloc(sizeof(double) * LENGTH); // = {3.0, 2.5, 2.5, 1.0};
    double *Y_1 = (double *)malloc(sizeof(double) * LENGTH); // = {4.0, 3.0, 3.5, 3.0};
    double *Y_2 = (double *)malloc(sizeof(double) * LENGTH); // = {2.0, 2.5, 1.0, 1.5};

    double *Z_c = (double *)malloc(sizeof(double) * LENGTH);
    double *Z_asm = (double *)malloc(sizeof(double) * LENGTH);

    clock_t start;
    double totalTimeC, totalTimeAsm;

    printf("N = %d\n\n", LENGTH);

    if (VERBOSE)
        printf("Generating random vectors...\n");
    propagate_vectors(X_1, X_2, Y_1, Y_2);
    if (VERBOSE)
        printf("Random vectors generated.\n\n");

    if (VERBOSE)
        printf("Calculating Euclidean distance (C implementation)...\n");
    start = clock();
    euclidean_distance_c(X_1, X_2, Y_1, Y_2, Z_c, LENGTH);
    totalTimeC = getTimeElapsed(start);
    if (VERBOSE)
        printf("C implementation completed.\n\n");

    if (VERBOSE)
        printf("Calculating Euclidean distance (Assembly implementation)...\n");
    start = clock();
    euclidean_distance_asm(X_1, X_2, Y_1, Y_2, Z_asm, LENGTH);
    totalTimeAsm = getTimeElapsed(start);
    if (VERBOSE)
        printf("Assembly implementation completed.\n\n");

    if (VERBOSE)
        printf("Comparing results...\n");
    verifyAssembly(Z_asm, Z_c, LENGTH);
    printf("\n");

    printf("Results summary:\n");
    printf("Total time taken (C implementation): %lf seconds\n", totalTimeC);
    printf("Total time taken (Assembly implementation): %lf seconds\n", totalTimeAsm);

    if (VERBOSE)
        printf("Deallocating memory...\n");
    free(X_1);
    free(X_2);
    free(Y_1);
    free(Y_2);
    free(Z_c);
    free(Z_asm);

    return 0;
}