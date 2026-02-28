#include "Quaternion.h"

#include <math.h>

Quaternion QuatAdd(const float q1[4], const float q2[4])
{
    Quaternion result = { 0 };

    for(int i = 0; i < 4; i++)
    {
        result.data[i] = q1[i] + q2[i];
    }

    return result;
}

Quaternion QuatSub(const float q1[4], const float q2[4])
{
    Quaternion result = { 0 };

    for(int i = 0; i < 4; i++)
    {
        result.data[i] = q1[i] - q2[i];
    }

    return result;
}

Quaternion QuatMul(const float q1[4], const float q2[4])
{
    float s1 = q1[0]; float s2 = q2[0];
    float a[4] = {q1[1],  q1[2], q1[3], 0.0f}; float b[4] = {q2[1],  q2[2], q2[3], 0.0f};

    Quaternion result = { 0 };
    result.a = s1 * s2 - VecDot(a, b);

    Vector axis = VecAdd(VecCross(a, b).data, VecAdd(VecScale(a, s2).data, VecScale(b, s1).data).data);
    result.b = axis.x;
    result.c = axis.y;
    result.d = axis.z;

    return result;
}

Quaternion QuatScale(const float q[4], float s)
{
    Quaternion result = { 0 };

    for(int i = 0; i < 4; i++)
    {
        result.data[i] = s * q[i];
    }

    return result;
}

int QuatEqual(const float q1[4], const float q2[4])
{
    return VecEqual(q1, q2);
}

float QuatLength(const float q[4])
{
    return VecLength(q);
}

Quaternion QuatNorm(const float q[4])
{
    Vector v = VecNorm(q);
    Quaternion result = {v.x, v.y, v.z, v.w};
    return result;
}

Quaternion QuatConj(const float q[4])
{
    Quaternion result = {q[0], -q[1], -q[2], -q[3]};
    return result;
}

Quaternion QuatInv(const float q[4])
{
    float d = VecDot(q, q);
    Quaternion conj = QuatConj(q);
    return QuatScale(conj.data, 1.0f/ d);
}

float QuatDot(const float q1[4], const float q2[4])
{
    return VecDot(q1, q2);
}

Quaternion QuatFromAxisAngle(Vector axis, float angle)
{
    Quaternion result = { 0 };
    float halfAngle = angle * 0.5f;

    result.a = cos(halfAngle);
    Vector v = VecScale(VecNorm(axis.data).data, sin(halfAngle));

    result.b = v.x;
    result.c = v.y;
    result.d = v.z;

    return result;
}

Matrix QuatToMat(const float q[4])
{
    Quaternion t  = { 0 };
    t.data[0] = q[0];
    t.data[1] = q[1];
    t.data[2] = q[2];
    t.data[3] = q[3];
    t = QuatNorm(t.data);

    Matrix result = MatIdentity();

    float w = t.a;
    float x = t.b;
    float y = t.c;
    float z = t.d;

    result._11 = 1.0f - 2.0f * (y * y + z * z);
    result._21 = 2.0f * (x * y + w * z);
    result._31 = 2.0f * (x * z - w * y);

    result._12 = 2.0f * (x * y - w * z);
    result._22 = 1.0f - 2.0f * (x * x + z * z);
    result._32 = 2.0f * (y * z + w * x);

    result._13 = 2.0f * (x * z + w * y);
    result._23 = 2.0f * (y * z - w * x);
    result._33 = 1.0f - 2.0f * (x * x + y * y);

    return result;
}

Vector RotateVec(const float q[4], Vector v)
{
    Quaternion p = {0.0f, v.x, v.y, v.z};
    Quaternion q_ = { 0 };
    q_.data[0] = q[0];
    q_.data[1] = q[1];
    q_.data[2] = q[2];
    q_.data[3] = q[3];
    Quaternion _q = QuatInv(q_.data);

    Quaternion r_q = QuatMul(QuatMul(q_.data, p.data).data, _q.data);
    Vector result = {r_q.b, r_q.c, r_q.d, 0.0f};

    return result;
}

Quaternion QuatLerp(const float q1[4], const float q2[4], float t)
{
    Quaternion result = { 0 };

    result = QuatAdd(QuatScale(q1, (1.0f - t)).data ,  QuatScale(q2, t).data);

    return result;
}

Quaternion QuatSlerp(const float q1[4], const float q2[4], float t)
{
    Quaternion result = { 0 };

    float dot = QuatDot(q1, q2);

    float sign = 1.0f;
    if (dot < 0.0f) {
        dot = -dot;
        sign = -1.0f;
    }

    float theta = acos(dot);
    float sin_theta = sin(theta);

    float scale1, scale2;
    if (sin_theta > 0.001f) {
        scale1 = sin((1.0f - t) * theta) / sin_theta;
        scale2 = sin(t * theta) / sin_theta;
    } else {
        scale1 = 1.0f - t;
        scale2 = t;
    }

    result = QuatAdd(
        QuatScale(q1, scale1).data,
        QuatScale(q2, scale2 * sign).data
    );

    return QuatNorm(result.data);
}
