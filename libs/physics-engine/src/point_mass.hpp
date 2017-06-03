#pragma once

namespace pmframework
{

    class PointMass
    {
    protected:

        enum { numberOfConfigurations = 2 };

        scalar mass;
        scalar restitution;
        scalar boundingSphereRadius;

        struct configuration {
            Vector3d position;
            Vector3d velocity;
            Vector3d sumForce;
        };


    private:
        configuration aConfiguration[numberOfConfigurations];

    public:

        PointMass(void);

        void Mass(scalar massValue);
        scalar Mass(void);

        void BoundingSphereRadius(scalar sphereRadius);
        scalar BoundingSphereRadius(void);

        void Restitution(scalar elasticity);
        scalar Restitution(void);

        void Position(Vector3d positionCenterOfMass);
        Vector3d Position(int configurationIndex);

        void Velocity(Vector3d newVelocity);
        Vector3d Velocity(int configurationIndex);

        void SumForce(Vector3d sumExternalForces);
        Vector3d SumForce(int configurationIndex);
    };


    inline PointMass::PointMass(void)
    {
        mass = 1.0;
        boundingSphereRadius = 1.0;
        restitution = 0.9;
    }


    inline void PointMass::Mass(scalar massValue)
    {
        assert(massValue > 0.0);
        mass = massValue;
    }

    inline scalar PointMass::Mass(void)
    {
        return mass;
    }

    inline void PointMass::Position(Vector3d positionCenterOfMass)
    {
        aConfiguration[0].position = positionCenterOfMass;
    }

    inline Vector3d PointMass::Position(int configurationIndex)
    {
        return aConfiguration[configurationIndex].position;
    }

    inline void PointMass::Velocity(Vector3d newVelocity)
    {
        aConfiguration[0].velocity = newVelocity;
    }

    inline Vector3d PointMass::Velocity(int configurationIndex)
    {
        return aConfiguration[configurationIndex].velocity;
    }

    inline void PointMass::SumForce(Vector3d sumExternalForces)
    {
        aConfiguration[0].sumForce = sumExternalForces;
    }

    inline Vector3d PointMass::SumForce(int configurationIndex)
    {
        return aConfiguration[configurationIndex].sumForce;
    }

    inline void PointMass::BoundingSphereRadius(scalar sphereRadius)
    {
        boundingSphereRadius = sphereRadius;
    }

    inline scalar PointMass::BoundingSphereRadius(void)
    {
        return boundingSphereRadius;
    }

    inline void PointMass::Restitution(scalar elasticity)
    {
        restitution = elasticity;
    }

    inline scalar PointMass::Restitution(void)
    {
        return restitution;
    }

}