#include <string> 

//==============================================================================
class Matrix
    //==============================================================================
{
public:
    float m[4][4];

    Matrix(float mIn[4][4] = NULL)
    {
        if (mIn)
            set(mIn);
        else
            memset(m, 0, sizeof(float) * 16);
    }

    void set(float glMatrix[4][4])
    {
        memcpy(m, glMatrix, sizeof(float) * 16);
    }

    float* matrix()
    {
        return (float*)m;
    }

    Matrix add(Matrix m2)
    {
        Matrix ret;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                ret.m[i][j] = m[i][j] + m2.m[i][j];
            }
        }


        return ret;

    }

    Matrix subtract(Matrix m2)
    {
        Matrix ret;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                ret.m[i][j] = m[i][j] - m2.m[i][j];
            }
        }

        return ret;

    }

    Matrix multiply(Matrix m2)
    {
        Matrix ret;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                ret.m[i][j] = 0.0;
            }
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    ret.m[i][j] += m[i][k] * m2.m[k][j];
                }
            }
        }

        return ret;
    }

    Matrix inverse()
    {
        Matrix ret;

        if ((m[0][3] != 0) || (m[1][3] != 0) || (m[2][3] != 0) || (m[3][3] != 1))
        {
            printf("ERROR: Matrix is not Affine\n");
            return ret;
        }

        float i11 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
        float i21 = m[1][2] * m[2][0] - m[1][0] * m[2][2];
        float i31 = m[1][0] * m[2][1] - m[1][1] * m[2][0];
        float det = i11*m[0][0] + i21*m[0][1] + i31*m[0][2];

        if (det == 0)
        {
            printf("ERROR: Matrix is singular\n");
            return ret;
        }
        else
            det = 1 / float(det);

        float i12 = m[0][2] * m[2][1] - m[0][1] * m[2][2];
        float i22 = m[0][0] * m[2][2] - m[0][2] * m[2][0];
        float i32 = m[0][1] * m[2][0] - m[0][0] * m[2][1];

        float i13 = m[0][1] * m[1][2] - m[0][2] * m[1][1];
        float i23 = m[0][2] * m[1][0] - m[0][0] * m[1][2];
        float i33 = m[0][0] * m[1][1] - m[0][1] * m[1][0];

        float i41 = -(i11*m[3][0] + i21*m[3][1] + i31*m[3][2]);
        float i42 = -(i12*m[3][0] + i22*m[3][1] + i32*m[3][2]);
        float i43 = -(i13*m[3][0] + i23*m[3][1] + i33*m[3][2]);

        float inv[4][4] =
        {
            { det*i11, det*i12, det*i13, 0 },
            { det*i21, det*i22, det*i23, 0 },
            { det*i31, det*i32, det*i33, 0 },
            { det*i41, det*i42, det*i43, 1 }
        };
        ret.set(inv);

        return ret;
    }
};
