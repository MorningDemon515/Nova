#include "Matrix.h"

#include <stdio.h>
#include <string.h>

void PrintMat(Matrix m)
{
    for(int i = 0; i < 4 ; i++)
    {
        printf("%f, %f, %f, %f \n", m.data[i][0], m.data[i][1], m.data[i][2], m.data[i][3]);
    }

    printf("\n");
}

Matrix MatTranspose(const float m[4][4])
{
    Matrix result = { 0 };

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            result.data[i][j] = m[j][i];
        }
    }

    return result;
}

