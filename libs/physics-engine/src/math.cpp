#include "pmframework.hpp"

namespace pmframework
{

    Matrix3x3::Matrix3x3(void)
    {
        for (int Counter = 0; Counter < 9; Counter++)
        {
            aElements[0][Counter] = 0;
        }
        aElements[0][0] = aElements[1][1] = aElements[2][2] = 1;
    }

    Matrix3x3 operator*(Matrix3x3 const &Multiplicand, Matrix3x3 const &Multiplier)
    {
        Matrix3x3 ReturnMatrix;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                scalar Value = 0;

                for (int k = 0; k < 3; k++)
                {
                    Value += Multiplicand.GetElement(i, k) *
                        Multiplier.GetElement(k, j);
                }

                ReturnMatrix.SetElement(i, j, Value);
            }
        }

        return ReturnMatrix;
    }

    void OrthonormalizeOrientation(Matrix3x3 &Orientation)
    {
        Vector3d x1(Orientation(0, 0), Orientation(1, 0), Orientation(2, 0));
        Vector3d y1(Orientation(0, 1), Orientation(1, 1), Orientation(2, 1));
        Vector3d z1;

        x1.normalize(SCALAR_TOLERANCE);
        z1 = x1.crossProduct(y1.normalize(SCALAR_TOLERANCE));
        y1 = z1.crossProduct(x1.normalize(SCALAR_TOLERANCE));

        Orientation(0, 0) = x1.X(); Orientation(0, 1) = y1.X(); Orientation(0, 2) = z1.X();
        Orientation(1, 0) = x1.Y(); Orientation(1, 1) = y1.Y(); Orientation(1, 2) = z1.Y();
        Orientation(2, 0) = x1.Z(); Orientation(2, 1) = y1.Z(); Orientation(2, 2) = z1.Z();
    }

    Vector3d operator*(Matrix3x3 const &Multiplicand, Vector3d Multiplier)
    {
        Vector3d ReturnPoint;

        for (int i = 0; i < 3; i++)
        {
            scalar Value = 0;
            Value += Multiplicand.GetElement(i, 0) * Multiplier.X();
            Value += Multiplicand.GetElement(i, 1) * Multiplier.Y();
            Value += Multiplicand.GetElement(i, 2) * Multiplier.Z();
            if (i == 0) ReturnPoint.X(Value);
            else if (i == 1) ReturnPoint.Y(Value);
            else ReturnPoint.Z(Value);
        }

        return ReturnPoint;
    }

}