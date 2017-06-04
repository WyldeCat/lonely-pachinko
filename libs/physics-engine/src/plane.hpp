#pragma once

namespace pmframework
{
    class Plane
    {
    private:
        scalar a, b, c, d; //Plane equation : ax + by + cz +d = 0
        Vector3d normalVector;
        Vector3d point1;
        Vector3d point2;
        Vector3d point3;
    public:
        PHYSICSENGINE_API Plane(void);

        PHYSICSENGINE_API void A(scalar aComponent);
        PHYSICSENGINE_API scalar A(void);

        PHYSICSENGINE_API void B(scalar bComponent);
        PHYSICSENGINE_API scalar B(void);

        PHYSICSENGINE_API void C(scalar cComponent);
        PHYSICSENGINE_API scalar C(void);

        PHYSICSENGINE_API void D(scalar dComponenet);
        PHYSICSENGINE_API scalar D(void);

        PHYSICSENGINE_API void NormalVector(Vector3d normal);
        PHYSICSENGINE_API Vector3d NormalVector(void);

        PHYSICSENGINE_API void SetPlane(Vector3d p1, Vector3d p2, Vector3d p3);

        PHYSICSENGINE_API scalar DistanceFromPoint(Vector3d point);

        PHYSICSENGINE_API bool SeperatingAxisTest(RigidBody *sphere, int config);

        PHYSICSENGINE_API scalar AreaOfTriangle(Vector3d point1, Vector3d point2, Vector3d point3);

        PHYSICSENGINE_API bool CollisionInTriangle(Vector3d collisionPoint);
    };

    inline Plane::Plane(void)
    {
        a = b = c = d = 0;
    }

    inline void Plane::A(scalar aComponent)
    {
        a = aComponent;
    }

    inline scalar Plane::A(void)
    {
        return a;
    }

    inline void Plane::B(scalar bComponent)
    {
        b = bComponent;
    }

    inline scalar Plane::B(void)
    {
        return b;
    }

    inline void Plane::C(scalar cComponent)
    {
        c = cComponent;
    }

    inline scalar Plane::C(void)
    {
        return c;
    }

    inline void Plane::D(scalar dComponent)
    {
        d = dComponent;
    }

    inline scalar Plane::D(void)
    {
        return d;
    }

    inline void Plane::NormalVector(Vector3d normal)
    {
        normalVector = normal;
    }

    inline Vector3d Plane::NormalVector(void)
    {
        return normalVector;
    }


}