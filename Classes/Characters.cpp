/*
This cpp-file is mainly for initializing static vars in 'Characters.h'.
*/

#include "Characters.h"

USING_NS_CC;

std::vector<GunnerBase*> GunnerBase::gunnerList = {};
std::vector<ZombieBase*> ZombieBase::zombieList = {};