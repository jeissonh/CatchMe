#include "Ball.h"

USING_NS_CC;

Ball::Ball()
{
	Size screenSize = Director::getInstance()->getWinSize();
	x = rand() % int(screenSize.width - 20);
	y = rand() % int(screenSize.height - 20);
}

Ball *Ball::createWithSpriteFrame(SpriteFrame *spriteFrame)
{
	Ball *ball = new Ball();
	if (spriteFrame && ball && ball->initWithSpriteFrame(spriteFrame))
	{
		ball->autorelease();
		return ball;
	}
	CC_SAFE_DELETE(ball);
	return nullptr;
}

void Ball::update(float dt)
{
	Size screenSize = Director::getInstance()->getWinSize();
	x += 3.5f;
	if ( x > screenSize.width - 20 ) x = -(screenSize.width - 20);

	y += 3.5f;
	if ( y > screenSize.height - 20 ) y = -(screenSize.height - 20);

	setPosition(abs(x), abs(y));
}
