#pragma once
#include "pmframework.hpp"

namespace pmframework
{

class angleSet3d
{
private:
    scalar xRotationAngle;
    scalar yRotationAngle;
    scalar zRotationAngle;

    scalar CheckAngle(scalar angle);

public:
    angleSet3d();
    angleSet3d(scalar xRotation, scalar yRotation, scalar zRotatiton);
    angleSet3d(const angleSet3d &angleSet);

    void XAngle(scalar xRotation);
    scalar XAngle(void);

    void YAngle(scalar yRotation);
    scalar YAngle(void);

    void ZAngle(scalar zRotation);
    scalar ZAngle(void);

    void SetXYZ(scalar xRotation, scalar yRotation, scalar zRotation);
    angleSet3d &operator = (const angleSet3d &rightOperand);
};

inline angleSet3d::angleSet3d(void)
{
    xRotationAngle = yRotationAngle = zRotationAngle = 0;
}

inline angleSet3d::angleSet3d(scalar xRotation, scalar yRotation, scalar zRotation)
{
    xRotationAngle = CheckAngle(xRotation);
    yRotationAngle = CheckAngle(yRotation);
    zRotationAngle = CheckAngle(zRotation);
}

inline angleSet3d::angleSet3d(const angleSet3d &angleSet)
{
    XAngle(angleSet.xRotationAngle);
    YAngle(angleSet.yRotationAngle);
    ZAngle(angleSet.zRotationAngle);
}

inline void angleSet3d::XAngle(scalar xRotation)
{
    xRotationAngle = CheckAngle(xRotation);
}

inline scalar angleSet3d::XAngle(void)
{
    return xRotationAngle;
}

inline void angleSet3d::YAngle(scalar yRotation)
{
    yRotationAngle = CheckAngle(yRotation);
}

inline scalar angleSet3d::YAngle(void)
{
    return yRotationAngle;
}

inline void angleSet3d::ZAngle(scalar zRotation)
{
    zRotationAngle = CheckAngle(zRotation);
}

inline scalar angleSet3d::ZAngle(void)
{
    return zRotationAngle;
}

inline void angleSet3d::SetXYZ(scalar xRotation, scalar yRotation, scalar zRotation)
{
    XAngle(xRotation);
    YAngle(yRotation);
    ZAngle(zRotation);
}

inline angleSet3d &angleSet3d::operator =(const angleSet3d &rightOperand)
{
    XAngle(rightOperand.xRotationAngle);
    YAngle(rightOperand.yRotationAngle);
    ZAngle(rightOperand.zRotationAngle);
    return (*this);
}

inline scalar angleSet3d::CheckAngle(scalar angle)
{
    scalar tempAngle = angle;
    
    tempAngle = (tempAngle < 0.0) ? -1 * tempAngle : tempAngle;
    for (; tempAngle > 2 * PI; tempAngle -= 2 * PI)
    {

    }
    tempAngle = (angle < 0.0) ? -1 * tempAngle: tempAngle;
    return tempAngle;
}

}