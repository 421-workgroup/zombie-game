/*
This cpp-file is mainly for initializing static vars in 'Characters.h'.
*/

#include "Characters.h"

USING_NS_CC;
std::vector<ZombieBase*> ZombieBase::zombieList = {};



// ZombieBase
std::vector<ZombieBase*> ZombieBase::getZombieList() {
	return zombieList;
}
GunnerBase* ZombieBase::getNearestGunner(std::vector<GunnerBase*> gunnerList) {
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
