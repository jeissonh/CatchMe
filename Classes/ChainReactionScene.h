#ifndef ChainReactionScene_h
#define ChainReactionScene_h

#include "cocos2d.h"

class ChainReactionScene : public cocos2d::Layer
{
  protected:

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
	void setEventHandlers();
};

#endif // ChainReactionScene_h
