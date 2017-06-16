#include "pmframework.hpp"

namespace pmframework
{
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

<<<<<<< HEAD
    /*구와 삼각형간의 sphere-triangle separate axis test입니다.
    구와 평면(무한한)의 충돌검사는 쉬웠는데 모든 mesh가 삼각형이다보니 충돌검출에서 어려움이 있었습니다.
    그러던 중 어느 글에서 SAT를 통해 구와 삼각형의 충돌검사를 하는 것을 보고 프로젝트를 하며 SAT는 볼록 다각형간의
    충돌에 쓰이는 것으로 배워 AABB, OBB등에 쓰이는 것인줄 알았기 때문에 흥미로워 써보았습니다.
    SAT알고리즘은 분리 초평면 이론에서 나온것으로, 어떠한 축에 대해서 객체들을 투영시켰을때 투영 구간이 겹친다면
    두 도형이 충돌했다고 볼 수 있습니다.

    구와 삼각형이 교차하지 않는다면, 삼각형의 특정한 점과 그 점에 가장 가까운 구의 점을 지정할 수 있습니다.
    그래서 그 점들을 이은 벡터가 seperating axis가 되고, 그 벡터를 normal로 하는 분리plane을 넣을 수 있습니다.
    따라서 모든 후보가 되는 axis들에 대해서 분리 plane을 찾을 수 없다면 구와 삼각형이 교차한다고 보면 됩니다.
    참고한 글에 따르면 분리축 검사를 해야하는 후보가 되는 축들은 아래와 같이 일곱가지가 있습니다.
    -삼각형의 normal(1가지)
    -구의 중심을 지나며 각 삼각형의 변에 수직 (3가지)
    -구의 중심을 지나며 각 삼각형의 꼭지점을 지나는 축(3가지)

    */
    bool Plane::SeperatingAxisTest(RigidBody* sphere, int config)
=======
    bool Plane::SeperatingAxisTest(RigidBody* sphere, int config) // 7-separate check
>>>>>>> origin/master
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
        //구의 중심이 삼각형으로부터 반지름보다 멀리 떨어져 있으면 구는 삼각형과 교차할 수 없다
        scalar aa = A.dotProduct(A);
        scalar ab = A.dotProduct(B);
        scalar ac = A.dotProduct(C);
        scalar bb = B.dotProduct(B);
        scalar bc = B.dotProduct(C);
        scalar cc = C.dotProduct(C);
        bool sep2 = ((aa > rr) && (ab > aa) && (ac > aa));
        bool sep3 = ((bb > rr) && (ab > bb) && (bc > bb));
        bool sep4 = ((cc > rr) && (ac > cc) && (bc > cc));
        //A와의 거리가 반지름보다 클때 교차할 수 없다.(이때, B,C가 더 가까운쪽이라면 성립하지 않으므로 A에 더 가깝다는 조건을 추가)
        //B, C에 대해서도 같은 적용을 한다.
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
        //edge에 대해서 Q를 잡는 기준은 잘 이해하지 못했습니다.
        //Q가 P로부터 반지름보다 멀리있고 점C가 PQ를 normal로 하며 선분 AB를 통과하는 평면에 대해 Q의 반대편에 있는지 검사합니다.
        //edge AB,BC,CD에 대해서 모두 분리되었는지 검사합니다.
        bool separated = sep1 || sep2 || sep3 || sep4 || sep5 || sep6 || sep7;
        return separated;
    }

    /*아래가 원래 삼각형과 구의 충돌을 구하려고 직접 짰던 함수입니다.
    일반적인 충돌검사는 가능하였지만 까다로운 케이스에서는 제대로 검출하지 못하여 결국 SAT방법을 사용했습니다
    아이디어는 삼각형과 확장시킨 삼각형(평면)과의 충돌점을 구해서 충돌점이 삼각형의 안에 있다면(넓이를 통해서 계산)
    충돌이고 그렇지 않으면 충돌하지 않은것입니다.
    아래의 함수로도 충돌검사가 잘 이루어지긴 하지만 충돌점을 기반으로 검사하기 때문에
    구와 평면사이의 거리가 임계치 이하이면 충돌로 판정하는 저희 알고리즘에서는 충돌로 판정하지만 제대로 된 충돌점을 구할 수 없었습니다.
    그래서 이 경우에 구를 조금 더 이동하던 속도로 움직여 Penetrating이 되도록 한 다음 강제로 충돌점을 만들어 적용하려 했습니다.
    하지만 삼각형이 아닌 확장된 평면에 대해 충돌점을 구하다 보니 삼각형의 edge에 걸치도록 공을 떨어트릴 경우 충돌점을 edge옆으로 잡게 되어
    올바로 충돌검사를 하지 못하는 케이스가 있었습니다.
    */
    
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