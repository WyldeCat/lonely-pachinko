#pragma once

#include "pmframework.hpp"

namespace pmframework
{

class RigidBody : protected PointMass
{
private:
    Matrix3x3 inverseBodyInertiaTensor;

    struct configuration : public PointMass::configuration{
        Vector3d angularMomentum;
        Vector3d torque;
        Matrix3x3 orientation;

        Matrix3x3 inverseWorldInertiaTensor;
        Vector3d angularVelocity;
        Vector3d rotationalInertia;
    }aConfiguration[numberOfConfigurations];

    friend class Simulation;

public:
    RigidBody(void);

    virtual void InverseBodyInertiaTensor(Matrix3x3 inverseInertiaValue);
    virtual Matrix3x3 InverseBodyInertiaTensor(void);

    virtual void AngularMomentum(Vector3d angularMomentumValue);
    virtual Vector3d AngularMomentum(void);

    virtual void Torque(Vector3d torqueValue);
    virtual Vector3d Torque(void);

    virtual void Orientation(Vector3d newOrientation);
    virtual Matrix3x3 Orientation(void);

    virtual void InverseWorldInertiaTensor(Matrix3x3 inverseInertiaValue);
    virtual Matrix3x3 InverseWorldInertiaTensor(void);

    virtual void AngularVelocity(Vector3d velocity);
    virtual Vector3d AngularVelocity(void);

    virtual void RotationalInertia(Vector3d inertiaValue);
    virtual Vector3d RotationalInertia(void);
};

inline RigidBody::RigidBody(void)
{

}

inline void RigidBody::InverseBodyInertiaTensor(Matrix3x3 inverseInertiaValue)
{
    inverseBodyInertiaTensor = inverseInertiaValue;
}

inline Matrix3x3 RigidBody::InverseBodyInertiaTensor(void)
{
    return inverseBodyInertiaTensor;
}

inline void RigidBody::AngularMomentum(Vector3d angularMomentumValue)
{
    aConfiguration[0].angularMomentum = angularMomentumValue;
}

inline Vector3d RigidBody::AngularMomentum(void)
{
    return  aConfiguration[0].angularMomentum;
}

inline void RigidBody::Torque(Vector3d torqueValue)
{
    aConfiguration[0].torque = torqueValue;
}

inline Vector3d RigidBody::Torque(void)
{
    return aConfiguration[0].torque;
}

inline void RigidBody::Orientation(Vector3d newOrientation)
{
    aConfiguration[0].orientation = newOrientation;
}

inline Matrix3x3 RigidBody::Orientation(void)
{
    return aConfiguration[0].orientation;
}

inline void RigidBody::InverseWorldInertiaTensor(Matrix3x3 inverseInertiaValue)
{
    aConfiguration[0].inverseWorldInertiaTensor = inverseInertiaValue;
}

inline Matrix3x3 RigidBody::InverseWorldInertiaTensor(void)
{
    return aConfiguration[0].inverseWorldInertiaTensor;
}

inline void RigidBody::AngularVelocity(Vector3d velocity)
{
    aConfiguration[0].angularVelocity = velocity;
}

inline Vector3d RigidBody::AngularVelocity(void)
{
    return aConfiguration[0].angularVelocity;
}

inline void RigidBody::RotationalInertia(Vector3d inertiaValue)
{
    aConfiguration[0].rotationalInertia = inertiaValue;
}

inline Vector3d RigidBody::RotationalInertia(void)
{
    return aConfiguration[0].rotationalInertia;
}

}