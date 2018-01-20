#ifndef __GAME_UTILS
#define __GAME_UTILS
#endif // !__GAME_UTILS

#include "cocos2d.h"

USING_NS_CC;

class BloodBar : DrawNode
/*	the retangular bar representing remaining blood.
	It contains two retangulars.
*/
{
private:
	static const char blood_length = 100;
	static const char blood_height = 7;
	const Color4F blood_color = Color4F(255, 0, 0, 0);
	const Color4F frame_color = Color4F(255, 255, 255, 0);
	const Vec2 origin = Vec2(0, 0);
	const Vec2 dest = Vec2(100, blood_height);
	// `blood`, representing each one's healthy state, is unique to every person or zombie:
	char blood = 100;
public:
	BloodBar(char blood_init = 100) : blood(blood_init) {};
	virtual bool init()
	{
		auto blood_dest = Vec2(char(blood_length / 100.0*blood), blood_height);
		this->drawSolidRect(origin,dest,blood_color);
		this->drawRect(origin, blood_dest,frame_color);
	}
	// `call back` function to update blood representation
	void updateBlood(char curr_blood)
	{
		blood = curr_blood;
		init();
	}

};