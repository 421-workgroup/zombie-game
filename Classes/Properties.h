#pragma once

#include "cocos2d.h"

USING_NS_CC;

class PropertiesBundle{
public:
	float speed;
	int hitBoxRadius;
	float atk; // drop atk per second
	float max_blood;
};

class normalZombieProp : public PropertiesBundle {
public:
	normalZombieProp() {
		speed = 30;
		hitBoxRadius = 30;
		atk = 10;
		max_blood = 100;
	}
};
extern normalZombieProp normalZombieProperties;

class mainRoleProp : public PropertiesBundle {
public:
	mainRoleProp() {
		speed = 120;
		hitBoxRadius = 20;
		max_blood = 100;
	}
};
extern mainRoleProp mainRoleProperties;