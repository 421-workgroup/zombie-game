#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class KeyBoardScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	// implement the "static create()" method manually
	CREATE_FUNC(KeyBoardScene);

private:
	cocos2d::Label* label;

};

#endif // __TEST_SCENE_H__