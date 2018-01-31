#pragma once

#include "cocos2d.h"
#include "utils.h"

USING_NS_CC;

// Both enemies and gunners are inherited from this class.
class RoleBase : public Sprite
{
public:
	float speed;//The number of pixels the role moved between two frame.
	Vec2 loc;
	void update(float delta) override{
		if (velocity.v != 0) {
			loc = getPosition();
			loc.x += velocity.v * cos(velocity.theta);
			loc.y += velocity.v * sin(velocity.theta);
			setPosition(loc);
		}
	}

protected:
	struct Velocity {
		float v = 0;
		float theta = 0;//Counterclockwise as positive, from x+ direction. rad.
					//v_x = v * cos(theta); v_y = v * sin(theta)

	}velocity;//Here velocity represents the real movement of the role. 
			  //Nothing to do with the speed attribute of the role.
};

// Base class for Teammate and MainRole
class GunnerBase : public RoleBase
{
public:

	GunnerBase()
	{
		// A role is constituted by a BloodBar object and a Gunner object. (Those are defined in utils.h)
		auto gunner = new Gunner();
		gunner->autorelease();
		gunner->setPosition(Vec2::ZERO);
		addChild(gunner);
		auto bloodbar = BloodBar::create();
		gunner->addChild(bloodbar);
		bloodbar->setPosition(Vec2(0,gunner->getContentSize().height ));
	}

private:
	
};

class ZombieBase : public RoleBase {
public:
	ZombieBase() {
		// A zombie is constituted by a BloodBar object and a Zombie object. (Those are defined in utils.h)
		auto zombie = new Zombie();
		zombie->autorelease();
		zombie->setPosition(Vec2::ZERO);
		addChild(zombie);
		auto bloodbar = BloodBar::create();
		zombie->addChild(bloodbar);
		bloodbar->setPosition(Vec2(0,zombie->getContentSize().height));
	}
};

class NormalZombie : public ZombieBase{
public:
	NormalZombie() {//NormalZombies simply move towards a player.

	}
private:
	void moveTowards() {
	}
};

class MainRole : public GunnerBase{
public:
	MainRole(){
		/* add a keyboard listener.
		This listener is for changing the role's direction and position.
		*/
		auto eventListener = EventListenerKeyboard::create();
		eventListener->onKeyPressed = onKeyPressed;
		eventListener->onKeyReleased = onKeyReleased;
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
	}

	

private:
	bool isPressed[4] = {false, false, false, false};
	enum {UP, DOWN, LEFT, RIGHT};

	//What onKeyPressed/onKeyReleased does is change CurrentTarget->velocity when keyboard statu changed.
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

	static void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event){
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

		switch (x){
		case 1:
			switch (y){
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