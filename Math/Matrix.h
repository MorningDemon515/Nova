#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

struct Matrix
{
    union
    {
        struct
        {
            float _11, _12, _13, _14,
                     _21, _22, _23, _24,
                     _31, _32, _33, _34,
                     _41, _42, _43, _44;
        };
        float data[4][4];
    };
};

typedef struct Matrix Matrix;

void PrintMat(Matrix m);

Matrix FloatToMatrix(const float m[4][4]);
Matrix MatTranspose(const float m[4][4]);

Matrix MatAdd(const float m1[4][4], const float m2[4][4]);
Matrix MatSub(const float m1[4][4], const float m2[4][4]);
Matrix MatMul(const float m1[4][4], const float m2[4][4]);
Matrix MatScale(const float m[4][4], float s);
int MatEqual(const float m1[4][4], const float m2[4][4]);

float MatDet(const float m[4][4]);
Matrix MatAdj(const float m[4][4]);
Matrix MatInv(const float m[4][4]);

Vector VecMulMat(const float v[4], const float m[4][4]);

#endif // MATRIX_H
