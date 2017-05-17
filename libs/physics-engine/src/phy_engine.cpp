//http://www.defold.com/manuals/physics/?lang=ko


#include<iostream>
#include "phy_engine.hpp"

namespace phyEngine {
	class Object
	{
		float mass;        //질량
		float friction;    //마찰 - 오브젝트끼리 붙어서 현실감있게 미끄러지게 만드는 것. 수직항력(normal force)에 비례함 마찰력이 두 오브젝트 사이에 계산되면 기하 평균에 의해 계산됨 (루트ab)
		float restitution; //탄성 - 반발력을 설정. 두 오브젝트의 restitution 값 중 최대값으로 결합.
		float drag;        //항력 - 움직임에 대한 저항력,
		float velocity;    //속도
		float direction;   //방향
		float inertia;     //관성

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
		__declspec (dllexport) bool addForce(); // 힘
		{

		}
		__declspec (dllexport) bool addTorque(); // 회전
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