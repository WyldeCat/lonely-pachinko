#include "pmframework.hpp"
<<<<<<< HEAD

/* simulation�� ��ü���� �帧�� chris hacker�� �����Ͽ����ϴ�.
* http://chrishecker.com/images/e/e7/Gdmphys3.pdf
* http://chrishecker.com/Rigid_Body_Dynamics
������ project�� ���缭 sphere, plane class�� ���Ͽ� �߰��ϰ� �����Ͽ����ϴ�
������ ���� ȿ���� �־���, ǥ����� �������� �浹�� ���� �ణ�� ���������� �����Ͽ����ϴ�
ó������ ���� ǥ�鿡 ��� ������ �ξ� ȸ�� ��� �����Ϸ� �Ͽ�����
�ᱹ ���� �߽ɿ��� �����Ͽ��� ��� ��� ������� �ǵ��� ����Ͽ����ϴ�.

���� ���� �浹�� ������ �������� �Ÿ��� �����Ͽ���, resolve�� ���� ����� resolve�� �Ȱ��� ������ ����Ͽ��µ�
���׸� ���� ���Ͽ� �� �����ϰ� ��ݷ��� ����Ͽ����ϴ�.
���� ����� �浹�� SAT�� ���� �����Ͽ���, resolve�� �Լ��� ���Ǻκп� �ִ� url�� �����Ͽ� ����Ͽ����ϴ�.
*/

=======
/*Fix start!*/
>>>>>>> origin/master
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
        scalar unitTime = 0.02f;
        for (; timeSum <= time; timeSum += 0.02f) {
            SimulateUnitTime(0.02f);
        }
    }

    void Simulation::SimulateUnitTime(scalar DeltaTime)
    {
        scalar currentTime = 0.0;
        scalar targetTime = DeltaTime;
        while (currentTime < targetTime) {

            ComputeForces(sourceConfigurationIndex);

            Integrate(targetTime - currentTime);

<<<<<<< HEAD
=======
            //CheckForCollisions(targetConfigurationIndex);

>>>>>>> origin/master
            if (CheckForCollisions(targetConfigurationIndex) == RigidBody::Penetrating)
            {
                printf("!");
                targetTime = (currentTime + targetTime) / 2.0;
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
        int i;

        for (i = 0; i < Balls.size(); i++)
        {
            RigidBody* Body = Balls[i];
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
        int i;

        for (i = 0; i < Balls.size(); ++i)
        {
            RigidBody::configuration &Source = Balls[i]->aConfiguration[sourceConfigurationIndex];
            RigidBody::configuration &Target = Balls[i]->aConfiguration[targetConfigurationIndex];

            //HACK
<<<<<<< HEAD
            if (Balls[i]->collisionState != RigidBody::Clear) Source.velocity *= frictionCoefficient;
=======
            if (Balls[Counter]->collisionState != RigidBody::Clear) Source.velocity *= frictionCoefficient;
>>>>>>> origin/master

            Target.position = Source.position + DeltaTime * Source.velocity;

            Target.orientation = Source.orientation + DeltaTime * Matrix3x3(Source.angularVelocity, Matrix3x3::SkewSymmetric) * Source.orientation;

            Target.velocity = Source.velocity + (DeltaTime / Balls[i]->mass) * Source.sumForce;

            if ((Source.velocity.Y() < 0.0000011f || Source.velocity.Y() < 0) && 0.000001f < Target.velocity.Y() && Target.velocity.Y() < 0.8f) {
                Target.velocity.Y(0.0000011f);
            }

            if ((Source.velocity.Y() < 0.0000011f || Source.velocity.Y() < 0) && 0.000001f < Target.velocity.Y() && Target.velocity.Y() < 0.8f) {
                Target.velocity.Y(0.0000011f);
            }

            Target.angularMomentum = Source.angularMomentum + DeltaTime * Source.torque;

            OrthonormalizeOrientation(Target.orientation);

            Target.inverseWorldInertiaTensor = Target.orientation * Balls[i]->inverseBodyInertiaTensor * Transpose(Target.orientation);

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

<<<<<<< HEAD
            for (int j = 0; j < Walls.size(); ++j) {
=======
            for (int WallIndex = 0; WallIndex < Walls.size(); WallIndex++) {
>>>>>>> origin/master

                Plane *wall = Walls[j];

                scalar distance = wall->DistanceFromPoint(Configuration1.position) - Body1->BoundingSphereRadius();

                bool colliding;

                if (distance < -DepthEpsilon) {
                    colliding = (!(wall->SeperatingAxisTest(Body1, ConfigurationIndex)));
                    if (colliding) {
                        Body1->collisionState = RigidBody::Penetrating;
                        return RigidBody::Penetrating;
<<<<<<< HEAD
=======
                    }
                    else {
                        //a sphere collides with the expanded trangle
>>>>>>> origin/master
                    }
                }
                else {
                    if (distance < DepthEpsilon) {
<<<<<<< HEAD
                        /*
                        Vector3d vv = -(distance + 0.01) * wall->NormalVector();
                        Configuration1.position += vv;
                        Vector3d center = Configuration1.position;
                        scalar t = -(wall->NormalVector().dotProduct(Configuration1.position) + wall->D()) / wall->NormalVector().normSquared();
                        collisionPoint = Vector3d(wall->A()*t + center.X(), wall->B()*t + center.Y(), wall->C()*t + center.Z());
                        colliding = wall->CollisionInTriangle(collisionPoint);
                        Configuration1.position -= vv;*/
                        colliding = wall->CollisionInTriangle(collisionPoint);

=======
                        Vector3d vv = -(distance + 0.01) * wall->NormalVector();


                        Configuration1.position += vv;
                        scalar arar = wall->DistanceFromPoint(Configuration1.position) - Body1->BoundingSphereRadius();
                        colliding = (!(wall->SeperatingAxisTest(Body1, ConfigurationIndex)));

                        Configuration1.position -= vv;
>>>>>>> origin/master
                        if (colliding) {
                            Vector3d center = Configuration1.position;
                            scalar t = -(wall->NormalVector().dotProduct(Configuration1.position) + wall->D()) / wall->NormalVector().normSquared();
                            collisionPoint = Vector3d(wall->A()*t + center.X(), wall->B()*t + center.Y(), wall->C()*t + center.Z());
                            Body1->collisionState = RigidBody::Colliding;
                            collisionType = SpherePlane;
                            collisionNormal = wall->NormalVector();
                            collisionBodyIndex1 = i;
                            collisionPlaneIndex = j;

                            ResolveSpherePlaneCollisions(collisionPoint, ConfigurationIndex);

                        }
                        else {
                            //�ﰢ���� edge���� �浹�� �߰������� �ʿ��մϴ�. -> bug�� ����
                        }
                    }
                }

            }
        }
        if (collisionType != None) return RigidBody::Colliding;
    }

    // http://gafferongames.com/virtual-go/collision-response-and-coulomb-friction/ �� �߰��� �ִ� ���� �����Ͽ����ϴ�.
    void Simulation::ResolveSphereSphereCollisions(int configurationIndex)
    {

        RigidBody *ball1 = Balls[collisionBodyIndex1];
        RigidBody *ball2 = Balls[collisionBodyIndex2];
        RigidBody::configuration &Configuration1 = ball1->aConfiguration[configurationIndex];
        RigidBody::configuration &Configuration2 = ball2->aConfiguration[configurationIndex];
        /*
        Vector3d v = Configuration1.velocity - Configuration2.velocity;

        scalar inv_m1 = 1.0 / ball1->Mass();
        Vector3d r1 = collisionPoint - Configuration1.position;
        Vector3d rr1 = ball1->inverseBodyInertiaTensor * r1.crossProduct(collisionNormal);

        scalar inv_m2 = 1.0 / ball2->Mass();
        Vector3d r2 = collisionPoint - Configuration2.position;
        Vector3d rr2 = ball2->inverseBodyInertiaTensor * r2.crossProduct(collisionNormal);

        scalar impulseDenominator = inv_m1 + inv_m2 + (rr1.crossProduct(r1) + rr2.crossProduct(r2)).dotProduct(collisionNormal);

        scalar j1 = (v * (-(1.0 + ball1->restitution))).dotProduct(v) / impulseDenominator;
        scalar j2 = (v * (-(1.0 + ball1->restitution))).dotProduct(v) / impulseDenominator;

        Vector3d impulse1 = collisionNormal * j1;
        Vector3d impulse2 = collisionNormal * j2;
        Configuration1.velocity += impulse1 *inv_m1;
        Configuration2.velocity -= impulse2 *inv_m2;
        */
        //bug�� ���� ���Ͽ� �� �����ϰ� ���Ͽ����ϴ�.
        scalar inv_m1 = 1.0 / ball1->Mass();
        scalar inv_m2 = 1.0 / ball2->Mass();
        Vector3d v = Configuration1.velocity - Configuration2.velocity;
        scalar vn = v.dotProduct(collisionNormal);
        scalar nn = collisionNormal.dotProduct(collisionNormal);

        scalar j1 = (-(1.0 + ball1->restitution) * vn) / (nn*(inv_m1 + inv_m2));
        scalar j2 = (-(1.0 + ball1->restitution) * vn) / (nn*(inv_m1 + inv_m2));
        Vector3d impulse1 = collisionNormal * j1;
        Vector3d impulse2 = collisionNormal * j2;
        Configuration1.velocity += impulse1 *inv_m1;
        Configuration2.velocity -= impulse2 *inv_m2;

    }

    // http://gafferongames.com/virtual-go/collision-response-and-coulomb-friction/ �� �߰��� �ִ� ���� �����Ͽ����ϴ�.
    // ���� plane�� �浹�̹Ƿ� ����� �ӵ��� 0, ������ ���Ѵ�� �����Ͽ������� �� �Ʒ��� ���� ������ ����� �� �ֽ��ϴ�.

    void Simulation::ResolveSpherePlaneCollisions(Vector3d CollisionPoint, int configurationIndex)
    {
        RigidBody *ball = Balls[collisionBodyIndex1];
        RigidBody::configuration &Configuration = ball->aConfiguration[configurationIndex];

        Vector3d p = CollisionPoint;

        Vector3d r = (p - Configuration.position);

        Vector3d v = Configuration.velocity;

        scalar impulseNumerator = -((1.0f) + ball->restitution) * v.dotProduct(collisionNormal);

        Vector3d rr = ball->inverseBodyInertiaTensor * r.crossProduct(collisionNormal);

        scalar impulseDenominator = ((1.0f) / ball->mass) + collisionNormal.dotProduct(rr.crossProduct(r));

        Vector3d impulse = (impulseNumerator / impulseDenominator) * collisionNormal;

<<<<<<< HEAD
        Configuration.velocity += ((1.0f) / ball->mass) * impulse;
=======
        Configuration.velocity += ((1.0f) / ball->mass) * Impulse;
>>>>>>> origin/master

        //HACK
        scalar prevVelocity = ball->aConfiguration[sourceConfigurationIndex].velocity.Y();
        if ((prevVelocity < 0.0000011f || prevVelocity<0) && 0.000001f < Configuration.velocity.Y() && Configuration.velocity.Y() < 0.8f) {
            Configuration.velocity.Y(0.0000011f);
        }
<<<<<<< HEAD
=======

        Configuration.angularMomentum += R.crossProduct(Impulse);
        Configuration.angularVelocity = Configuration.inverseWorldInertiaTensor * Configuration.angularMomentum;
>>>>>>> origin/master
    }
}