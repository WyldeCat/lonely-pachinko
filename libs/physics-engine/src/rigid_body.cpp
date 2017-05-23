#include "pmframework.hpp"

namespace pmframework
{
    bool RigidBody::Update(scalar changeInTime)
    {
        assert(mass > 0);

        linearAcceleration = sumForces.Force() / mass;

        linearVelocity += linearAcceleration * changeInTime;

        centerOfMass += linearVelocity * changeInTime;

        //need Translate

        torque = sumForces.ApplicationPoint().crossProduct(sumForces.Force());

        angularAcceleration.X(torque.X() / rotationalInertia.X());
        angularAcceleration.Y(torque.Y() / rotationalInertia.Y());
        angularAcceleration.Z(torque.Z() / rotationalInertia.Z());

        angularVelocity += angularAcceleration * changeInTime;

        currentOrientation.XAngle(currentOrientation.XAngle() + angularVelocity.X() * changeInTime);
        currentOrientation.YAngle(currentOrientation.YAngle() + angularVelocity.Y() * changeInTime);
        currentOrientation.ZAngle(currentOrientation.ZAngle() + angularVelocity.Z() * changeInTime);

        //need rotation


        return true;
    }
    
    bool RigidBody::Render(void)
    {
        //save world transformation matrix
        //apply current world trans- to the obj
        //render
        //restore world matrix
        
        //return renderedOK
    }

}