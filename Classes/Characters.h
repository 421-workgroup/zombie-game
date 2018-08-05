#pragma once

#include "cocos2d.h"
#include "utils.h"
#include "Properties.h"

USING_NS_CC;

// Both zombies and gunners are inherited from this class.
class RoleBase : public Sprite
{
public:

protected:
	// An attribute of one kind of role. Might change during the game.
	// The number of pixels the role moved in a second.
	float speed;

	// A circle hitbox. Might change during the game.
	int hitBoxRadius;

	//Here velocity represents the real movement of the role. 
	//Nothing to do with the speed attribute of the role.
	struct Velocity {
		float v = 0;
		float theta = 0;
		//Counterclockwise as positive, from x+ direction. rad.
		//v_x = v * cos(theta); v_y = v * sin(theta)
	}velocity;

	void updatePosition(float delta) {
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

private:
	Vec2 loc;
};

class ZombieBase;

// Base class for Teammate and MainRole
class GunnerBase : public RoleBase
{
public:
	// A role is constituted by a BloodBar object and a Gunner object. (Those are defined in utils.h)
	GunnerBase(){
		gunnerList.push_back(this);
	}

	static std::vector<GunnerBase*> getGunnerList() {
		return gunnerList;
	}

	std::vector<ZombieBase*> getHitZombieList();
	std::vector<GunnerBase*> getHitGunnerList();

	int dropBlood() {
		// Detect hitBox collapse.
	}

private:
	static std::vector<GunnerBase*> gunnerList;
	std::vector<ZombieBase*> hitZombieList;
	std::vector<GunnerBase*> hitGunnerList;
};

class MainRole : public GunnerBase {
public:
	MainRole(float speed_init = mainRoleProperties.speed, int hitBoxRadius_init = mainRoleProperties.hitBoxRadius,
		     int max_blood_init = mainRoleProperties.max_blood) {
		auto gunner = new Gunner();
		gunner->autorelease();
		gunner->setPosition(Vec2::ZERO);
		addChild(gunner, 0, "gunner");
		auto bloodbar = BloodBar::create(max_blood_init);
		addChild(bloodbar, 0, "bloodbar");
		bloodbar->setPosition(Vec2(0, this->getChildByName("gunner")->getContentSize().height));
		// Add a keyboard listener.
		// This listener is for changing the role's direction and position.
		auto eventListener = EventListenerKeyboard::create();
		eventListener->onKeyPressed = onKeyPressed;
		eventListener->onKeyReleased = onKeyReleased;
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);

		speed = speed_init;
		hitBoxRadius = hitBoxRadius_init;
	}

	void update(float delta) override {
		updatePosition(delta);

		BloodBar* bloodbar_ = dynamic_cast<BloodBar*>(getChildByName("bloodbar"));
		//bloodbar_->updateBlood(50);
		bloodbar_->drawBlood();
	}

private:
	bool isPressed[4] = { false, false, false, false };
	enum { UP, DOWN, LEFT, RIGHT };

	// Change CurrentTarget->velocity when keyboard statu changed.
	static void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
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
	static void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
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

	static Velocity getVelocity(bool* isPressed, float speed) {
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
};

//Base class for all kinds of zombies
class ZombieBase : public RoleBase {
public:
	ZombieBase() {
		// A zombie is constituted by a BloodBar object and a Zombie object. (Those are defined in utils.h)
		zombieList.push_back(this);
	}

	static std::vector<ZombieBase*> getZombieList();

protected:
	float atk;
	GunnerBase* getNearestGunner(std::vector<GunnerBase*> gunnerList) {
		float currentDistance, leastDistance = ccpDistance(gunnerList[0]->getPosition(), this->getPosition());
		GunnerBase* nearestGunner = gunnerList[0];
		for (auto gunner : gunnerList) {
			currentDistance = ccpDistance(gunner->getPosition(), getPosition());
			if (currentDistance < leastDistance) {
				leastDistance = currentDistance;
				nearestGunner = gunner;
			}
		}
		return (nearestGunner);
	}

private:
	static std::vector<ZombieBase*> zombieList;
};

std::vector<ZombieBase*> ZombieBase::getZombieList() {
	return zombieList;
}


class NormalZombie : public ZombieBase {
public:

	// NormalZombies simply move towards the nearest gunner.
	NormalZombie(float speed_init = normalZombieProperties.speed, int hitBoxRadius_init = normalZombieProperties.hitBoxRadius,
		float atk_init = normalZombieProperties.atk, int max_blood_init = normalZombieProperties.max_blood) {
		auto zombie = new Zombie();
		zombie->autorelease();
		zombie->setPosition(Vec2::ZERO);
		addChild(zombie, 0, "zombie");
		auto bloodbar = BloodBar::create(max_blood_init);
		addChild(bloodbar, 0, "bloodbar");
		bloodbar->setPosition(Vec2(0, this->getChildByName("zombie")->getContentSize().height));

		atk = atk_init;
		speed = speed_init;
		hitBoxRadius = hitBoxRadius_init;
	}

	void update(float delta) override {
		// Move towards the nearest gunner. 
		auto nearestGunner = getNearestGunner(GunnerBase::getGunnerList());
		velocity.v = speed;

		if (nearestGunner->getPositionX() > getPositionX())
			velocity.theta = atan((nearestGunner->getPositionY() - getPositionY()) / (nearestGunner->getPositionX() - getPositionX()));

		else if (nearestGunner->getPositionX() < getPositionX())
			velocity.theta = M_PI + atan((nearestGunner->getPositionY() - getPositionY()) / (nearestGunner->getPositionX() - getPositionX()));

		else if (nearestGunner->getPositionX() == getPositionX()) {
			if (nearestGunner->getPositionY() == getPositionY()) {
				velocity.v = 0; velocity.theta = 0;
			}
			else if (nearestGunner->getPositionY() > getPositionY())
				velocity.theta = M_PI_2;
			else if (nearestGunner->getPositionY() < getPositionY())
				velocity.theta = -M_PI_2;
		}
		updatePosition(delta);

		// TODO: A GunnerBase touched by a NormalZombie will get hurt.

	}

private:

};
