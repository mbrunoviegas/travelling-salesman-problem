#include <iostream>
#include <cstring>
#include <math.h>
#include <climits>

#pragma once

using namespace std;

namespace Graph
{
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define MAX_N 100

    int x[] = {100, 900, 900, 100, 150, 709, 467, 329, 936, 440, 700, 117, 258, 811, 952, 491, 993, 931, 823, 431, 359, 590, 899, 153, 292, 370, 404, 698, 699, 876, 442, 705, 757, 527, 868, 893, 642, 273, 18, 885, 675, 788, 291, 303, 656, 660, 126, 704, 225, 862, 522, 617, 630, 725, 17, 847, 715, 732, 502, 778, 304, 32, 168, 841, 288, 76, 31, 934, 245, 626, 419, 782, 875, 723, 346, 335, 992, 70, 369, 545, 610, 611, 60, 935, 738, 829, 962, 369, 918, 282, 928, 407, 602, 312, 532, 517, 102, 80, 907, 525};
    int y[] = {100, 100, 900, 900, 633, 399, 904, 632, 445, 608, 109, 293, 520, 459, 426, 303, 952, 87, 138, 230, 505, 982, 162, 183, 911, 826, 348, 64, 896, 128, 434, 962, 955, 94, 246, 601, 121, 472, 581, 221, 361, 981, 944, 571, 488, 513, 834, 403, 634, 581, 653, 585, 876, 448, 631, 682, 43, 985, 988, 111, 883, 142, 235, 797, 123, 592, 376, 559, 385, 137, 291, 635, 923, 336, 18, 970, 244, 222, 476, 249, 422, 723, 602, 748, 258, 681, 603, 420, 769, 639, 583, 75, 258, 307, 36, 59, 548, 905, 363, 354};

    void swap(int* vetor, int i, int j)
    {
        int aux = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = aux;
    }

    void fillVector (int* vector, int n){
        for (int i = 0; i < n; i++){
            vector[i] = i;
        }
    }
    
    void initMatrix(int **matrix, int n)
    {
        for (int i = 0; i < n; i++)
        {
            matrix[i] = new int[n];
            memset(matrix[i], 0, n * sizeof(int));
        }
    }

    double twoPointsDistance(int i, int j, int *x, int *y)
    {
        double distance = sqrt(pow((x[i] - x[j]), 2) + pow((y[i] - y[j]), 2));
        return distance;
    }

    void fillMatrix(int **matrix, int n, int *x, int *y)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                matrix[i][j] = twoPointsDistance(i, j, x, y);
            }
        }
    }
    
    double twoPointsDistanceManual(int i, int j, int *x1, int *y1)
    {
        double distance = sqrt(pow((x1[i] - x1[j]), 2) + pow((y1[i] - y1[j]), 2));
        return distance;
    }

    void fillMatrixManual(int **matrix, int n)
    {
        int *x1, *y1;
        x1 = new int[n];
        y1 = new int[n];
        for (int i = 0; i < n; i++)
        {
            cin >> x1[i] >> y1[i];
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                matrix[i][j] = twoPointsDistance(i, j, x1, y1);
            }
        }
    }

    void printMatrix(int **matrix, int n)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << " | " << matrix[i][j] << " | ";
            }
            cout << endl;
        }
    }

} // namespace Graph
