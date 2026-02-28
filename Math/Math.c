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

Vector Vec2(float x, float y)
{
    Vector v = { x, y, 0.0f, 0.0f };
    return v;
}

Vector Vec3(float x, float y, float z)
{
    Vector v = { x, y, z, 0.0f };
    return v;
}

Vector Vec4(float x, float y, float z, float w)
{
    Vector v = { x, y, z, w };
    return v;
}

Quaternion Quat(float a, float b, float c, float d)
{
    Quaternion q = {a, b, c, d};
    return q;
}
