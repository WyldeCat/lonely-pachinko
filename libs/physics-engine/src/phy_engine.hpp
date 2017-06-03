#pragma once
#include <vector>

namespace pmframework
{

    class Simulation
    {
    public:
        Simulation();
        void SimulateUnitTime(scalar DeltaTime);
        void Simulate(scalar executuionTime);
        ~Simulation(void);

        int SourceConfiguration(void);
        void SourceConfiguration(int index);
        int TargetConfiguration(void);
        void TargetConfiguration(int index);
        void AddBody(RigidBody *body);
        void AddPlane(Plane *plane);

    private:
        enum collision_state
        {
            Penetrating,
            Colliding,
            Clear
        } collisionState;

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
        collision_state CheckForCollisions(int configurationIndex);
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