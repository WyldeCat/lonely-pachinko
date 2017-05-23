#pragma once
#include <cmath>
#include <string>
#include <assert.h>

namespace pmframework
{
#define SCALAR_TOLERANCE 0.000001f
const float PI = 3.14159265358979f;
typedef float scalar;

//Vector3d class
class Vector3d
{
private:
    scalar x, y, z;

public:
    Vector3d(void);
    Vector3d(scalar xComponent, scalar yComponent, scalar zComponent);
    Vector3d(const Vector3d &rightOperand);

    void X(scalar xComponent);
    scalar X(void);

    void Y(scalar yComponent);
    scalar Y(void);

    void Z(scalar zComponent);
    scalar Z(void);

    void SetXYZ(scalar xComponent, scalar yComponent, scalar zComponent);
    void GetXYZ(scalar &xCompoenet, scalar &yComponent, scalar &zComponent);

    Vector3d &operator = (const Vector3d &rightOperand);

    Vector3d operator +( const Vector3d &rightOperand);
    Vector3d operator +=( const Vector3d &rightOperand);
    Vector3d operator -( const Vector3d &rightOperand);
    Vector3d operator -=( const Vector3d &rightOperand);
    Vector3d operator *( scalar rightOperand);
    friend Vector3d operator *( scalar leftOperand, const Vector3d &rightOperand);

    Vector3d operator *=( scalar rightOperand);
    Vector3d operator /( scalar rightOperand);
    Vector3d operator /=( scalar rightOperand);

    scalar dotProduct( const Vector3d &v1);
    scalar norm(void);
    scalar normSquared(void);

    Vector3d crossProduct( const Vector3d &rightOperand);
    Vector3d normalize( scalar tolerance);

};

inline Vector3d::Vector3d(void)
{
    x = y = z = 0;
}

inline Vector3d::Vector3d(scalar xComponent, scalar yComponent, scalar zComponent)
{
    x = xComponent;
    y = yComponent;
    z = zComponent;
}

inline Vector3d::Vector3d(const Vector3d &sourceVector)
{
    x = sourceVector.x;
    y = sourceVector.y;
    z = sourceVector.z;
}

inline void Vector3d::X(scalar xComponent)
{
    x = xComponent;
}

inline scalar Vector3d::X(void)
{
    return x;
}

inline void Vector3d::Y(scalar yComponent)
{
    y = yComponent;
}

inline scalar Vector3d::Y(void)
{
    return y;
}

inline void Vector3d::Z(scalar zComponent)
{
    z = zComponent;
}

inline scalar Vector3d::Z(void)
{
    return z;
}

inline void Vector3d::SetXYZ(scalar xComponent, scalar yComponent, scalar zComponent)
{
    x = xComponent;
    y = yComponent;
    z = zComponent;
}

inline void Vector3d::GetXYZ( scalar &xComponent, scalar &yComponent, scalar &zComponent)
{
    xComponent = x;
    yComponent = y;
    zComponent = z;
}

inline Vector3d &Vector3d::operator =( const Vector3d &rightOperand)
{
    x = rightOperand.x;
    y = rightOperand.y;
    z = rightOperand.z;

    return (*this);
}

inline Vector3d Vector3d::operator +(const Vector3d &rightOperand)
{
    return(Vector3d(x + rightOperand.x, y + rightOperand.y, z + rightOperand.z));
}
inline Vector3d Vector3d::operator -(const Vector3d &rightOperand)
{
    return(Vector3d(x - rightOperand.x, y - rightOperand.y, z - rightOperand.z));
}
inline Vector3d Vector3d::operator +=(const Vector3d &rightOperand)
{
    x += rightOperand.x;
    y += rightOperand.y;
    z += rightOperand.z;
    return (*this);
}
inline Vector3d Vector3d::operator -=(const Vector3d &rightOperand)
{
    x -= rightOperand.x;
    y -= rightOperand.y;
    z -= rightOperand.z;
    return (*this);
}
inline Vector3d Vector3d::operator *(scalar rightOperand)
{
    return(Vector3d(x * rightOperand, y * rightOperand, z * rightOperand));
}

inline Vector3d operator *(scalar leftOperand,const Vector3d &rightOperand)
{
    return (Vector3d(leftOperand*rightOperand.x,
                     leftOperand*rightOperand.y,
                     leftOperand*rightOperand.z));
}
inline Vector3d Vector3d::operator *=(scalar rightOperand)
{
    x *= rightOperand;
    y *= rightOperand;
    z *= rightOperand;
    return (*this);
}
inline Vector3d Vector3d::operator /(scalar rightOperand)
{
    return (Vector3d(x / rightOperand, y / rightOperand, z / rightOperand));
}

inline Vector3d Vector3d::operator /=(scalar rightOperand)
{
    x /= rightOperand;
    y /= rightOperand;
    z /= rightOperand;
}
inline scalar Vector3d::dotProduct(const Vector3d &v1)
{
    return (x*v1.x, y*v1.y, z*v1.z);
}
inline scalar Vector3d::norm(void)
{
    return (sqrt(x*x + y*y + z*z));
}

inline scalar Vector3d::normSquared(void)
{
    return (x*x + y*y + z*z);
}

inline Vector3d Vector3d::crossProduct(const Vector3d &rightOperand)
{
    return(Vector3d(y*rightOperand.z - z*rightOperand.y,
        z*rightOperand.x - x*rightOperand.z,
        x*rightOperand.y - y*rightOperand.x));
}

inline Vector3d Vector3d::normalize(scalar tolerance)
{
    Vector3d result;

    scalar length = norm();
    if (length >= tolerance) {
        result.x = x / length;
        result.y = y / length;
        result.z = z / length;
    }
    return result;
}


//Matrix class

class Matrix
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


inline bool CloseToZero(scalar testValue)
{
    bool answer = (testValue > -1 * SCALAR_TOLERANCE && testValue <= SCALAR_TOLERANCE) ? true : false;
    return answer;
}




}