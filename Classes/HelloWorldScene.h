#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Util/ColorfulLabel.h"

class HelloWorld : public cocos2d::Layer
{
protected:
	ColorfulLabel* labelGameTitle;

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	/// Se invoca 60 veces por segundo, cada vez que se actualiza la pantalla
	void update(float df);

	/// Mueve el titulo del juego a otra poaicion asignandole una nueva accion
	void animateGameTitle();

  protected:
    void setEventHandlers();
};

#endif // __HELLOWORLD_SCENE_H__
