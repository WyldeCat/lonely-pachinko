//http://www.defold.com/manuals/physics/?lang=ko


#include<iostream>
#include "phy_engine.hpp"

namespace phyEngine {
	class Object
	{
		float mass;        //����
		float friction;    //���� - ������Ʈ���� �پ ���ǰ��ְ� �̲������� ����� ��. �����׷�(normal force)�� ����� �������� �� ������Ʈ ���̿� ���Ǹ� ���� ��տ� ���� ���� (��Ʈab)
		float restitution; //ź�� - �ݹ߷��� ����. �� ������Ʈ�� restitution �� �� �ִ밪���� ����.
		float drag;        //�׷� - �����ӿ� ���� ���׷�,
		float velocity;    //�ӵ�
		float direction;   //����
		float inertia;     //����

	};
	
	class Dynamic : Object
	{

	};

	class Static : Object
	{

	};

	class Sphere : Object
	{
		float radius;
	};

	class Plane : Object
	{
		
	};
}
/*
	namespace dynamics {
		namespace rigid {
		__declspec (dllexport) bool addForce(); // ��
		{

		}
		__declspec (dllexport) bool addTorque(); // ȸ��
		{

		}
	}

	namespace collision {

		__declspec (dllexport) bool SphereSphereCollision(Sphere s1, Sphere s2)
		{

		}

		__declspec (dllexport) bool SpherePlaneCollision(Sphere s1, Plane s2)
		{

		}
	}
}*/