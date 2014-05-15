#include "ChainReactionScene.h"
#include "Ball.h"
#include "Util/Util.h"

USING_NS_CC;

Scene* ChainReactionScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ChainReactionScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ChainReactionScene::init()
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
										   CC_CALLBACK_1(ChainReactionScene::menuCloseCallback, this));

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

	loadBalls();
	for ( size_t i = 0; i < 13; ++i )
		addRandomBall();

	remainingTimeLabel = ColorfulLabel::create("CatchMe", "Fonts/NextGames.ttf", 24);

	// position the label on the center of the screen
	remainingTimeLabel->setPosition(Point(origin.x + visibleSize.width/2,
							origin.y + visibleSize.height - remainingTimeLabel->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(remainingTimeLabel, 1);

#if 0
	// add "ChainReactionScene" splash screen"
	auto sprite = Sprite::create("ChainReactionScene.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
#endif

	schedule( schedule_selector(ChainReactionScene::update) );
	schedule( schedule_selector(ChainReactionScene::updateTimer), 1.0f);
	setEventHandlers();

	return true;
}

void ChainReactionScene::setEventHandlers()
{
	//Create a "one by one" touch event listener (processes one touch at a time)
	auto listener = EventListenerTouchOneByOne::create();
	// When "swallow touches" is true, then returning 'true' from the onTouchBegan method will "swallow" the touch event, preventing other listeners from using it.
	listener->setSwallowTouches(true);

	// Example of using a lambda expression to implement onTouchBegan event callback function
	listener->onTouchBegan = CC_CALLBACK_2(ChainReactionScene::placeExplosion, this);

	//Add listener
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void ChainReactionScene::update(float df)
{
	for ( size_t i = 0; i < _ballClones.size(); ++i)
	{
		_ballClones[i]->update(df);
		if ( explosion && Util::collides(explosion, _ballClones[i] ) )
		{
			ParticleSystemQuad* particleSystem = ParticleExplosion::create();
			this->addChild(particleSystem, 10);
			particleSystem->setTexture( Director::getInstance()->getTextureCache()->addImage("Stars2.png") );
			particleSystem->setAutoRemoveOnFinish(true);
			particleSystem->setPosition( _ballClones[i]->getPosition() );
			particleSystem->setDuration(1.0f);

			log("Removing child %zi" , i + 1);
			removeChild(_ballClones[i]);
			_ballClones.erase( _ballClones.begin() + i );
		}
	}
}

void ChainReactionScene::updateTimer(float df)
{
	remainingTime -= 1.0f;
	char buffer[32];
	sprintf(buffer, "%.0f", remainingTime );

	remainingTimeLabel->setString(buffer);
}

void ChainReactionScene::loadBalls()
{
	for (size_t i = 0; i < 7; ++i)
	{
		auto ball = SpriteFrame::create("Balls.png", Rect(i * 40, 0, 40, 40));
		_ballFrames.push_back(ball);
	}
}

void ChainReactionScene::addRandomBall()
{
	size_t random = rand() % _ballFrames.size();
	auto ball = Ball::createWithSpriteFrame( _ballFrames[random] );
	_ballClones.push_back(ball);
	this->addChild(ball, 1);
}

bool ChainReactionScene::placeExplosion(Touch* touch, Event* event)
{
	if ( explosion ) return false;

	explosion = Sprite::create("Explosion.png");
	explosion->setPosition( touch->getLocation() );
	addChild(explosion, 2);
	return true;
}


void ChainReactionScene::menuCloseCallback(Ref* pSender)
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
