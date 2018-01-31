#ifndef __GAME_UTILS
#define __GAME_UTILS
#endif // !__GAME_UTILS

#include "cocos2d.h"
#include <string>

USING_NS_CC;

class BloodBar : public Sprite
/*	the retangular bar representing remaining blood.
	It contains two retangulars.
*/
{
private:
	static const char blood_length = 100;	// the length of blood displayed on screen
	static const char blood_height = 7;		// the height of the blood displayed on screen
	static const char max_blood = 100;		// the maximum number of blood points
	const Color4F blood_color = Color4F(1, 0, 0, 1);
	const Color4F frame_color = Color4F(0.87F, 0.94F, 1, 1);
	const Vec2 origin = Vec2(0, 0);
	const Vec2 dest = Vec2(100, blood_height);
	// `blood`, representing each one's healthy state, is unique to every person or zombie:
	char blood = 100;
	
public:
	BloodBar(char blood_init = 100) : blood(blood_init) { };
	static BloodBar* create()
	{
		BloodBar* ret = new (std::nothrow) BloodBar();
		if (ret && ret->init())
			ret->autorelease();
		else
			CC_SAFE_DELETE(ret);
		return ret;
	}
	bool init()
	{
		DrawNode* dnode = DrawNode::create();
		dnode->setPosition(Vec2::ZERO);
		this->addChild(dnode);
		auto blood_dest = Vec2(char(blood_length / float(max_blood)*blood), blood_height);
		dnode->drawSolidRect(origin,dest,blood_color);
		dnode->drawRect(origin, blood_dest,frame_color);
		return true;
	}
	// `call back` function to update blood representation
	void updateBlood(char curr_blood)
	{
		blood = curr_blood;
		// init(); // it's not needed.
	}

};

class Gunner : public Sprite
{
	/* TODO later:
		a spritesheet(http://cocos2d-x.org/docs/cocos2d-x/en/sprites/spritesheets.html) should be made later.
	*/
private:
	const std::string gunner_image_path = "characters/brownfellow_right.PNG";
public:
	enum Type
	{
		BROWN_GUY,
		BLUE_GUY, // unavailable now
		BLACK_GUY, // unavailable now
	};
	Gunner()
	{
		/* TODO later:
			we can create a gunner with different appearances
			like blue ones, and black ones.
		*/
		initWithFile(gunner_image_path);

		

	}
};

class Zombie : public Sprite {
private:
	const std::string zombie_image_path = "characters/zombie.PNG";
public:
	enum Type {
		NORMAL_ZOMBIE,
	};

	Zombie() {
		initWithFile(zombie_image_path);
	}

};