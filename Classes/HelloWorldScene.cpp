#include "HelloWorldScene.h"

USING_NS_CC;

HelloWorld::HelloWorld()
	: r ( 128 + rand() % 128)
	, g ( 128 + rand() % 128)
	, b ( 128 + rand() % 128 )
{
}

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

	label = LabelTTF::create("CatchMe", "Fonts/Gameboy.ttf", 72);

	// position the label on the center of the screen
	label->setPosition(Point(origin.x + visibleSize.width/2,
							origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	// add "HelloWorld" splash screen"
//	auto sprite = Sprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
//	sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
//	this->addChild(sprite, 0);

	schedule( schedule_selector(HelloWorld::update) );
	animateGameTitle();

#if 0
/*
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
*/

	auto listener1 = EventListenerTouchOneByOne::create();
	// When "swallow touches" is true, then returning 'true' from the onTouchBegan method will "swallow" the touch event, preventing other listeners from using it.
	listener1->setSwallowTouches(true);

	// Example of using a lambda expression to implement onTouchBegan event callback function
	listener1->onTouchBegan = [](Touch* touch, Event* event)
	{
		log("sprite onTouchesEnded.. ");
		// event->getCurrentTarget() returns the *listener's* sceneGraphPriority node.
		auto target = static_cast<Node*>(event->getCurrentTarget());

		//Get the position of the current point relative to the button
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		//Check the click area
		if (rect.containsPoint(locationInNode))
		{
			log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
			target->stopAllActions();
			return true;
		}
		return false;
	};

	//Trigger when moving touch
	listener1->onTouchMoved = [](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		//Move the position of current button sprite
		target->setPosition(target->getPosition() + touch->getDelta());
	};

	//Process the touch end event
	listener1->onTouchEnded = [=](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		log("sprite onTouchesEnded.. ");
		target->stopAllActions();
	};

	static EventDispatcher* _eventDispatcher = new EventDispatcher();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, label);

#endif

	return true;
}

static GLubyte newColor()
{
	GLubyte amount = 1 + rand() % 3;
	return rand() % 2 ? amount : -amount;
}

void HelloWorld::update(float df)
{
	r += newColor();
	g += newColor();
	b += newColor();
	label->setColor( Color3B(r, g, b) );
}

static Point generateRandomPoint(const Node* node)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float nodeWidth = node->getContentSize().width;
	float nodeHeight = node->getContentSize().height;
	int width = visibleSize.width - nodeWidth;
	int height = visibleSize.height - nodeHeight;
	return Point(rand() % width + nodeWidth * 0.5f, rand() % height + nodeHeight * 0.5f);
}

void HelloWorld::animateGameTitle()
{
	auto randomPoint = generateRandomPoint(label);
	auto moveTo = MoveTo::create( 0.5f + rand() % 50 / 100.0f, randomPoint);
	auto callFunc = CallFunc::create( this, callfunc_selector(HelloWorld::animateGameTitle) );
	auto sequence = Sequence::create( moveTo, callFunc, nullptr );
	label->runAction( sequence );
}

void HelloWorld::gameTitleTapped()
{
	label->stopAllActions();
}

void HelloWorld::onTouchesBegan(const std::vector<Touch*>& touches, Event */*unused_event*/)
{
	for ( size_t i = 0; i < touches.size(); ++i )
	{
		auto tappedPoint = touches[i]->getLocation();
		if ( label->getBoundingBox().containsPoint(tappedPoint) )
			gameTitleTapped();
	}
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
