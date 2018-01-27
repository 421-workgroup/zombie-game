#include "KeyBoardScene.h"
#include "ui/cocosGUI.h"

USING_NS_CC;

Scene* KeyBoardScene::createScene() {
	return KeyBoardScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool KeyBoardScene::init() {

	if (!Scene::init()){
		return false;
	}

	auto visibleSize = Director::getInstance()->getWinSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backGround = Sprite::create("backgrounds/White_480_320.png");
	if (backGround == nullptr)
		problemLoading("backgrounds/White_480_320.png");
	else {
		backGround->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height/2));
		this->addChild(backGround, 0);
	}

	//Add a menu item to close the game.
	auto closeItem = MenuItemImage::create("CloseNormal.png", 
										   "CloseSelected.png",
										   [&](Ref* sender) {
											  Director::getInstance()->end();
										   });
	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0){
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else{
		closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
									origin.y + closeItem->getContentSize().height / 2));
	}
	//Menu.
	auto testMenu = Menu::create(closeItem, NULL);
	this->addChild(testMenu);
	testMenu->setPosition(Vec2(0, 0));

	//Add a sprite: gunnerMiami.
	auto gunnerMiami = Sprite::create("characters/Gunner_Sprite.png");
	if (gunnerMiami == nullptr ||
		gunnerMiami->getContentSize().width <= 0 ||
		gunnerMiami->getContentSize().height <= 0) {
		problemLoading("characters/Gunner_Sprite.png");
	}
	else {
		gunnerMiami->setPosition(Vec2(origin.x + visibleSize.width/2,
									  origin.y + visibleSize.height/2));
		this->addChild(gunnerMiami, 1);
	}

	//label to show the key pressed.
	label = Label::createWithSystemFont("Label Test Text.", "Arial", 20);
	label->setColor(Color3B(0, 0, 0));
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
						    origin.y + visibleSize.height*4/5));
	this->addChild(label);
	//label->setString("Label Text Changed.");

	auto keyBoardListener = EventListenerKeyboard::create();
	
	keyBoardListener->onKeyPressed = CC_CALLBACK_2(KeyBoardScene::onKeyPressed, this);
	keyBoardListener->onKeyReleased = CC_CALLBACK_2(KeyBoardScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);

	return true;
}

void KeyBoardScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	log("Key with keycode %d pressed.", keyCode);
	label->setString("Pressed");
}
void KeyBoardScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	log("Key with keycode %d pressed.", keyCode);
	label->setString("Released");
}
