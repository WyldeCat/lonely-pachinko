#include "pmframework.hpp"

namespace pmframework
{

bool PointMass::Update(scalar changeInTime)
{
    assert(mass != 0);
    linearAcceleration = sumForces / mass;
    linearVelocity += linearAcceleration * changeInTime;
    centerOfMass += linearVelocity * changeInTime;

    //glMatrixMode...
    //loadIdentity...
    //glPush..
    //glTranslate(centerOfMass.X(), centerOfMass.Y(), centerOfMass.Z());
    //gl

    return true;
}

bool PointMass::Render(void)
{
    //현재 world 변환 행렬 저장..
    //이 객체의 world행렬을 현재 world행렬로 지정
    //지정한 변환을 사용하여 물체를 렌더링
    //world 변환 행렬 복구ㅓㅕ
}

}