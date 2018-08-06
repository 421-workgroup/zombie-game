#pragma once

#include "cocos2d.h"
#include "utils.h"
#include "Properties.h"

USING_NS_CC;

// Both zombies and gunners are inherited from this class.
class RoleBase : public Sprite
{
public:
	int getHitBoxRadius();

protected:
	float speed;
	int hitBoxRadius;
	int max_blood;

	//Here velocity represents the real movement of the role. 
	//Nothing to do with the speed attribute of the role.
	struct Velocity {
		float v = 0;
		float theta = 0;
		//Counterclockwise as positive, from x+ direction. rad.
		//v_x = v * cos(theta); v_y = v * sin(theta)
	}velocity;

	void updatePosition(float delta);

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

	static std::vector<GunnerBase*> getGunnerList();

	std::vector<ZombieBase*> getHitZombieList();
	//std::vector<GunnerBase*> getHitGunnerList();

	int updateBlood(float delta);

private:
	static std::vector<GunnerBase*> gunnerList;
	std::vector<ZombieBase*> hitZombieList;
	std::vector<GunnerBase*> hitGunnerList;
};

class MainRole : public GunnerBase {
public:
	MainRole() {
		speed = mainRoleProperties.speed;
		hitBoxRadius = mainRoleProperties.hitBoxRadius;
		max_blood = mainRoleProperties.max_blood;

		auto gunner = new Gunner();
		gunner->autorelease();
		gunner->setPosition(Vec2::ZERO);
		addChild(gunner, 0, "gunner");
		auto bloodbar = BloodBar::create(max_blood);
		addChild(bloodbar, 0, "bloodBar");
		bloodbar->setPosition(Vec2(0, this->getChildByName("gunner")->getContentSize().height));
		bloodbar->scheduleUpdate();
		// Add a keyboard listener.
		// This listener is for changing the role's direction and position.
		auto eventListener = EventListenerKeyboard::create();
		eventListener->onKeyPressed = onKeyPressed;
		eventListener->onKeyReleased = onKeyReleased;
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);

	}

	void update(float delta) override {
		updatePosition(delta);
		updateBlood(delta);
	}

private:
	bool isPressed[4] = { false, false, false, false };
	enum { UP, DOWN, LEFT, RIGHT };

	// Change CurrentTarget->velocity when keyboard statu changed.
	static void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	static void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	static Velocity getVelocity(bool* isPressed, float speed);
};

//Base class for all kinds of zombies
class ZombieBase : public RoleBase {
public:
	ZombieBase() {
		// A zombie is constituted by a BloodBar object and a Zombie object. (Those are defined in utils.h)
		zombieList.push_back(this);
	}

	static std::vector<ZombieBase*> getZombieList();

	float getATK();

protected:
	float atk;
	GunnerBase* getNearestGunner(std::vector<GunnerBase*> gunnerList);

private:
	static std::vector<ZombieBase*> zombieList;
};

class NormalZombie : public ZombieBase {
public:

	// NormalZombies simply move towards the nearest gunner.
	NormalZombie() {
		atk = normalZombieProperties.atk;
		speed = normalZombieProperties.speed;
		hitBoxRadius = normalZombieProperties.hitBoxRadius;
		max_blood = normalZombieProperties.max_blood;

		auto zombie = new Zombie();
		zombie->autorelease();
		zombie->setPosition(Vec2::ZERO);
		addChild(zombie, 0, "zombie");
		auto bloodbar = BloodBar::create(max_blood);
		addChild(bloodbar, 0, "bloodBar");
		bloodbar->setPosition(Vec2(0, this->getChildByName("zombie")->getContentSize().height));

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
