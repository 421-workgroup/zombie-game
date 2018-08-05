/*
This cpp-file is mainly for initializing static vars in 'Characters.h'.
*/

#include "Characters.h"

USING_NS_CC;

std::vector<GunnerBase*> GunnerBase::gunnerList = {};
std::vector<ZombieBase*> ZombieBase::zombieList = {};

// RoleBase
void RoleBase::updatePosition(float delta) {
	if (velocity.v != 0) {
		loc = getPosition();

		loc.x += velocity.v * cos(velocity.theta) *delta;
		if (loc.x < 0)
			loc.x = 0;
		if (loc.x > Director::getInstance()->getVisibleSize().width)
			loc.x = Director::getInstance()->getVisibleSize().width;

		loc.y += velocity.v * sin(velocity.theta) *delta;
		if (loc.y < 0)
			loc.y = 0;
		if (loc.y > Director::getInstance()->getVisibleSize().height)
			loc.y = Director::getInstance()->getVisibleSize().height;

		setPosition(loc);
	}
}
int RoleBase::getHitBoxRadius() {
	return hitBoxRadius;
}

// GunnerBase
std::vector<GunnerBase*> GunnerBase::getGunnerList() {
	return gunnerList;
}
std::vector<ZombieBase*> GunnerBase::getHitZombieList() {
	std::vector<ZombieBase*> hitZombieList = {};
	auto zombieList = ZombieBase::getZombieList();
	for (auto zombie : zombieList) {
		auto zombiePositon = zombie->getPosition();
		if (ccpDistance(zombiePositon, this->getPosition()) <= (zombie->getHitBoxRadius() + this->getHitBoxRadius()))
			hitZombieList.push_back(zombie);
	}
	return hitZombieList;
}
int GunnerBase::updateBlood(float delta) {
	float drop = 0;
	for (auto zombie : this->getHitZombieList())
		drop += zombie->getATK();
	auto thisBloodBar = dynamic_cast<BloodBar*>(this->getChildByName("bloodBar"));
	thisBloodBar->setBlood(thisBloodBar->getBlood() - drop * delta);
	return drop;
}

// MainRole
void MainRole::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	auto mrole = dynamic_cast<MainRole*>(event->getCurrentTarget());
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		mrole->isPressed[UP] = true;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		mrole->isPressed[DOWN] = true;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		mrole->isPressed[LEFT] = true;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		mrole->isPressed[RIGHT] = true;
		break;
	}
	mrole->velocity = getVelocity(mrole->isPressed, mrole->speed);
}
void MainRole::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	auto mrole = dynamic_cast<MainRole*>(event->getCurrentTarget());
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		mrole->isPressed[UP] = false;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		mrole->isPressed[DOWN] = false;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		mrole->isPressed[LEFT] = false;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		mrole->isPressed[RIGHT] = false;
		break;
	}
	mrole->velocity = getVelocity(mrole->isPressed, mrole->speed);
}
RoleBase::Velocity MainRole::getVelocity(bool* isPressed, float speed) {
	Velocity velocity;
	velocity.v = speed;
	int x = 0;// 1 for RIGHT, -1 for LEFT
	int y = 0;// 1 for UP, -1 for DOWN
	if (isPressed[UP])
		y++;
	if (isPressed[DOWN])
		y--;
	if (isPressed[LEFT])
		x--;
	if (isPressed[RIGHT])
		x++;

	switch (x) {
	case 1:
		switch (y) {
		case 1:
			velocity.theta = M_PI_4;
			break;
		case -1:
			velocity.theta = -M_PI_4;
			break;
		case 0:
			velocity.theta = 0;
			break;
		}
		break;
	case -1:
		switch (y) {
		case 1:
			velocity.theta = 3 * M_PI_4;
			break;
		case -1:
			velocity.theta = -3 * M_PI_4;
			break;
		case 0:
			velocity.theta = M_PI;
			break;
		}
		break;
	case 0:
		switch (y) {
		case 1:
			velocity.theta = M_PI_2;
			break;
		case -1:
			velocity.theta = -M_PI_2;
			break;
		case 0:
			velocity.v = 0;
			velocity.theta = 0;// Not really matter.
			break;
		}
		break;
	}

	return velocity;
}

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
