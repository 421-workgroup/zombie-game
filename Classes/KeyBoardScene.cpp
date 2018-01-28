#include "KeyboardScene.h"

USING_NS_CC;

Scene* KeyboardScene::createScene()
{
	auto scene = Scene::create();

	KeyboardScene* layer = KeyboardScene::create();
	scene->addChild(layer);
	return scene;
}

bool KeyboardScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	interval = 50;// 20 pixel/s
	moveControlKeys = { EventKeyboard::KeyCode::KEY_UP_ARROW,
		EventKeyboard::KeyCode::KEY_DOWN_ARROW,
		EventKeyboard::KeyCode::KEY_LEFT_ARROW,
		EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
	};

	gunnerMiami = Sprite::create("./characters/Gunner_Sprite.png");
	gunnerMiami->setPosition(this->getBoundingBox().getMidX(), this->getBoundingBox().getMidY());
	addChild(gunnerMiami);

	label = cocos2d::Label::createWithSystemFont("Press the CTRL Key", "Arial", 32);
	label->setPosition(this->getBoundingBox().getMidX(), this->getBoundingBox().getMidY());
	addChild(label);

	auto eventListener = EventListenerKeyboard::create();
	//Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		// If a key already exists, do nothing as it will already have a time stamp
		// Otherwise, set's the timestamp to now
		if (keys.find(keyCode) == keys.end()) {
			keys[keyCode] = std::chrono::high_resolution_clock::now();
		}
	};
	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		// remove the key.  std::map.erase() doesn't care if the key doesnt exist
		keys.erase(keyCode);
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	// Let cocos know we have an update function to be called.
	// No worries, ill cover this in more detail later on
	this->scheduleUpdate();
	return true;
}

bool KeyboardScene::isKeyPressed(EventKeyboard::KeyCode code) {
	// Check if the key is currently pressed by seeing it it's in the std::map keys
	// In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
	if (keys.find(code) != keys.end())
		return true;
	return false;
}

bool KeyboardScene::areKeysPressed(std::vector<EventKeyboard::KeyCode> keys) {
	for (auto key : keys) {
		if (isKeyPressed(key))
			return true;
	}
	return false;
}

int KeyboardScene::keyPressedDuration(EventKeyboard::KeyCode code) {
	if (!isKeyPressed(code))
		return 0;  // Not pressed, so no duration obviously

				   // Return the amount of time that has elapsed between now and when the user
				   // first started holding down the key in milliseconds
				   // Obviously the start time is the value we hold in our std::map keys
	return std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::high_resolution_clock::now() - keys[code]).count();
}

void KeyboardScene::update(float delta) {
	// Register an update function that checks to see if the CTRL key is pressed
	// and if it is displays how long, otherwise tell the user to press it
	Node::update(delta);
	if (!areKeysPressed(moveControlKeys)) {//No keys control moving is pressed.
		label->setString("Press Direction Keys.");
		return;
	}
	label->setString("");

	if ((keyPressedDuration(EventKeyboard::KeyCode::KEY_UP_ARROW) != 0) &
		(keyPressedDuration(EventKeyboard::KeyCode::KEY_UP_ARROW) % interval == 0)) {
		gunnerMiami->runAction(MoveBy::create(0, Vec2(0, 1)));
	}
	if ((keyPressedDuration(EventKeyboard::KeyCode::KEY_DOWN_ARROW) != 0) &
		(keyPressedDuration(EventKeyboard::KeyCode::KEY_DOWN_ARROW) % interval == 0)) {
		gunnerMiami->runAction(MoveBy::create(0, Vec2(0, -1)));
	}
	if ((keyPressedDuration(EventKeyboard::KeyCode::KEY_LEFT_ARROW) != 0) &
		(keyPressedDuration(EventKeyboard::KeyCode::KEY_LEFT_ARROW) % interval == 0)) {
		gunnerMiami->runAction(MoveBy::create(0, Vec2(-1, 0)));
	}
	if ((keyPressedDuration(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) != 0) &
		(keyPressedDuration(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) % interval == 0)) {
		gunnerMiami->runAction(MoveBy::create(0, Vec2(1, 0)));
	}
	return;

}
// Because cocos2d-x requres createScene to be static, we need to make other non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode,
	std::chrono::high_resolution_clock::time_point> KeyboardScene::keys;