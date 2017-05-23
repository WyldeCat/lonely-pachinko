#include "pmframework.hpp"
using namespace pmframework;

#define TOTAL_PARTICLES 100

PointMass allParticles[TOTAL_PARTICLES];

void HandleCollision(Vector3d separationDistance, scalar changeInTime) //질점들의 collision 처리
{
    Vector3d unitNormal = separationDistance.normalize(SCALAR_TOLERANCE);// 충돌이 일어나는 면의 수직방향
    
    scalar velocity1 = allParticles[0].LinearVelocity().dotProduct(unitNormal);
    scalar velocity2 = allParticles[1].LinearVelocity().dotProduct(unitNormal);

    scalar avgElaticity = (allParticles[0].Elasticity()*allParticles[1].Elasticity()) / 2; //////곱하기 ?

    scalar finalVelocity1 = (((allParticles[0].Mass() -
                           (avgElaticity * allParticles[1].Mass()))*velocity1) +
                           ((1 + avgElaticity) * allParticles[1].Mass() * velocity2)) /
                           (allParticles[0].Mass() + allParticles[1].Mass());

    scalar finalVelocity2 = (((allParticles[1].Mass() -
                           (avgElaticity * allParticles[0].Mass()))*velocity2) +
                           ((1 + avgElaticity) * allParticles[0].Mass() * velocity1)) /
                           (allParticles[0].Mass() + allParticles[1].Mass());

    allParticles[0].LinearVelocity((finalVelocity1 - velocity1)*unitNormal + allParticles[0].LinearVelocity());
    allParticles[1].LinearVelocity((finalVelocity2 - velocity2)*unitNormal + allParticles[1].LinearVelocity());

    Vector3d acceleration1 = allParticles[0].LinearVelocity() / changeInTime;
    Vector3d acceleration2 = allParticles[1].LinearVelocity() / changeInTime;

    allParticles[0].Force(acceleration1 * allParticles[0].Mass());
    allParticles[1].Force(acceleration2 * allParticles[1].Mass());
}