#include "HelloWorldScene.h"
#include "Scores.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
										   "CloseNormal.png",
										   "CloseSelected.png",
										   CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
								origin.y + closeItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	labelGameTitle = ColorfulLabel::create("CatchMe", "Fonts/NextGames.ttf", 72);

	// position the label on the center of the screen
	labelGameTitle->setPosition(Point(origin.x + visibleSize.width/2,
							origin.y + visibleSize.height - labelGameTitle->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(labelGameTitle, 1);

#if 0
	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
#endif

	schedule( schedule_selector(HelloWorld::update) );
	animateGameTitle();
	setEventHandlers();
	showHighScores();

	return true;
}

void HelloWorld::animateGameTitle()
{
	MoveTo* moveTo = MoveTo::create(1.5f, Point( rand() % 1024, rand() % 768 ) );
	CallFunc* callFunc = CallFunc::create( this, callfunc_selector(HelloWorld::animateGameTitle) );
	Sequence* sequence = Sequence::create(moveTo, callFunc, nullptr);

	labelGameTitle->runAction(sequence);
	//label->runAction(parallelAction);
}

void HelloWorld::setEventHandlers()
{
	labelGameTitle->setEventHandlers();
}

void HelloWorld::update(float df)
{
	labelGameTitle->nextColor();
}

void HelloWorld::showHighScores()
{
	Scores* scores = Scores::create("", "Fonts/Gameboy.ttf", 24);
	float screenWidth = Director::sharedDirector()->getWinSize().width;
	scores->setPosition( screenWidth * 0.5f, 250.0f );
	scores->showHighScores();
	addChild(scores, -1);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
