#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
  protected:
	cocos2d::LabelTTF* label;
	GLubyte r;
	GLubyte g;
	GLubyte b;

  public:
	HelloWorld();
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

	/// Se llama aproximadamente 60 veces en un segundo para refrescar objetos en la pantalla
	void update(float df);
	/// Se invoca cuando el jugador ha presionado en uno o mas lugares de la pantalla
	virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);

  protected:
	/// Cada vez que se invoca, crea una nueva animacion para el titulo del juego
	void animateGameTitle();
	/// Se invoca cuando el jugador logra hacer click o tap sobre el escurridizo titulo del juego
	void gameTitleTapped();
};

#endif // __HELLOWORLD_SCENE_H__
