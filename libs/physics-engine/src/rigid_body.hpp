#pragma once

#include "pmframework.hpp"

namespace pmframework
{

class RigidBody
{
private:
    //mesh objectMesh;

    scalar mass;
    Vector3d centerOfMass;
    Vector3d linearVelocity;
    Vector3d linearAcceleration;
    force sumForces;

    angleSet3d currentOrientation;
    Vector3d angularVelocity;
    Vector3d angularAcceleration;
    Vector3d rotationalInertia;
    Vector3d torque;

    scalar coefficientOfRestitution;
    scalar boundingSphereRadius;

    //___ worldMatrix;

public:
    RigidBody(void);

    //bool LoadMesh(std::string meshFileName);

    void Mass(scalar massValue);
    scalar Mass(void);

    void Location(Vector3d locationCenterOfMass);
    Vector3d Location(void);

    void LinearVelocity(Vector3d newVelocity);
    Vector3d LinearVelocity(void);

    void LinearAcceleration(Vector3d newAcceleration);
    Vector3d LinearAcceleration(void);

    void Force(force SumExternalForces);
    force Force(void);

    void CurrentOrientation(angleSet3d newOrientation);
    angleSet3d CurrentOrientation(void);

    void AngularVelocity(Vector3d newAngularVelocity);
    Vector3d AngularVelocity(void);

    void AngularAcceleration(Vector3d newAngularAcceleration);
    Vector3d AngularAcceleration(void);

    void RotationalInertia(Vector3d inertiaValue);
    Vector3d RotationalInertia(void);

    void Torque(Vector3d torqueValue);
    Vector3d Torque(void);

    void CoefficientOfRestitution(scalar elasticity);
    scalar CoefficientOfRestitution(void);

    void BoundingSphereRadius(scalar radius);
    scalar BoundingSphereRadius(void);

    bool Update(scalar changeInTime);
    bool Render(void);

};

inline RigidBody::RigidBody(void)
{
    mass = 0.0;
}

//inline bool RigidBody::LoadMesh(std::string meshFileName)
//{}

inline void RigidBody::Mass(scalar massValue)
{
    assert(massValue > 0);
    mass = massValue;
}

inline scalar RigidBody::Mass(void)
{
    return mass;
}

inline void RigidBody::Location(Vector3d locationCenterOfMass)
{
    centerOfMass = locationCenterOfMass;
}

inline Vector3d RigidBody::Location(void)
{
    return centerOfMass;
}

inline void RigidBody::LinearVelocity(Vector3d newVelocity)
{
    linearVelocity = newVelocity;
}

inline Vector3d RigidBody::LinearVelocity(void)
{
    return linearVelocity;
}

inline void RigidBody::LinearAcceleration(Vector3d newAcceleration)
{
    linearAcceleration = newAcceleration;
}

inline Vector3d RigidBody::LinearAcceleration(void)
{
    return linearAcceleration;
}

inline void RigidBody::Force(force sumExternalForces)
{
    sumForces = sumExternalForces;
}

inline force RigidBody::Force(void)
{
    return sumForces;
}

inline void RigidBody::CurrentOrientation(angleSet3d newOrientation)
{
    currentOrientation = newOrientation;
}

inline angleSet3d RigidBody::CurrentOrientation(void)
{
    return currentOrientation;
}

inline void RigidBody::AngularVelocity(Vector3d newAngularVelocity)
{
    angularVelocity = newAngularVelocity;
}

inline Vector3d RigidBody::AngularVelocity(void)
{
    return angularVelocity;
}

inline void RigidBody::AngularAcceleration(Vector3d newAngularAcceleration)
{
    angularAcceleration = newAngularAcceleration;
}

inline Vector3d RigidBody::AngularAcceleration(void)
{
    return angularAcceleration;
}

inline void RigidBody::RotationalInertia(Vector3d inertiaValue)
{
    rotationalInertia = inertiaValue;
}

inline Vector3d RigidBody::RotationalInertia(void)
{
    return rotationalInertia;
}

inline void RigidBody::Torque(Vector3d torqueValue)
{
    torque = torqueValue;
}

inline Vector3d RigidBody::Torque(void)
{
    return torque;
}

inline void RigidBody::CoefficientOfRestitution(scalar elasticity)
{
    coefficientOfRestitution = elasticity;
}

inline scalar RigidBody::CoefficientOfRestitution(void)
{
    return coefficientOfRestitution;
}

inline void RigidBody::BoundingSphereRadius(scalar radius)
{
    boundingSphereRadius = radius;
}

inline scalar RigidBody::BoundingSphereRadius(void)
{
    return boundingSphereRadius;
}


}