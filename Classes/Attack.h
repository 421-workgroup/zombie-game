#pragma once
#include "Characters.h"

class AttackBase
{
public:
	AttackBase(unsigned int hurt):hurt(hurt) {}
	unsigned int hurt; // amount of blood dropped
	// trigerred when attacks hit enemies
	virtual void attackEnemy(ZombieBase* zombie) = 0;
	// trigerred when attacks hit roles
	virtual void attackRole(RoleBase* role) = 0;
	// trigerred when attacks hit other objects
	virtual void attackWall() = 0;
	virtual void attackBarrel() = 0;

};

// represent bite attack generated from NormalZombie
class ZombieBiteAttack :AttackBase
{
public:
	// angle the attack is pointed at, used to calculate displacement after hit 
	float attackAngle;
	ZombieBiteAttack(float attackAngle, unsigned int hurt = 18):AttackBase(hurt),attackAngle(attackAngle) {}
	// normal zombies will not hurt themselves 
	void attackEnemy(ZombieBase* zombie) {}
	void attackRole(RoleBase* role) override;
	// a bite attack cannot destroy walls or barrels
	void attackWall() {}
	void attackBarrel() {}
};