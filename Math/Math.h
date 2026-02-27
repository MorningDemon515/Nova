#ifndef MATH_H
#define MATH_H

#include <math.h>

#include "Matrix.h"

int Equal(float a, float b);
float Lerp(float a, float b, float t);
float ToRadian(float angle);
float ToAngle(float radian);

Vector Vec2(float x, float y);
Vector Vec3(float x, float y, float z);
Vector Vec4(float x, float y, float z, float w);

#endif // MATH_H
