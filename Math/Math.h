#ifndef MATH_H
#define MATH_H

#include <math.h>

#include "Quaternion.h"

int Equal(float a, float b);
float Lerp(float a, float b, float t);
float ToRadian(float angle);
float ToAngle(float radian);

Vector Vec2(float x, float y);
Vector Vec3(float x, float y, float z);
Vector Vec4(float x, float y, float z, float w);

Quaternion Quat(float a, float b, float c, float d);

#endif // MATH_H
