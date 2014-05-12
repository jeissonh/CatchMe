#ifndef BALL_H
#define BALL_H

#include <cocos2d.h>

class Ball : public cocos2d::Sprite
{
  protected:
	float x = 0;
	float y = 0;

  public:
	Ball();
	static Ball* createWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame);
	void update(float dt);
	inline float getRadius() const { getBoundingBox().size.width * 0.5f; }
};

#endif // BALL_H
