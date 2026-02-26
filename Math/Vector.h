#ifndef VECTOR_H
#define VECTOR_H

struct Vector
{
    union
    {
        struct
        {
            float x, y, z, w;
        };

        struct
        {
            float r, g, b, a;
        };

        struct
        {
            float s, t, p, q;
        };

        float data[4];
    };
};

typedef struct Vector Vector;

void PrintVec(Vector v);

Vector VecAdd(const float *v1, const float *v2);
Vector VecSub(const float *v1, const float *v2);
Vector VecMul(const float *v1, const float *v2); //(x1 * x2, y1 * y2, z1 * z2, w1 * w2)
Vector VecScale(const float *v, float s);
int VecEqual(const float *v1, const float *v2);

Vector VecLerp(const float *v1, const float *v2, float t);
float VecDot(const float *v1, const float *v2);
Vector VecCross(const float *v1, const float *v2);
float VecLength(const float *v);
Vector VecNorm(const float *v);

#endif // VECTOR_H
