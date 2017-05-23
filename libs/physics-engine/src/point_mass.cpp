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
    //���� world ��ȯ ��� ����..
    //�� ��ü�� world����� ���� world��ķ� ����
    //������ ��ȯ�� ����Ͽ� ��ü�� ������
    //world ��ȯ ��� �����ä�
}

}