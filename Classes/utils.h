#pragma once

#include "cocos2d.h"
#include <string>

USING_NS_CC;

class BloodBar : public Sprite
/*	the retangular bar representing remaining blood.
*/
{
private:
	static const char blood_length = 30;	// the length of blood displayed on screen
	static const char blood_height =5;		// the height of the blood displayed on screen
	const Color4F back_color = Color4F(1, 1, 1, 1);
	const Color4F blood_color = Color4F(1, 0, 0, 1);
	const Color4F frame_color = Color4F(0.87F, 0.94F, 1, 1);
	const Vec2 origin = Vec2(0, 0);
	const Vec2 dest = Vec2(blood_length, blood_height);
	// `blood`, representing each one's healthy state, is unique to every person or zombie:
	int max_blood;
	char blood;
	DrawNode* dnode;
	
public:

	BloodBar(int max_blood_init) : max_blood(max_blood_init), blood(max_blood_init) {};

	static BloodBar* create(int max_blood_init){
		BloodBar* ret = new (std::nothrow) BloodBar(max_blood_init);
		if (ret && ret->init())
			ret->autorelease();
		else
			CC_SAFE_DELETE(ret);
		return ret;
	}

	bool init(){
		drawBlood();
		return true;
	}

	//void update(float delta) override {
	//	auto blood_dest = Vec2(char(blood_length / float(max_blood)*blood), blood_height);
	//	updateBlood(blood - delta * 1);
	//	dnode->drawSolidRect(origin, dest, blood_color);
	//	dnode->drawRect(origin, blood_dest, frame_color);
	//}

	// 'call back' function to update blood representation
	void updateBlood(char curr_blood){
		blood = curr_blood;
	}

	void drawBlood() {
		// Remove old dnode first.
		if (auto old_dnode = this->getChildByName("dnode"))
			this->removeChild(old_dnode, TRUE);
		dnode = DrawNode::create();
		dnode->setPosition(Vec2::ZERO);
		this->addChild(dnode, 0 ,"dnode");

		auto blood_dest = Vec2(char(blood_length / float(max_blood)*blood), blood_height);
		dnode->drawSolidRect(origin, dest, back_color);
		dnode->drawSolidRect(origin, blood_dest, blood_color);
		dnode->drawRect(origin, dest, frame_color);
	}	
};

class Gunner : public Sprite
{
	/* TODO later:
		a spritesheet(http://cocos2d-x.org/docs/cocos2d-x/en/sprites/spritesheets.html) should be made later.
	*/
private:
	std::string gunner_image_path;
public:
	enum Type
	{
		BROWN_GUY,
		MIAMI_GUY,
	}type;
	
	Gunner(enum Type type_init = BROWN_GUY) : type(type_init)
	{
		/* TODO later:
			we can create a gunner with different appearances
			like blue ones, and black ones.
		*/
		switch (type)
		{
		case Gunner::BROWN_GUY:
			gunner_image_path = "characters/brownfellow_right.PNG";
			break;
		case Gunner::MIAMI_GUY:
			gunner_image_path = "characters/miami.PNG";
			break;
		default:
			break;
		}
		initWithFile(gunner_image_path);
	}

	std::string get_image_path() {
		return gunner_image_path;
	}
};

class Zombie : public Sprite {
private:
	std::string zombie_image_path;
public:
	enum Type {
		NORMAL_ZOMBIE,
	}type;

	Zombie(enum Type type_init = NORMAL_ZOMBIE) : type(type_init)
	{
		switch (type)
		{
		case Zombie::NORMAL_ZOMBIE:
			zombie_image_path = "characters/zombie.PNG";
			break;
		default:
			break;
		}
		initWithFile(zombie_image_path);
	}

	std::string get_image_path() {
		return zombie_image_path;
	}
};