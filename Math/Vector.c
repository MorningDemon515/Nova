
#include "Math.h"
#include <stdio.h>

void PrintVec(Vector v)
{
    printf("x: %f\n", v.x);
    printf("y: %f\n", v.y);
    printf("z: %f\n", v.z);
    printf("w: %f\n", v.w);

    printf("\n");
}

Vector VecAdd(const float *v1, const float *v2)
{
    Vector result = { 0 };
    for(int i = 0; i < 4; i++)
    {
        result.data[i] = v1[i] + v2[i];
    }

    return result;
}

Vector VecSub(const float *v1, const float *v2)
{
    Vector result = { 0 };
    for(int i = 0; i < 4; i++)
    {
        result.data[i] = v1[i] - v2[i];
    }

    return result;
}

Vector VecMul(const float *v1, const float *v2)
{
    Vector result = { 0 };
    for(int i = 0; i < 4; i++)
    {
        result.data[i] = v1[i] * v2[i];
    }

    return result;
}

Vector VecScale(const float *v, float s)
{
    Vector result = { 0 };
    for(int i = 0; i < 4; i++)
    {
        result.data[i] = s * v[i];
    }

    return result;
}

int VecEqual(const float *v1, const float *v2)
{
    int result[4] = { 0 };

    for(int i = 0; i < 4; i++)
    {
        result[i] = Equal(v1[i], v2[i]);
    }

    return (result[0] && result[1] && result[2] && result[3]) ? 1 : 0;
}

Vector VecLerp(const float *v1, const float *v2, float t)
{
    Vector result = { 0 };

    for(int i = 0; i <4; i++)
    {
        result.data[i] = Lerp(v1[i], v2[i], t);
    }

    return result;
}

float VecDot(const float *v1, const float *v2)
{
    float result = 0.0f;

    for(int i = 0; i < 4; i++)
    {
        result += v1[i] * v2[i];
    }

    return result;
}

Vector VecCross(const float *v1, const float *v2)
{
    Vector result = { 0 };

    result.data[0] = v1[1] * v2[2] - v2[1] * v1[2];
    result.data[1] = v2[0] * v1[2] - v1[0] * v2[2];
    result.data[2] = v1[0] * v2[1] - v2[0] * v1[1];

    return result;
}

float VecLength(const float *v)
{
    return sqrt(VecDot(v, v));
}

Vector VecNorm(const float *v)
{
    float length = VecLength(v);
    return VecScale(v, 1.0f / length);
}
