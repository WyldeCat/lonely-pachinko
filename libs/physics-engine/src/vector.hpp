#include <cmath>

class Vector3d
{
private :
    float x, y, z;

public:
    Vector3d(void);
    Vector3d(float xComponent, float yComponent, float zComponent);
    Vector3d(const Vector3d &rightOperand);

    void X(float xComponent);
    float X(void);

    void Y(float yComponent);
    float Y(void);

    void Z(float zComponent);
    float Z(void);

    void SetXYZ(float xComponent, float yComponent, float zComponent);
    void GetXYZ(float &xCompoenet, float &yComponent, float &zComponent);

    Vector3d &operator = (const Vector3d &rightOperand);
    
    inline Vector3d Vector3d::operator +(Vector3d &rightOperand)
    {
        return(Vector3d(x + rightOperand.x, y + rightOperand.y, z + rightOperand.z));
    }
    inline Vector3d Vector3d::operator -(Vector3d &rightOperand)
    {
        return(Vector3d(x - rightOperand.x, y - rightOperand.y, z - rightOperand.z));
    }
    inline Vector3d Vector3d::operator +=(Vector3d &rightOperand)
    {
        x += rightOperand.x;
        y += rightOperand.y;
        z += rightOperand.z;
        return (*this);
    }
    inline Vector3d Vector3d::operator -=(Vector3d &rightOperand)
    {
        x -= rightOperand.x;
        y -= rightOperand.y;
        z -= rightOperand.z;
        return (*this);
    }
    inline Vector3d Vector3d::operator *(float rightOperand)
    {
        return(Vector3d(x * rightOperand, y * rightOperand, z * rightOperand));
    }

    friend inline Vector3d operator *(float leftOperaand, Vector3d &rightOperand)
    {
        return (Vector3d(leftOperand*rightOperand.x,
                         leftOperand*rightOperand.y
                         leftOperand*rightOperand.z));
    }
    
    inline Vector3d Vector3d::operator *=(float rightOperand)
    {
        x *= rightOperand;
        y *= rightOperand;
        z *= rightOperand;
        return (*this);
    }

    inline Vector3d Vector3d::operator /(float rightOperand)
    {
        return (Vector3d(x / rightOperand, y / rightOperand, z / rightOperand));
    }

    inline Vector3d Vector3d::operator /=(float rightOperand)
    {
        x /= rightOperand;
        y /= rightOperand;
        z /= rightOperand;
    }

    inline float Vector3d::dotProduct(const Vector3d &v1)
    {
        return (x*v1.x, y*v1.y, z*v1.z);
    }

    inline float Vector3d::norm(void)
    {
        return (sqrt(x*x + y*y + z*z));
    }

    inline float Vector3d::normSquared(void)
    {
        return (x*x + y*y + z*z);
    }

    inline Vector3d Vector3d::crossProduct(const Vector3d &rightOperand)
    {
        return(
            Vector3d(
                y*rightOperand.z - z*rightOperand.y,
                z*rightOperand.x - x*rightOperand.z,
                x*rightOperand.y - y*rightOperand.x));
    }

    inline Vector3d Vector3d::normalize(float tolerance)
    {
        Vector3d result;

        float length = norm();
        if (length >= tolerance) {
            result.x = x / length;
            result.y = y / length;
            result.z = z / length;
        }
        return(result);
    }

};