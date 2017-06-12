#include "pmframework.hpp"
/*Fix start!*/
namespace pmframework
{
    Vector3d gravity(0, -9.8f, 0);
    scalar frictionCoefficient = 0.98;

    Simulation::Simulation()
    {
        collisionType = None;
        sourceConfigurationIndex = 0;
        targetConfigurationIndex = 1;
    }

    Simulation::~Simulation(void)
    {

    }

    void Simulation::Simulate(scalar time)
    {
        scalar timeSum = 0.0f;
        scalar unitTime = 0.033f;
        for (; timeSum <= time; timeSum += 0.033f) {
            SimulateUnitTime(0.033f);
        }
    }

    void Simulation::SimulateUnitTime(scalar DeltaTime)
    {
        scalar currentTime = 0.0;
        scalar targetTime = DeltaTime;
        while (currentTime < targetTime) {

            ComputeForces(sourceConfigurationIndex);

            Integrate(targetTime - currentTime);

            //CheckForCollisions(targetConfigurationIndex);

            if (CheckForCollisions(targetConfigurationIndex) == RigidBody::Penetrating)
            {
                printf("!");
                targetTime = (currentTime + targetTime) / 2.0;

                //assert(fabs(targetTime - currentTime) > SCALAR_TOLERANCE);
            }
            else
            {
                // either colliding or clear

                currentTime = targetTime;
                targetTime = DeltaTime;

                sourceConfigurationIndex = sourceConfigurationIndex ? 0 : 1;
                targetConfigurationIndex = targetConfigurationIndex ? 0 : 1;
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

            Configuration.sumForce = Vector3d(0, 0, 0);
            Configuration.torque = Vector3d(0, 0, 0);

            Configuration.sumForce += gravity * Body->mass;
            Configuration.sumForce += (-0.002f) * Configuration.velocity;
            Configuration.torque += (-0.001f) * Configuration.angularVelocity;
        }
    }


    void Simulation::Integrate(scalar DeltaTime)
    {
        int Counter;

        for (Counter = 0; Counter < Balls.size(); Counter++)
        {
            RigidBody::configuration &Source = Balls[Counter]->aConfiguration[sourceConfigurationIndex];
            RigidBody::configuration &Target = Balls[Counter]->aConfiguration[targetConfigurationIndex];

            //HACK
            if (Balls[Counter]->collisionState != RigidBody::Clear) Source.velocity *= frictionCoefficient;

            Target.position = Source.position + DeltaTime * Source.velocity;

            Target.orientation = Source.orientation + DeltaTime * Matrix3x3(Source.angularVelocity, Matrix3x3::SkewSymmetric) * Source.orientation;

            Target.velocity = Source.velocity + (DeltaTime / Balls[Counter]->mass) * Source.sumForce;

            if ((Source.velocity.Y() < 0.0000011f || Source.velocity.Y() < 0) && 0.000001f < Target.velocity.Y() && Target.velocity.Y() < 0.8f) {
                Target.velocity.Y(0.0000011f);
            }

            Target.angularMomentum = Source.angularMomentum + DeltaTime * Source.torque;

            OrthonormalizeOrientation(Target.orientation);

            Target.inverseWorldInertiaTensor = Target.orientation * Balls[Counter]->inverseBodyInertiaTensor * Transpose(Target.orientation);

            Target.angularVelocity = Target.inverseWorldInertiaTensor * Target.angularMomentum;
        }
    }



    RigidBody::collision_state Simulation::CheckForCollisions(int ConfigurationIndex)
    {

        float const DepthEpsilon = 0.01f;

        for (int i = 0; i < Balls.size(); ++i) {
            RigidBody *Body1 = Balls[i];
            RigidBody::configuration &Configuration1 = Body1->aConfiguration[ConfigurationIndex];
            Body1->collisionState = RigidBody::Clear;

            for (int j = i + 1; j < Balls.size(); ++j) {
                RigidBody *Body2 = Balls[j];
                RigidBody::configuration &Configuration2 = Body2->aConfiguration[ConfigurationIndex];
                Body2->collisionState = RigidBody::Clear;

                Vector3d distanceVector = Configuration1.position - Configuration2.position;
                scalar distance = distanceVector.norm() - Body1->boundingSphereRadius - Body2->boundingSphereRadius;
                if (distance < -DepthEpsilon) {
                    Body1->collisionState = RigidBody::Penetrating;
                    Body2->collisionState = RigidBody::Penetrating;
                    return RigidBody::Penetrating;
                }
                else {
                    if (distance < DepthEpsilon) {
                        Body1->collisionState = RigidBody::Colliding;
                        Body2->collisionState = RigidBody::Colliding;
                        collisionType = SphereSphere;
                        collisionNormal = (Configuration1.position - Configuration2.position).normalize(SCALAR_TOLERANCE);
                        collisionBodyIndex1 = i;
                        collisionBodyIndex2 = j;

                        ResolveSphereSphereCollisions(ConfigurationIndex);

                    }
                }
            }

            for (int WallIndex = 0; WallIndex < Walls.size(); WallIndex++) {

                Plane *wall = Walls[WallIndex];

                scalar distance = wall->DistanceFromPoint(Configuration1.position) - Body1->BoundingSphereRadius();

                bool colliding;

                if (distance < -DepthEpsilon) {
                    colliding = (!(wall->SeperatingAxisTest(Body1, ConfigurationIndex)));
                    if (colliding) {
                        Body1->collisionState = RigidBody::Penetrating;
                        return RigidBody::Penetrating;
                    }
                    else {
                        //a sphere collides with the expanded trangle
                    }
                }
                else {
                    if (distance < DepthEpsilon) {
                        Vector3d vv = -(distance + 0.01) * wall->NormalVector();


                        Configuration1.position += vv;
                        scalar arar = wall->DistanceFromPoint(Configuration1.position) - Body1->BoundingSphereRadius();
                        colliding = (!(wall->SeperatingAxisTest(Body1, ConfigurationIndex)));

                        Configuration1.position -= vv;
                        if (colliding) {
                            Vector3d center = Configuration1.position;
                            scalar t = -(wall->NormalVector().dotProduct(Configuration1.position) + wall->D()) / wall->NormalVector().normSquared();
                            collisionPoint = Vector3d(wall->A()*t + center.X(), wall->B()*t + center.Y(), wall->C()*t + center.Z());
                            Body1->collisionState = RigidBody::Colliding;
                            collisionType = SpherePlane;
                            collisionNormal = wall->NormalVector();
                            collisionBodyIndex1 = i;
                            collisionPlaneIndex = WallIndex;

                            ResolveSpherePlaneCollisions(collisionPoint, ConfigurationIndex);

                        }
                        else {
                            // @todo more check
                        }
                    }
                }

            }
        }
        if (collisionType != None) return RigidBody::Colliding;
    }

    void Simulation::ResolveSphereSphereCollisions(int configurationIndex)
    {

        RigidBody *ball1 = Balls[collisionBodyIndex1];
        RigidBody *ball2 = Balls[collisionBodyIndex2];
        RigidBody::configuration &Configuration1 = ball1->aConfiguration[configurationIndex];
        RigidBody::configuration &Configuration2 = ball2->aConfiguration[configurationIndex];

        scalar im1 = 1.0 / ball1->Mass();
        scalar im2 = 1.0 / ball2->Mass();
        Vector3d v = Configuration1.velocity - Configuration2.velocity;
        scalar vn = v.dotProduct(collisionNormal);

        scalar i = (-(1.0 + 0.9) * vn) / (im1 + im2);
        Vector3d impulse = collisionNormal * i;
        Configuration1.velocity += impulse *im1;
        Configuration2.velocity -= impulse *im2;

    }


    void Simulation::ResolveSpherePlaneCollisions(Vector3d CollisionPoint, int configurationIndex)
    {
        RigidBody *ball = Balls[collisionBodyIndex1];
        RigidBody::configuration &Configuration = ball->aConfiguration[configurationIndex];

        Vector3d Position = CollisionPoint;

        Vector3d R = (Position - Configuration.position);

        Vector3d Velocity = Configuration.velocity + Configuration.angularVelocity.crossProduct(R);

        scalar ImpulseNumerator = -((1.0f) + ball->restitution) * Velocity.dotProduct(collisionNormal);

        Vector3d RR = Configuration.inverseWorldInertiaTensor * R.crossProduct(collisionNormal);

        scalar ImpulseDenominator = ((1.0f) / ball->mass) + collisionNormal.dotProduct(RR.crossProduct(R));

        Vector3d Impulse = (ImpulseNumerator / ImpulseDenominator) * collisionNormal;

        Configuration.velocity += ((1.0f) / ball->mass) * Impulse;

        //HACK
        scalar prevVelocity = ball->aConfiguration[sourceConfigurationIndex].velocity.Y();
        if ((prevVelocity < 0.0000011f || prevVelocity<0) && 0.000001f < Configuration.velocity.Y() && Configuration.velocity.Y() < 0.8f) {
            Configuration.velocity.Y(0.0000011f);
        }

        Configuration.angularMomentum += R.crossProduct(Impulse);
        Configuration.angularVelocity = Configuration.inverseWorldInertiaTensor * Configuration.angularMomentum;
    }
}