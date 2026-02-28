#include "Matrix.h"

Matrix Translation(Vector pos)
{
    Matrix result = {
        1.0f,    0.0f,      0.0f,         0.0f,
        0.0f,    1.0f,      0.0f,         0.0f,
        0.0f,    0.0f,      1.0f,         0.0f,
        pos.x, pos.y,    pos.z,      1.0f
    };

    return result;
}

Matrix Scale(Vector s)
{
    Matrix result = {
        s.x, 0.0f, 0.0f, 0.0f,
        0.0f, s.y, 0.0f, 0.0f,
        0.0f, 0.0f, s.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    return result;
}

Matrix Orthproj(float w, float h, float n, float f)
{
    Matrix result = {
        2.0f / w, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f/ h, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f / (n + f), 0.0f,
        -1.0f, -1.0f, n / (n + f), 1.0f
    };

    return result;
}
