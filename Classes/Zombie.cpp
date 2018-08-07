/*
This cpp-file is mainly for initializing static vars in 'Characters.h'.
*/

#include "Characters.h"

USING_NS_CC;
std::vector<ZombieBase*> ZombieBase::zombieList = {};

const float NormalZombie::beatRange = 40.0;

// ZombieBase
std::vector<ZombieBase*> ZombieBase::getZombieList() {
	return zombieList;
}
GunnerBase* ZombieBase::getTargetGunner(std::vector<GunnerBase*> gunnerList) {
	float currentDistance, leastDistance = ccpDistance(gunnerList[0]->getPosition(), this->getPosition());
	GunnerBase* nearestGunner = gunnerList[0];
	for (auto gunner : gunnerList) {
		currentDistance = ccpDistance(gunner->getPosition(), this->getPosition());
		if (currentDistance < leastDistance) {
			leastDistance = currentDistance;
			nearestGunner = gunner;
		}
	}
	return (nearestGunner);
}
float ZombieBase::getATK() {
	return atk;
}

float ZombieBase::calcGunnerAngle(GunnerBase* gunner)
{
	float theta;
	if (gunner->getPositionX() > getPositionX())
		theta = atan((gunner->getPositionY() - getPositionY()) / (gunner->getPositionX() - getPositionX()));

	else if (gunner->getPositionX() < getPositionX())
		theta = M_PI + atan((gunner->getPositionY() - getPositionY()) / (gunner->getPositionX() - getPositionX()));

	else if (gunner->getPositionX() == getPositionX()) {
		if (gunner->getPositionY() == getPositionY()) {
			theta = 0; theta = 0;
		}
		else if (gunner->getPositionY() > getPositionY())
			theta = M_PI_2;
		else if (gunner->getPositionY() < getPositionY())
			theta = -M_PI_2;
	}
	return theta;
}

// NormalZombie
bool NormalZombie::isReachable(GunnerBase* target)
{
	if (target == nullptr)
		return false;
	float orient_angle = calcGunnerAngle(target);
	float curr_orient = curr_pos * M_PI_2;
	float delta = abs(orient_angle - curr_orient);
	// check if the gunner is in its direction
	if (delta <= M_PI_4 || (M_PI * 2 - delta) <= M_PI_4)
	{
		// check if the gunner is near enough
		if (ccpDistance(target->getPosition(), this->getPosition()))
			return true;
	}
	else return false;
}
void NormalZombie::checkAttack()
{
	assert(targetGunner != nullptr);
	if (isReachable(targetGunner))
		scheduleOnce(CC_SCHEDULE_SELECTOR(biteAttack), ATTACK_DELAY);
}

void NormalZombie::biteAttack(float dt)
{
	// check the spatial location of gunner again
	if (isReachable(targetGunner))
	{
		// TODO: create an attack object and push back? or call 
		// gunner's accept() method.
	}
}
