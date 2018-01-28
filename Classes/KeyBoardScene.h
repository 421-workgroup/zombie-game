#pragma once

#include "cocos2d.h"
#include <map>

class KeyboardScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();
	virtual bool init();

	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
	bool areKeysPressed(std::vector<cocos2d::EventKeyboard::KeyCode>);
	int keyPressedDuration(cocos2d::EventKeyboard::KeyCode);

	CREATE_FUNC(KeyboardScene);

private:
	static std::map<cocos2d::EventKeyboard::KeyCode,
				    std::chrono::high_resolution_clock::time_point> keys;
	cocos2d::Label * label;
	cocos2d::Sprite *gunnerMiami;
	int interval;//Interval between the sprite move one pixel.As reciprocal of the velocity.
	std::vector<cocos2d::EventKeyboard::KeyCode> moveControlKeys;

public:
	virtual void update(float delta) override;
};