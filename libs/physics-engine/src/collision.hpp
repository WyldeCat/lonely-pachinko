#pragma once
#include "pmframework.hpp"

namespace pmframework//physical modeling framework
{
    enum collision_status
    {
        COLLISION_NONE,
        COLLISION_TOUCHING,
        COLLISION_OVERLAPPING
    };

    class collision
    {
    private:
        RigidBody *object1;
        RigidBody *object2;
    public:
        collision();
        collision(RigidBody *firstObject, RigidBody *secondObject);

        void FirstObject(RigidBody *firstObject);
        RigidBody *FirstObject(void);

        void SecondObject(RigidBody *secondObject);
        RigidBody *SecondObject(void);

        collision_status CollisionCheck(void);
        bool CalculateReactions(void);
    };

    inline collision::collision()
    {
        object1 = object2 = NULL;
    }
    
    inline collision::collision(RigidBody *firstObject, RigidBody *secondObject)
    {
        assert(firstObject != NULL);
        assert(secondObject != NULL);

        object1 = firstObject;
        object2 = secondObject;
    }

    inline void collision::FirstObject(RigidBody *firstObject)
    {
        assert(firstObject != NULL);
        object1 = firstObject;
    }

    inline RigidBody *collision::FirstObject(void)
    {
        return object1;
    }

    inline void collision::SecondObject(RigidBody *secondObject)
    {
        assert(SecondObject != NULL);
        object2 = secondObject;
    }

    inline RigidBody *collision::SecondObject(void)
    {
        return object2;
    }
}