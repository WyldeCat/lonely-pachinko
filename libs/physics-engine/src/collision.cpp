#include "pmframework.hpp"
using namespace pmframework;

collision_status collision::CollisionCheck(void) //collision check
{
    scalar distance;
    Vector3d distanceVector;
    collision_status collisionStatus = COLLISION_NONE;

    distanceVector = object1->Location() - object2->Location();
    distance = abs(distanceVector.norm()) -
               object1->BoundingSphereRadius() -
               object2->BoundingSphereRadius();

    if (CloseToZero(distance)){
        collisionStatus = COLLISION_TOUCHING;
    }
    else if (distance < 0.0){
        collisionStatus = COLLISION_OVERLAPPING;
    }
    return collisionStatus;
}

bool collision::CalculateReactions(void) // 강체들의 collision 처리
{
    float averageElasticity = (object1->CoefficientOfRestitution() +
                               object2->CoefficientOfRestitution()) / 2;

    Vector3d relativeVelocity = object1->AngularVelocity() - object2->AngularVelocity();
    Vector3d numerator = -1 * relativeVelocity * (averageElasticity + 1);

    Vector3d unitNormal = object1->Location() - object2->Location();
    unitNormal = unitNormal.normalize(SCALAR_TOLERANCE);

    Vector3d forceLocation2 = unitNormal * object2->BoundingSphereRadius();
    Vector3d tempVector = forceLocation2.crossProduct(unitNormal);

    tempVector.X(tempVector.X() / object2->RotationalInertia().X());
    tempVector.Y(tempVector.Y() / object2->RotationalInertia().Y());
    tempVector.Z(tempVector.Z() / object2->RotationalInertia().Z());

    tempVector = tempVector.crossProduct(forceLocation2);

    float part1 = unitNormal.dotProduct(tempVector);

    unitNormal *= -1;
    Vector3d forceLocation1 = unitNormal * object1->BoundingSphereRadius();

    tempVector = forceLocation1.crossProduct(unitNormal);

    tempVector.X(tempVector.X() / object1->RotationalInertia().X());
    tempVector.Y(tempVector.Y() / object1->RotationalInertia().Y());
    tempVector.Z(tempVector.Z() / object1->RotationalInertia().Z());

    tempVector = tempVector.crossProduct(forceLocation1);

    scalar part2 = unitNormal.dotProduct(tempVector);

    scalar denominator = 1 / object1->Mass() + 1 / object2->Mass() + part2 + part1;
    
    force impulseForce;
    impulseForce.Force(numerator / denominator);
    impulseForce.ApplicationPoint(forceLocation1);
    
    Vector3d existingForce = object1->Force().Force();
    
    force totalForce;
    totalForce.Force(existingForce + impulseForce.Force());
    object1->Force(totalForce);

    existingForce = object2->Force().Force();
    totalForce.Force(existingForce - impulseForce.Force());
    object2->Force(totalForce);

    return true;
}