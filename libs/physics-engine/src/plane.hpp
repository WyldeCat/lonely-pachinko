#pragma once
//#include "pmframework.hpp"

namespace pmframework
{
class Plane
{
private:
    scalar a, b, c, d; //ax + by + cz +d = 0
    Vector3d normalVector;
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

    Plane SetPlane(Vector3d p1, Vector3d p2, Vector3d p3);

    scalar DistanceFromPoint(Vector3d point);
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

Plane Plane::SetPlane(Vector3d p1, Vector3d p2, Vector3d p3)
{
    Vector3d v1 = p1 - p2;
    Vector3d v2 = p1 - p3;
    Vector3d normal = v1.crossProduct(v2);
    normal.normalize(SCALAR_TOLERANCE);
    normalVector = normal;
    Plane p;
    p.A(normal.X());
    p.B(normal.Y());
    p.C(normal.Z());
    p.D(-(normal.dotProduct(p1)));
    return p;
}

scalar Plane::DistanceFromPoint(Vector3d point)
{
    scalar distance;
    distance = abs(a*point.X() + b*point.Y() + c*point.Z() + d);
    distance /= point.norm();
    return distance;
}


}