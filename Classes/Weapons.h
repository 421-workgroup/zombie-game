#pragma once

#include "cocos2d.h"
#include "Properties.h"

USING_NS_CC;

class MeleeWeapon : public Sprite {
private:
	float rangeRadius;
	float rangeAngle;
	float atk;
public:
	enum Type {
		Sword,
	}type;
};

class Sword : public MeleeWeapon {
public:

};