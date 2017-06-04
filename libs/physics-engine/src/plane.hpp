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
        Plane(void);

        void A(scalar aComponent);
        scalar A(void);

        void B(scalar bComponent);
        scalar B(void);

        void C(scalar cComponent);
        scalar C(void);

        void D(scalar dComponenet);
        scalar D(void);

        void NormalVector(Vector3d normal);
        Vector3d NormalVector(void);

        void SetPlane(Vector3d p1, Vector3d p2, Vector3d p3);

        scalar DistanceFromPoint(Vector3d point);

        bool SeperatingAxisTest(RigidBody *sphere, int config);

        scalar AreaOfTriangle(Vector3d point1, Vector3d point2, Vector3d point3);

        bool CollisionInTriangle(Vector3d collisionPoint);
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