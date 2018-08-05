#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Characters.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    // super init first
    if ( !Scene::init() )
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add a menu item which is clicked to quit the program
    auto closeItem = MenuItemImage::create("CloseNormal.png",
                                           "CloseSelected.png",
											[&](Ref* sender) {
												Director::getInstance()->end();
											});

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


	// add playerGunner
	auto playGunner = new MainRole();
	if (playGunner == nullptr){
		problemLoading("PNG file for ");
	}
	else{
		playGunner->autorelease();
		playGunner->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(playGunner, 2);
		playGunner->scheduleUpdate();
	}

	// add zombie1
	auto zombie1 = new NormalZombie();
	if (zombie1 == nullptr) {
		problemLoading("zombie.png");
	}
	else {
		zombie1->autorelease();
		zombie1->setPosition(Vec2(visibleSize.width / 4 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(zombie1, 1);
		zombie1->scheduleUpdate();
	}
    return true;
}
