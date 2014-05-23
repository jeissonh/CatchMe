#include "ChainReactionScene.h"
#include "Ball.h"
#include "Util/Scores.h"
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
	// Init parent first
	if ( !Layer::init() ) return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	// Add a menu item with "X" image, which is clicked to quit the program
	auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(ChainReactionScene::menuCloseCallback, this));
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2, origin.y + closeItem->getContentSize().height/2));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);

	// Create and place the original balls on the scenery
	loadBalls();
	for ( size_t i = 0; i < 13; ++i )
		addRandomBall();

	// Create and place the label to show the remaining time
	_remainingTimeLabel = ColorfulLabel::create("CatchMe", "Fonts/NextGames.ttf", 24);
	_remainingTimeLabel->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height - _remainingTimeLabel->getContentSize().height));
	this->addChild(_remainingTimeLabel, 1);

	// Create and place the label to show the score of current player
	_currenPlayerScore = Scores::create("0000", "Fonts/NextGames.ttf", 24);
	_currenPlayerScore->setPosition(Point(origin.x + visibleSize.width - _currenPlayerScore->getContentSize().width, origin.y + visibleSize.height - _currenPlayerScore->getContentSize().height));
	addChild(_currenPlayerScore, 1);

	// Call update methods the
	schedule( schedule_selector(ChainReactionScene::update) );
	schedule( schedule_selector(ChainReactionScene::updateRemainingTime), 1.0f);

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
	for ( size_t i = 0; i < _ballClones.size(); ++i )
	{
		_ballClones[i]->update(df);
		if ( _lastExplosion && Util::collides(_lastExplosion, _ballClones[i] ) )
		{
			++_chainedExplosionCount;
			ParticleSystemQuad* particleSystem = ParticleExplosion::create();
			this->addChild(particleSystem, 10);
			particleSystem->setTexture( Director::getInstance()->getTextureCache()->addImage("Stars2.png") );
			particleSystem->setAutoRemoveOnFinish(true);
			particleSystem->setPosition( _ballClones[i]->getPosition() );
			particleSystem->setDuration(1.0f);

			// Update the score
			_currenPlayerScore->addPoints(_chainedExplosionCount);

			log("Removing child %zi", i + 1);
			removeChild(_ballClones[i]);
			_ballClones.erase( _ballClones.begin() + i );
		}
	}
}

void ChainReactionScene::updateRemainingTime(float df)
{
	_remainingTime -= 1.0f;
	char buffer[32];
	sprintf(buffer, "%.0f", _remainingTime );

	_remainingTimeLabel->setString(buffer);
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
	if ( _lastExplosion ) return false;

	_lastExplosion = Sprite::create("Explosion.png");
	_lastExplosion->setPosition( touch->getLocation() );
	addChild(_lastExplosion, 2);
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
