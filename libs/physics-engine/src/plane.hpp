#pragma once

namespace pmframework
{
    class Plane
    {
    private:
        scalar a, b, c, d; //ax + by + cz +d = 0
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

    void Plane::SetPlane(Vector3d p1, Vector3d p2, Vector3d p3)
    {
        point1 = p1;
        point2 = p2;
        point3 = p3;
        Vector3d v1 = p1 - p2;
        Vector3d v2 = p1 - p3;
        Vector3d normal = v2.crossProduct(v1);
        normal = normal.normalize(SCALAR_TOLERANCE);

        normalVector = normal;
        a = normal.X();
        b = normal.Y();
        c = normal.Z();
        d = -(normal.dotProduct(p1));
    }

    scalar Plane::DistanceFromPoint(Vector3d point)
    {
        scalar distance;
        distance = abs(a*point.X() + b*point.Y() + c*point.Z() + d);
        distance /= normalVector.norm();
        return distance;
    }


    bool Plane::SeperatingAxisTest(RigidBody* sphere, int config) // 7-separate check
    {
        Vector3d A = point1 - sphere->Position(config);
        Vector3d B = point2 - sphere->Position(config);
        Vector3d C = point3 - sphere->Position(config);
        scalar r = sphere->BoundingSphereRadius();
        scalar rr = r*r;
        Vector3d V = (B - A).crossProduct(C - A);
        scalar f = A.dotProduct(V);
        scalar e = V.dotProduct(V);
        bool sep1 = (f*f > rr*e);
        scalar aa = A.dotProduct(A);
        scalar ab = A.dotProduct(B);
        scalar ac = A.dotProduct(C);
        scalar bb = B.dotProduct(B);
        scalar bc = B.dotProduct(C);
        scalar cc = C.dotProduct(C);
        bool sep2 = ((aa > rr) && (ab > aa) && (ac > aa));
        bool sep3 = ((bb > rr) && (ab > bb) && (bc > bb));
        bool sep4 = ((cc > rr) && (ac > cc) && (bc > cc));
        Vector3d AB = B - A;
        Vector3d BC = C - B;
        Vector3d CA = A - C;
        scalar d1 = ab - aa;
        scalar d2 = bc - bb;
        scalar d3 = ac - cc;
        scalar e1 = AB.dotProduct(AB);
        scalar e2 = BC.dotProduct(BC);
        scalar e3 = CA.dotProduct(CA);
        Vector3d Q1 = A*e1 - d1*AB;
        Vector3d Q2 = B*e2 - d2*BC;
        Vector3d Q3 = C*e3 - d3*CA;
        Vector3d QC = C*e1 - Q1;
        Vector3d QA = A*e2 - Q2;
        Vector3d QB = B*e3 - Q3;
        bool sep5 = ((Q1.dotProduct(Q1) > rr * e1 * e1) && (Q1.dotProduct(QC) > 0));
        bool sep6 = ((Q2.dotProduct(Q2) > rr * e2 * e2) && (Q2.dotProduct(QA) > 0));
        bool sep7 = ((Q3.dotProduct(Q3) > rr * e3 * e3) && (Q3.dotProduct(QB) > 0));
        bool separated = sep1 || sep2 || sep3 || sep4 || sep5 || sep6 || sep7;
        return separated;
    }

    scalar Plane::AreaOfTriangle(Vector3d point1, Vector3d point2, Vector3d point3)
    {

        Vector3d P1 = point2 - point1;
        Vector3d P2 = point3 - point1;
        scalar Area = (P1.crossProduct(P2)).norm();
        return Area;
    }

    bool Plane::CollisionInTriangle(Vector3d collisionPoint)
    {
        scalar area = AreaOfTriangle(point1, point2, point3);
        scalar area1 = AreaOfTriangle(collisionPoint, point2, point1);
        scalar area2 = AreaOfTriangle(collisionPoint, point3, point1);
        scalar area3 = AreaOfTriangle(collisionPoint, point3, point2);
        if (area != area1 + area2 + area3) return false;
        return true;
    }

}