#ifndef __CHARACTERS__
#define __CHARACTERS__
#endif // !__CHARACTERS__

#include "cocos2d.h"
#include "utils.h"

USING_NS_CC;

// Both enemies and gunners are inherited from this class.
class RoleBase : public Sprite
{
public:
	// MovingState applies to one dimension.
	enum MovingState
	{
		BACK,
		FORWARD,
		STILL,
		STILL2 // when two keys with opposite directions are pressed
	};

	void update(float delta) override
	{
		// first deal with the movemenet in current frame
		if (x_state == MovingState::FORWARD)
			setPosition(Vec2(getPosition().x + 1, getPosition().y));
		else if (x_state == MovingState::BACK)
			setPosition(Vec2(getPosition().x - 1, getPosition().y));
		if (y_state == MovingState::FORWARD)
			setPosition(Vec2(getPosition().x, getPosition().y + 1));
		else if (y_state == MovingState::BACK)
			setPosition(Vec2(getPosition().x, getPosition().y - 1));
	}

protected:
	MovingState x_state = MovingState::STILL;
	MovingState y_state = MovingState::STILL;
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
		bloodbar->setPosition(Vec2(0,gunner->getContentSize().height ));
		addChild(bloodbar);
		
	}

private:
	
};

class MainRole : public GunnerBase
{
public:
	MainRole()
	{
		/* add a keyboard listener.
		This listener is for changing the role's direction and position.
		*/
		auto eventListener = EventListenerKeyboard::create();
		eventListener->onKeyPressed = onKeyPressed;
		eventListener->onKeyReleased = onKeyReleased;
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
	}

	

private:
	static void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {

		// Vec2 loc = event->getCurrentTarget()->getPosition();
		auto mrole = dynamic_cast<MainRole*>(event->getCurrentTarget());
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			if (mrole->x_state == RoleBase::MovingState::STILL)
				mrole->x_state = RoleBase::MovingState::BACK;
			else if (mrole->x_state == RoleBase::MovingState::FORWARD)
				mrole->x_state = RoleBase::MovingState::STILL2;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			if (mrole->x_state == RoleBase::MovingState::STILL)
				mrole->x_state = RoleBase::MovingState::FORWARD;
			else if (mrole->x_state == RoleBase::MovingState::BACK)
				mrole->x_state = RoleBase::MovingState::STILL2;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:
			if (mrole->y_state == RoleBase::MovingState::STILL)
				mrole->y_state = RoleBase::MovingState::FORWARD;
			else if (mrole->y_state == RoleBase::MovingState::BACK)
				mrole->y_state = RoleBase::MovingState::STILL2;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			if (mrole->y_state == RoleBase::MovingState::STILL)
				mrole->y_state = RoleBase::MovingState::BACK;
			else if (mrole->y_state == RoleBase::MovingState::FORWARD)
				mrole->y_state = RoleBase::MovingState::STILL2;
			break;
		}
	}

	static void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
	{
		auto mrole = dynamic_cast<MainRole*>(event->getCurrentTarget());
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			if (mrole->x_state == RoleBase::MovingState::STILL2)
				mrole->x_state = RoleBase::MovingState::FORWARD;
			else if (mrole->x_state == RoleBase::MovingState::BACK)
				mrole->x_state = RoleBase::MovingState::STILL;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			if (mrole->x_state == RoleBase::MovingState::STILL2)
				mrole->x_state = RoleBase::MovingState::BACK;
			else if (mrole->x_state == RoleBase::MovingState::FORWARD)
				mrole->x_state = RoleBase::MovingState::STILL;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:
			if (mrole->y_state == RoleBase::MovingState::STILL2)
				mrole->y_state = RoleBase::MovingState::BACK;
			else if (mrole->y_state == RoleBase::MovingState::FORWARD)
				mrole->y_state = RoleBase::MovingState::STILL;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			if (mrole->y_state == RoleBase::MovingState::STILL2)
				mrole->y_state = RoleBase::MovingState::FORWARD;
			else if (mrole->y_state == RoleBase::MovingState::BACK)
				mrole->y_state = RoleBase::MovingState::STILL;
			break;
		}
	}
};