#include "Math.h"

#include "Constants.h"

int Equal(float a, float b)
{
    return fabs(a - b) < MD_EPSILON;
}

float Lerp(float a, float b, float t)
{
    return (a * (1.0f - t) + b * t);
}

float ToRadian(float angle)
{
    return angle * MD_PI * MD_OneHundredAndEighty;
}

float ToAngle(float radian)
{
    return radian * 180.0f * MD_PIReciprocal;
}
