#pragma once
#include "math.hpp"

namespace pmframework
{


class PointMass
{
private:
    //mesh objectMesh;

    scalar mass;
    Vector3d centerOfMass;
    Vector3d linearVelocity;
    Vector3d linearAcceleration;
    Vector3d sumForces;

    scalar radius;
    scalar restitution;

    //____ worldMatrix; // transformation 계산할 행렬

public:
    PointMass();

    bool LoadMesh(std::string meshFileName);

    void Mass(scalar massValue);
    scalar Mass(void);
    
    void Location(Vector3d locationCenterOfMass);
    Vector3d Location(void);

    void LinearVelocity(Vector3d newVelocity);
    Vector3d LinearVelocity(void);

    void LinearAcceleration(Vector3d newAcceleration);
    Vector3d LinearAcceleration(void);

    void Force(Vector3d sumExternalForces);
    Vector3d Force(void);

    void BoundingSphereRadius(scalar sphereRadius);
    scalar BoundingSphereRadius(void);

    void Elasticity(scalar elasticity);
    scalar Elasticity(void);

    bool Update(scalar changeInTime); // 월드 행렬 값 지정
    bool Render(void); //월드행렬 이용하여 점들의 위치 변화
};


inline PointMass::PointMass(void)
{
    mass = 0.0;
}

//inline bool PointMass::LoadMesh(std::string meshFileName)
//{
    //assert(meshFileName.length() > 0);
    //return (objectMesh.Load(meshFileName));
//}

inline void PointMass::Mass(scalar massValue)
{
    assert(massValue > 0.0);
    mass = massValue;
}

inline scalar PointMass::Mass(void)
{
    return mass;
}

inline void PointMass::Location(Vector3d locationCenterOfMass)
{
    centerOfMass = locationCenterOfMass;
}

inline Vector3d PointMass::Location(void)
{
    return centerOfMass;
}

inline void PointMass::LinearVelocity(Vector3d newVelocity)
{
    linearVelocity = newVelocity;
}

inline Vector3d PointMass::LinearVelocity(void)
{
    return linearVelocity;
}

inline void PointMass::LinearAcceleration(Vector3d newAcceleration)
{
    linearAcceleration = newAcceleration;
}

inline Vector3d PointMass::LinearAcceleration(void)
{
    return linearAcceleration;
}

inline void PointMass::Force(Vector3d sumExternalForces)
{
    sumForces = sumExternalForces;
}

inline Vector3d PointMass::Force(void)
{
    return sumForces;
}

inline void PointMass::BoundingSphereRadius(scalar sphereRadius)
{
    radius = sphereRadius;
}

inline scalar PointMass::BoundingSphereRadius(void)
{
    return radius;
}

inline void PointMass::Elasticity(scalar elasticity)
{
    restitution = elasticity;
}

inline scalar PointMass::Elasticity(void)
{
    return restitution;
}


}