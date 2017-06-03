#pragma once

namespace pmframework
{

    class RigidBody : public PointMass
    {
    private:
        Matrix3x3 inverseBodyInertiaTensor;

        struct configuration : public PointMass::configuration {
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

        void Position(Vector3d positionCenterOfMass);
        Vector3d Position(int configurationIndex);

        void Velocity(Vector3d newVelocity);
        Vector3d Velocity(int configurationIndex);

        void SumForce(Vector3d sumExternalForces);
        Vector3d SumForce(int configurationIndex);

        virtual void InverseBodyInertiaTensor(Matrix3x3 inverseInertiaValue);
        virtual Matrix3x3 InverseBodyInertiaTensor(void);

        virtual void AngularMomentum(Vector3d angularMomentumValue);
        virtual Vector3d AngularMomentum(int configurationIndex);

        virtual void Torque(Vector3d torqueValue);
        virtual Vector3d Torque(int configurationIndex);

        virtual void Orientation(Matrix3x3 newOrientation);
        virtual Matrix3x3 Orientation(int configurationIndex);

        virtual void InverseWorldInertiaTensor(Matrix3x3 inverseInertiaValue);
        virtual Matrix3x3 InverseWorldInertiaTensor(int configurationIndex);

        virtual void AngularVelocity(Vector3d velocity);
        virtual Vector3d AngularVelocity(int configurationIndex);

        virtual void RotationalInertia(Vector3d inertiaValue);
        virtual Vector3d RotationalInertia(int configurationIndex);
    };

    inline RigidBody::RigidBody(void)
    {

    }

    inline void RigidBody::Position(Vector3d positionCenterOfMass)
    {
        aConfiguration[0].position = positionCenterOfMass;
    }

    inline Vector3d RigidBody::Position(int configurationIndex)
    {
        return aConfiguration[configurationIndex].position;
    }

    inline void RigidBody::Velocity(Vector3d newVelocity)
    {
        aConfiguration[0].velocity = newVelocity;
    }

    inline Vector3d RigidBody::Velocity(int configurationIndex)
    {
        return aConfiguration[configurationIndex].velocity;
    }

    inline void RigidBody::SumForce(Vector3d sumExternalForces)
    {
        aConfiguration[0].sumForce = sumExternalForces;
    }

    inline Vector3d RigidBody::SumForce(int configurationIndex)
    {
        return aConfiguration[configurationIndex].sumForce;
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

    inline Vector3d RigidBody::AngularMomentum(int configurationIndex)
    {
        return  aConfiguration[configurationIndex].angularMomentum;
    }

    inline void RigidBody::Torque(Vector3d torqueValue)
    {
        aConfiguration[0].torque = torqueValue;
    }

    inline Vector3d RigidBody::Torque(int configurationIndex)
    {
        return aConfiguration[configurationIndex].torque;
    }

    inline void RigidBody::Orientation(Matrix3x3 newOrientation)
    {
        aConfiguration[0].orientation = newOrientation;
    }

    inline Matrix3x3 RigidBody::Orientation(int configurationIndex)
    {
        return aConfiguration[configurationIndex].orientation;
    }

    inline void RigidBody::InverseWorldInertiaTensor(Matrix3x3 inverseInertiaValue)
    {
        aConfiguration[0].inverseWorldInertiaTensor = inverseInertiaValue;
    }

    inline Matrix3x3 RigidBody::InverseWorldInertiaTensor(int configurationIndex)
    {
        return aConfiguration[configurationIndex].inverseWorldInertiaTensor;
    }

    inline void RigidBody::AngularVelocity(Vector3d velocity)
    {
        aConfiguration[0].angularVelocity = velocity;
    }

    inline Vector3d RigidBody::AngularVelocity(int configurationIndex)
    {
        return aConfiguration[configurationIndex].angularVelocity;
    }

    inline void RigidBody::RotationalInertia(Vector3d inertiaValue)
    {
        aConfiguration[0].rotationalInertia = inertiaValue;
    }

    inline Vector3d RigidBody::RotationalInertia(int configurationIndex)
    {
        return aConfiguration[configurationIndex].rotationalInertia;
    }

}