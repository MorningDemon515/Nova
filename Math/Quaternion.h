#ifndef QUATERNION_H
#define QUATERNION_H

#include "Matrix.h"

/*
a + b i + c j + d k
data[0] + data[1] i + data[2] j + data[3] k
*/
struct Quaternion
{
    union
    {
        float data[4];

        struct
        {
            float a, b, c, d;
        };

    };
};

typedef struct Quaternion Quaternion;

Quaternion QuatAdd(const float q1[4], const float q2[4]);
Quaternion QuatSub(const float q1[4], const float q2[4]);
Quaternion QuatMul(const float q1[4], const float q2[4]);
Quaternion QuatScale(const float q[4], float s);
int QuatEqual(const float q1[4], const float q2[4]);

float QuatLength(const float q[4]);
Quaternion QuatNorm(const float q[4]);

Quaternion QuatConj(const float q[4]);
Quaternion QuatInv(const float q[4]);
float QuatDot(const float q1[4], const float q2[4]);

Quaternion QuatFromAxisAngle(Vector axis, float angle);
Matrix QuatToMat(const float q[4]);
Vector RotateVec(const float q[4], Vector v);
Quaternion QuatLerp(const float q1[4], const float q2[4], float t);
Quaternion QuatSlerp(const float q1[4], const float q2[4], float t);

#endif // QUATERNION_H
