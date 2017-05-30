#include <iostream>
#include "pmframework.hpp"
using namespace pmframework;

namespace pmframework
{

    Vector3d gravity(0, -9.8f, 0);

    Simulation::~Simulation(void)
    {
        
    }

    void Simulation::Simulate(scalar DeltaTime)
    {
        scalar currentTime = 0.0;
        scalar targetTime = DeltaTime;
        while (currentTime < targetTime) {
            ComputeForces(SourceConfiguration());

            Integrate(targetTime - currentTime);

            CheckForCollisions(TargetConfiguration());

            if (CollisionState == Penetrating)
            {
                targetTime = (currentTime + targetTime) / 2.0;

                assert(fabs(targetTime - currentTime) > SCALAR_TOLERANCE);
            }
            else
            {
                // either colliding or clear

                if (CollisionState == Colliding)
                {

                    int Counter = 0;
                    do
                    {
                        if (CollisionType == SphereSphere)
                            ResolveSphereSphereCollisions(TargetConfiguration());
                        else if (CollisionType == SpherePlane)
                            ResolveSpherePlaneCollisions(CollisionPoint(), TargetConfiguration());
                        Counter++;
                    } while ((CheckForCollisions(TargetConfiguration()) == Colliding) && (Counter < 100));

                    assert(Counter < 100);
                }

                currentTime = targetTime;
                targetTime = DeltaTime;

                SourceConfiguration((SourceConfiguration() ? 0 : 1));
                TargetConfiguration((TargetConfiguration() ? 0 : 1));
            }
        }
    }

    void Simulation::ComputeForces(int ConfigurationIndex)
    {
        int Counter;

        for (Counter = 0; Counter < Balls.size(); Counter++)
        {
            RigidBody* Body = Balls[Counter];
            RigidBody::configuration &Configuration = Body->aConfiguration[ConfigurationIndex];
            // clear forces
            Configuration.torque = Vector3d(0, 0, 0);
            Configuration.sumForce = Vector3d(0, 0, 0);

            Configuration.sumForce += gravity * Body->mass;
            Configuration.sumForce += (-0.002f) * Configuration.velocity;
            Configuration.torque += (-0.001f) * Configuration.angularVelocity;
        }
    }

    /*----------------------------------------------------------------------------

    Integrate - integrate the rigid body configurations forward in time from
    source config to target config

    @todo calculate initial derivatives _once_
    @todo use something better than Euler's method

    */

    void Simulation::Integrate(scalar DeltaTime)
    {
        int Counter;

        for (Counter = 0; Counter < Balls.size(); Counter++)
        {
            RigidBody::configuration &Source = Balls[Counter]->aConfiguration[SourceConfiguration()];
            RigidBody::configuration &Target = Balls[Counter]->aConfiguration[TargetConfiguration()];

            // integrate primary quantities

            Target.position = Source.position + DeltaTime * Source.velocity;

            Target.orientation = Source.orientation + DeltaTime * Matrix3x3(Source.angularVelocity, Matrix3x3::SkewSymmetric) * Source.orientation;

            Target.velocity = Source.velocity + (DeltaTime / Balls[Counter]->mass) * Source.sumForce;

            Target.angularMomentum = Source.angularMomentum + DeltaTime * Source.torque;

            OrthonormalizeOrientation(Target.orientation);

            // compute auxiliary quantities

            Target.inverseWorldInertiaTensor = Target.orientation * Balls[Counter]->inverseBodyInertiaTensor * Transpose(Target.orientation);

            Target.angularVelocity = Target.inverseWorldInertiaTensor * Target.angularMomentum;
        }
    }


    /*----------------------------------------------------------------------------

    CheckForCollisions - test the current configuration for collisions

    @todo handle multiple simultaneous collisions

    */


    Simulation::collision_state Simulation::CheckForCollisions(int ConfigurationIndex)
    {
        CollisionState = Clear;
        float const DepthEpsilon = 0.001f;

        for (int i = 0; (i < Balls.size() - 1) && (CollisionState != Penetrating); ++i) {
            RigidBody *Body1 = Balls[i];
            RigidBody::configuration &Configuration1 = Body1->aConfiguration[ConfigurationIndex];
            for (int j = i + 1; j < Balls.size() && (CollisionState != Penetrating); ++j) {
                RigidBody *Body2 = Balls[j];
                RigidBody::configuration &Configuration2 = Body2->aConfiguration[ConfigurationIndex];

                Vector3d distanceVector = Configuration1.position - Configuration2.position;
                scalar distance = distanceVector.norm() - Body1->boundingSphereRadius - Body2->boundingSphereRadius;
                if (distance < -DepthEpsilon) {
                    CollisionState = Penetrating;
                }
                else {
                    if (distance < DepthEpsilon) {
                        CollisionState = Colliding;
                        CollisionType = SphereSphere;
                        collisionBodyIndex1 = i;
                        collisionBodyIndex2 = j;
                    }
                }
            }

            for (int WallIndex = 0; (WallIndex < Walls.size()) && (CollisionState != Penetrating); WallIndex++) {

                Plane *wall = Walls[WallIndex];

                scalar distance = wall->DistanceFromPoint(Configuration1.position);

                if (distance < -DepthEpsilon)
                {
                    CollisionState = Penetrating;
                }
                else {
                    if (distance < DepthEpsilon)
                    {
                        Vector3d center = Configuration1.position;
                        scalar t = -(wall->NormalVector().dotProduct(Configuration1.position) + wall->D())/wall->NormalVector().normSquared();
                        CollisionPoint ( Vector3d(wall->A()*t + center.X(), wall->B()*t + center.Y(), wall->C()*t + center.Z()) );
                        CollisionState = Colliding;
                        CollisionType = SpherePlane;
                        collisionNormal = wall->NormalVector();
                        collisionBodyIndex1 = i;
                        collisionPlaneIndex = WallIndex;
                    }
                }
            }
        }
        return CollisionState;
    }

    void Simulation::ResolveSphereSphereCollisions(int configurationIndex)
    {
        RigidBody *ball1 = Balls[collisionBodyIndex1];
        RigidBody *ball2 = Balls[collisionBodyIndex2];
        RigidBody::configuration &Configuration1 = ball1->aConfiguration[configurationIndex];
        RigidBody::configuration &Configuration2 = ball2->aConfiguration[configurationIndex];

        scalar averageElasticity = (ball1->Restitution() + ball2->Restitution()) / 2;

        Vector3d relativeVelocity = ball1->AngularVelocity() - ball2->AngularVelocity();
        Vector3d numerator = -1 * relativeVelocity * (averageElasticity + 1);

        Vector3d unitNormal = ball1->Position() - ball2->Position();
        unitNormal = unitNormal.normalize(SCALAR_TOLERANCE);

        Vector3d forceLocation2 = unitNormal * ball2->BoundingSphereRadius();
        Vector3d tempVector = forceLocation2.crossProduct(unitNormal);

        tempVector.X(tempVector.X() / ball2->RotationalInertia().X());
        tempVector.Y(tempVector.Y() / ball2->RotationalInertia().Y());
        tempVector.Z(tempVector.Z() / ball2->RotationalInertia().Z());

        tempVector = tempVector.crossProduct(forceLocation2);

        scalar part1 = unitNormal.dotProduct(tempVector);

        unitNormal *= -1;
        Vector3d forceLocation1 = unitNormal * ball1->BoundingSphereRadius();

        tempVector = forceLocation1.crossProduct(unitNormal);

        tempVector.X(tempVector.X() / ball1->RotationalInertia().X());
        tempVector.Y(tempVector.Y() / ball1->RotationalInertia().Y());
        tempVector.Z(tempVector.Z() / ball1->RotationalInertia().Z());

        tempVector = tempVector.crossProduct(forceLocation1);

        scalar part2 = unitNormal.dotProduct(tempVector);

        scalar denominator = 1 / ball1->Mass() + 1 / ball2->Mass() + part2 + part1;

        Vector3d impulseForce = (numerator / denominator);
        ball1->SumForce(impulseForce);
        ball2->SumForce(-1 * impulseForce);
    }

    void Simulation::ResolveSpherePlaneCollisions(Vector3d CollisionPoint, int configurationIndex)
    {
        RigidBody *ball = Balls[collisionBodyIndex1];
        RigidBody::configuration &Configuration = ball->aConfiguration[configurationIndex];

        Vector3d Position = CollisionPoint;

        Vector3d R = Position - Configuration.position;

        Vector3d Velocity = Configuration.velocity + Configuration.angularVelocity.crossProduct(R);

        scalar ImpulseNumerator = -((1.0f) + ball->restitution) * Velocity.dotProduct(collisionNormal);

        scalar ImpulseDenominator = (1.0f) / ball->mass + collisionNormal.dotProduct((Configuration.inverseWorldInertiaTensor * R.crossProduct(collisionNormal)).crossProduct(R));

        Vector3d Impulse = (ImpulseNumerator / ImpulseDenominator) * collisionNormal;

        // apply impulse to primary quantities
        Configuration.velocity += (1.0f) / ball->mass * Impulse;
        Configuration.angularMomentum += R.crossProduct(Impulse);

        // compute affected auxiliary quantities
        Configuration.angularVelocity = Configuration.inverseWorldInertiaTensor * Configuration.angularMomentum;
    }
  
}