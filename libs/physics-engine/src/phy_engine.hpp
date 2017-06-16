#pragma once
#include "pmframework.hpp"
#include <vector>

namespace pmframework
{

    class Simulation
    {
    public:
        PHYSICSENGINE_API Simulation();
        PHYSICSENGINE_API void SimulateUnitTime(scalar DeltaTime);
        PHYSICSENGINE_API void Simulate(scalar executuionTime);
        PHYSICSENGINE_API ~Simulation(void);

        PHYSICSENGINE_API int SourceConfiguration(void);
        PHYSICSENGINE_API void SourceConfiguration(int index);
        PHYSICSENGINE_API int TargetConfiguration(void);
        PHYSICSENGINE_API void TargetConfiguration(int index);
        PHYSICSENGINE_API void AddBody(RigidBody *body);
        PHYSICSENGINE_API void AddPlane(Plane *plane);

    private:
<<<<<<< HEAD
=======
        /*enum collision_state
        {
            Penetrating,
            Colliding,
            Clear
        } collisionState;*/
>>>>>>> origin/master

        enum collision_type
        {
            None,
            SphereSphere,
            SpherePlane
        } collisionType;

        Vector3d collisionPoint;
        Vector3d collisionNormal;
        int collisionBodyIndex1;
        int collisionBodyIndex2;
        int collisionPlaneIndex;

        int sourceConfigurationIndex;
        int targetConfigurationIndex;

        std::vector <RigidBody *> Balls;
        std::vector <Plane *> Walls;

        void ComputeForces(int configurationIndex);
        void Integrate(scalar DeltaTime);
        RigidBody::collision_state CheckForCollisions(int configurationIndex);
        void ResolveSpherePlaneCollisions(Vector3d collisionPoint, int configurationIndex);
        void ResolveSphereSphereCollisions(int configurationIndex);

    };

    inline int Simulation::SourceConfiguration(void)
    {
        return sourceConfigurationIndex;
    }

    inline void Simulation::SourceConfiguration(int newIndex)
    {
        sourceConfigurationIndex = newIndex;
    }

    inline int Simulation::TargetConfiguration(void)
    {
        return targetConfigurationIndex;
    }

    inline void Simulation::TargetConfiguration(int newIndex)
    {
        targetConfigurationIndex = newIndex;
    }

    inline void Simulation::AddBody(RigidBody * body)
    {
        Balls.push_back(body);
    }

    inline void Simulation::AddPlane(Plane *plane)
    {
        Walls.push_back(plane);
    }

}