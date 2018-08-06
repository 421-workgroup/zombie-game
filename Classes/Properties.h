#pragma once

#include "cocos2d.h"

USING_NS_CC;

class RoleBaseProp {
public:
	float speed;
	int hitBoxRadius;
	float max_blood;
};

class GunnerBaseProp : public RoleBaseProp {
public:

};

class mainRoleProp : public GunnerBaseProp {
public:
	mainRoleProp() {
		speed = 120;
		hitBoxRadius = 20;
		max_blood = 100;
	}
};
extern mainRoleProp mainRoleProperties;



class ZombieBaseProp : public RoleBaseProp {
public:
	float atk;
};

class normalZombieProp : public ZombieBaseProp {
public:
	normalZombieProp() {
		speed = 30;
		hitBoxRadius = 30;
		atk = 10;
		max_blood = 100;
	}
};
extern normalZombieProp normalZombieProperties;

