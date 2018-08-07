#pragma once

#include "cocos2d.h"
#include "utils.h"
#include "Properties.h"
#include "Attack.h"

USING_NS_CC;

// Both zombies and gunners are inherited from this class.
class RoleBase : public Sprite
{
public:
	enum Direction { RIGHT, UP, LEFT, DOWN };
	int getHitBoxRadius();

protected:
	float speed;
	int hitBoxRadius;
	int max_blood;

	// Orientation of role, needed when drawing
	Direction curr_pos;

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
	/*
	// it listens to network messages from server
	void update(float delta) override
	*/

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

	void freeze() { _freeze = true; }
	void unfreeze() { _freeze = false; }

	void accept(AttackBase* attack) { attack->attackRole(this); }

private:
	bool isPressed[4] = { false, false, false, false };
	bool _freeze = false;
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

	// represent whether the zombie is turning left or right
	// used when generating animation of turning around.
	enum SpinningStatus
	{
		Still,
		ClockWise,
		AntiClockWise
	};

	static std::vector<ZombieBase*> getZombieList();

	float getATK();

	void accept(AttackBase* attack) { attack->attackEnemy(this); }

protected:
	float atk;
	// the gunner this zombie is chasing at
	GunnerBase* targetGunner = nullptr;
	GunnerBase* getTargetGunner(std::vector<GunnerBase*> gunnerList);
	// Check location of targetGunner and make attacking actions.
	// It won't take charge of zombie's movement.
	// Called on every frame.
	// Must be overrided by different zombie descendants.
	virtual void checkAttack() = 0;
	// Calculate the angle position of a specific gunner
	float calcGunnerAngle(GunnerBase* gunner);

private:
	static std::vector<ZombieBase*> zombieList;
	// when changing orientation, mark the final orientation.
	Direction endPos;
	
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
		auto nearestGunner = getTargetGunner(GunnerBase::getGunnerList());
		velocity.v = speed;

		velocity.theta = calcGunnerAngle(nearestGunner);
		updatePosition(delta);

		// TODO: A GunnerBase touched by a NormalZombie will get hurt.

	}
	void checkAttack() override;
	// scheduled once with some interval after `checkAttack()` finds gunners to attack.
	// corresponding to white zombie's bite actions.
	void biteAttack(float dt);

private:
	// normal zombie(white)
	static const float beatRange;
	// Interval between bite starting time and hit time.
	// Gunners can escape before hit time.
	static const float ATTACK_DELAY;
	bool isReachable(GunnerBase* target);

};
