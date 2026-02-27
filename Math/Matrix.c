#include "Matrix.h"

#include <stdio.h>
#include <string.h>

void PrintMat(Matrix m)
{
    for(int i = 0; i < 4 ; i++)
    {
        printf("%f, %f, %f, %f \n", m.data[i][0], m.data[i][1], m.data[i][2], m.data[i][3]);
    }

    printf("\n");
}

Matrix FloatToMatrix(const float m[4][4])
{
    Matrix result = { 0 };

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            result.data[i][j] = m[i][j];
        }
    }

    return result;
}

Matrix MatTranspose(const float m[4][4])
{
    Matrix result = { 0 };

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            result.data[i][j] = m[j][i];
        }
    }

    return result;
}

Matrix MatAdd(const float m1[4][4], const float m2[4][4])
{
    Matrix result = { 0 };

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            result.data[i][j] = m1[i][j] + m2[i][j];
        }
    }

    return result;
}

Matrix MatSub(const float m1[4][4], const float m2[4][4])
{
    Matrix result = { 0 };

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            result.data[i][j] = m1[i][j] - m2[i][j];
        }
    }

    return result;
}

Matrix MatMul(const float m1[4][4], const float m2[4][4])
{
    Matrix result = { 0 };
    Matrix temp = MatTranspose(m2);

    Vector temp1 = { 0 };
    Vector temp2 = { 0 };

    for(int i = 0; i <4 ; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            memcpy(temp1.data, m1[i], sizeof(temp1.data));
            memcpy(temp2.data, temp.data[j], sizeof(temp2.data));

            result.data[i][j] = VecDot(temp1.data, temp2.data);
        }
    }

    return result;
}

Matrix MatScale(const float m[4][4], float s)
{
    Matrix result = { 0 };

    for(int i = 0; i< 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            result.data[i][j] = s * m[i][j];
        }
    }

    return result;
}

int MatEqual(const float m1[4][4], const float m2[4][4])
{
    int result[4] = { 0 };

    Vector temp1 = { 0 };
    Vector temp2 = { 0 };
    for(int i = 0; i < 4; i++)
    {
        memcpy(temp1.data, m1[i], sizeof(temp1.data));
        memcpy(temp2.data, m2[i], sizeof(temp2.data));

        result[i] = VecEqual(temp1.data, temp2.data);
    }

    return (result[0] && result[1] && result[2] && result[3]) ? 1 : 0;
}

//-----------------------------------------------------------------------
float Mat2x2Det(float m[2][2])
{
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

float Mat3x3Det(float m[3][3])
{
    /*
    m[0][0] m[0][1] m[0][2]
    m[1][0] m[1][1] m[1][2]
    m[2][0] m[2][1] m[2][2]
    */

    float d1[2][2] = {
        m[1][1], m[1][2],
        m[2][1], m[2][2]
    };

    float d2[2][2] = {
        m[1][0], m[1][2],
        m[2][0], m[2][2]
    };

    float d3[2][2] = {
        m[1][0], m[1][1],
        m[2][0], m[2][1]
    };

    return
    m[0][0] * Mat2x2Det(d1) -
    m[0][1] * Mat2x2Det(d2) +
    m[0][2] * Mat2x2Det(d3)
    ;
}
//--------------------------------------------------------------------------

float MatDet(const float m[4][4])
{
    float result = 0;

    float temp[3][3] = { 0 };

    for(int k = 0; k < 4; k++)
    {
        for(int i =0; i < 3; i++)
        {
            int col = 0;
            for(int j = 0; j < 3; j++)
            {
                if(col == k)
                    col++;

                temp[i][j] = m[i + 1][col];
                col++;
            }
        }

        float sign = ((k % 2) == 0) ? 1.0f : -1.0f;
        result += sign * m[0][k] * Mat3x3Det(temp);
    }

    return result;
}

Matrix MatAdj(const float m[4][4])
{
    Matrix result = { 0 };

    float temp[3][3] = { 0 };

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j ++)
        {

            int row = 0;
            for(int _i = 0; _i < 3; _i++)
            {
                if(row == i)
                    row++;

                int col = 0;
                for(int _j = 0; _j < 3; _j++)
                {
                    if(col == j)
                        col++;

                    temp[_i][_j] = m[row][col];
                    col++;
                }

                row++;
            }


            float sign = ((i + j) % 2 == 0) ? 1.0f : -1.0f;
            result.data[i][j] = sign * Mat3x3Det(temp);
        }
    }

    return MatTranspose(result.data);
}

Matrix MatInv(const float m[4][4])
{
    Matrix result = { 0 };

    float det = MatDet(m);
    Matrix adj = MatAdj(m);
    result = MatScale(adj.data, 1.0f / det);

    return result;
}

Vector VecMulMat(const float v[4], const float m[4][4])
{
    Vector result = { 0 };
    Vector temp = { 0 };
    Matrix t_m = MatTranspose(m);

    for(int i = 0; i < 4; i++)
    {
        memcpy(temp.data, t_m.data[i], sizeof(temp.data));
        result.data[i] = VecDot(v, temp.data);
    }

    return result;
}
