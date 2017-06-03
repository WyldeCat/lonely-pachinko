#include "pmframework.hpp"
#include <iostream>

using namespace pmframework;

int main()
{
    Simulation simulation;
    RigidBody *ball1 = new RigidBody;

    scalar dx = 0;
    scalar dy = 0;
    scalar dz = 5;

    ball1->Position(Vector3d(dx, dy, dz));
    ball1->Mass(10);

    Matrix3x3 m;
    m(0, 0) = (3.0 / ball1->Mass())*(dy*dy + dz*dz);
    m(1, 1) = (3.0 / ball1->Mass())*(dx*dx + dz*dz);
    m(2, 2) = (3.0 / ball1->Mass())*(dx*dx + dy*dy);

    ball1->InverseBodyInertiaTensor(m);

    ball1->Restitution(0.8);
    ball1->Velocity(Vector3d(10, 0, 0));
    ball1->RotationalInertia(Vector3d(1, 2, 3));
    simulation.AddBody(ball1);


    /*RigidBody *ball2 = new RigidBody;
    dx = 51;
    dy = 3;
    dz = 50;
    ball2->Position(Vector3d(dx, dy, dz));
    ball2->Mass(10);
    ball2->InverseBodyInertiaTensor(m);
    ball2->Restitution(0.8);
    ball2->Velocity(Vector3d(0, -1, 0));
    ball2->RotationalInertia(Vector3d(1, 2, 3));
    simulation.AddBody(ball2);


    RigidBody *ball3 = new RigidBody;
    dx = 10;
    dy = 0;
    dz = 10;
    ball3->Position(Vector3d(dx, dy, dz));
    ball3->Mass(15);
    ball3->InverseBodyInertiaTensor(m);
    ball3->Restitution(0.8);
    ball3->Velocity(Vector3d(0, 0, 0));
    ball3->RotationalInertia(Vector3d(1, 2, 3));
    simulation.AddBody(ball3);
    */

    Plane *plane1 = new Plane;
    plane1->SetPlane(Vector3d(10000, -1, 10000), Vector3d(10000, -1, -10000), Vector3d(-10000, -1, 10000));
    simulation.AddPlane(plane1);


    Plane *plane2 = new Plane;
    plane2->SetPlane(Vector3d(10, -1, 1000), Vector3d(10, -1, -1000), Vector3d(10, 1000, 1000));
    simulation.AddPlane(plane2);

    for (;;) {
        std::cout << "Point  X : " << ball1->Position(simulation.SourceConfiguration()).X() <<
            " Y : " << ball1->Position(simulation.SourceConfiguration()).Y() <<
            " Z : " << ball1->Position(simulation.SourceConfiguration()).Z() <<
            " ||| Velocity  X : " << ball1->Velocity(simulation.SourceConfiguration()).X() <<
            " Y : " << ball1->Velocity(simulation.SourceConfiguration()).Y() <<
            " Z : " << ball1->Velocity(simulation.SourceConfiguration()).Z();

        //simulation.SimulateUnitTime(0.033f);
        simulation.Simulate(1);
        getchar();
    }

}