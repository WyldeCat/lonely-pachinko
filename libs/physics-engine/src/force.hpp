#pragma once

namespace pmframework
{
 
class force
{
private:
    Vector3d forceVector;
    Vector3d forceLocation;

public:
    void Force(Vector3d theForce);
    Vector3d Force(void);

    void ApplicationPoint(Vector3d forceApplicationPoint);
    Vector3d ApplicationPoint(void);
};

inline void force::Force(Vector3d theForce)
{
    forceVector = theForce;
}

inline Vector3d force::Force(void)
{
    return forceVector;
}

inline void force::ApplicationPoint(Vector3d forceApplicationPoint)
{
    forceLocation = forceApplicationPoint;
}

inline Vector3d force::ApplicationPoint(void)
{
    return forceLocation;
}


}