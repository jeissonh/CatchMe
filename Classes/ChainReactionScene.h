#ifndef ChainReactionScene_h
#define ChainReactionScene_h

#include "cocos2d.h"
#include <vector>

// Forward declarations
class Ball;

class ChainReactionScene : public cocos2d::Layer
{
  protected:
	/// Los 7 frames para crear bolas
	std::vector<cocos2d::SpriteFrame*> _ballFrames;

	/// Las n bolas en la pantalla que ve el jugador
	std::vector<Ball*> _ballClones;

	cocos2d::Sprite* explosion = nullptr;

  public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(ChainReactionScene)

	/// Se invoca 60 veces por segundo, cada vez que se actualiza la pantalla
	void update(float df);

  protected:
	void loadBalls();
	void setEventHandlers();
	void addRandomBall();
	bool placeExplosion(cocos2d::Touch* touch, cocos2d::Event *event);
};

#endif // ChainReactionScene_h
