#ifndef __CHARACTERS__
#define __CHARACTERS__
#endif // !__CHARACTERS__

#include "cocos2d.h"
#include "utils.h"

USING_NS_CC;

// Base class for Teammate and MainRole
class RoleBase : public Sprite
{
public:
	RoleBase()
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

class MainRole : public RoleBase
{
public:
	MainRole()
	{
		/* add a keyboard listener.
		This listener is for changing the role's direction and position.
		*/
		auto eventListener = EventListenerKeyboard::create();
		eventListener->onKeyPressed = onKeyPressed;
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
	}

private:
	static void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {

		Vec2 loc = event->getCurrentTarget()->getPosition();
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			event->getCurrentTarget()->setPosition(--loc.x, loc.y);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			event->getCurrentTarget()->setPosition(++loc.x, loc.y);
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:
			event->getCurrentTarget()->setPosition(loc.x, ++loc.y);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			event->getCurrentTarget()->setPosition(loc.x, --loc.y);
			break;
		}
	}
};