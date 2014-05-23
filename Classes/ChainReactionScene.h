#ifndef ChainReactionScene_h
#define ChainReactionScene_h

#include "cocos2d.h"
#include <vector>
#include "Util/ColorfulLabel.h"

// Forward declarations
class Ball;
class Scores;

class ChainReactionScene : public cocos2d::Layer
{
  protected:
	/// Original images used to create balls on the scenery
	/// These are just image files
	std::vector<cocos2d::SpriteFrame*> _ballFrames;
	/// The n balls created on the screen using the ball frames as basis
	std::vector<Ball*> _ballClones;
	/// Pointer to the last explosion created on the scenery, nullptr if there is no
	/// currently an explosion.
	cocos2d::Sprite* _lastExplosion = nullptr;
	/// Player has initially a minute to create as many explosions as s/he can
	float _remainingTime = 60.0f;
	/// A label to show the remaining time to the user
	ColorfulLabel* _remainingTimeLabel = nullptr;
	/// A label showing the score of the current player on the screen
	Scores* _currenPlayerScore = nullptr;
	/// Score for an explosion increses when there is a chain. Each explosion has its own value.
	/// The first explosion credits for 1 point, the second explosion in the same chain credits
	/// for 2 points, and so on. Therefore a counter is required to count the number of explosions
	/// in the current chain
	size_t _chainedExplosionCount = 0;

  public:
	/// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
	/// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	/// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	/// implement the "static create()" method manually
	CREATE_FUNC(ChainReactionScene)
	/// Se invoca 60 veces por segundo, cada vez que se actualiza la pantalla
	void update(float df);
	/// Called once each second in order to update the time ramining label
	void updateRemainingTime(float df);

  protected:
	/// Create the original set of balls when the game is loaded
	void loadBalls();
	/// .
	void setEventHandlers();
	/// Creates a ball from the frames array and places it on some place of the screen
	void addRandomBall();
	/// .
	bool placeExplosion(cocos2d::Touch* touch, cocos2d::Event *event);
};

#endif // ChainReactionScene_h
