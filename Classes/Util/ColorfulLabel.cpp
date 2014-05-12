#include "ColorfulLabel.h"

USING_NS_CC;

ColorfulLabel::ColorfulLabel()
	: _red(255) // Esto si es inicializacion
	, _green(255)
	, _blue(255)
{
	// Esto seria una asignacion, no inicializacion
	//_blue = _green =_red = 255;
}

ColorfulLabel* ColorfulLabel::create(const std::string& string, const std::string& fontName, float fontSize,
							   const Size &dimensions, TextHAlignment hAlignment,
							   TextVAlignment vAlignment)
{
	ColorfulLabel *ret = new ColorfulLabel();
	if(ret && ret->initWithString(string, fontName, fontSize, dimensions, hAlignment, vAlignment))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

void ColorfulLabel::nextColor()
{
	if ( rand() % 2 ) --_red;
	if ( rand() % 2 ) --_blue;
	if ( rand() % 2 ) --_green;
	setColor( Color3B(_red, _green, _blue) );
}

void ColorfulLabel::setEventHandlers()
{
	//Create a "one by one" touch event listener (processes one touch at a time)
   auto listener = EventListenerTouchOneByOne::create();
   // When "swallow touches" is true, then returning 'true' from the onTouchBegan method will "swallow" the touch event, preventing other listeners from using it.
   listener->setSwallowTouches(true);

   // Example of using a lambda expression to implement onTouchBegan event callback function
   listener->onTouchBegan = [](Touch* touch, Event* event){
	   // event->getCurrentTarget() returns the *listener's* sceneGraphPriority node.
	   auto target = static_cast<Sprite*>(event->getCurrentTarget());

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
   listener->onTouchMoved = [](Touch* touch, Event* event){
	   auto target = dynamic_cast<Sprite*>(event->getCurrentTarget());
	   //Move the position of current button sprite
	   target->setPosition(target->getPosition() + touch->getDelta());
   };

   //Process the touch end event
   listener->onTouchEnded = [=](Touch* touch, Event* event){
	   auto target = static_cast<Sprite*>(event->getCurrentTarget());
	   log("sprite onTouchesEnded.. ");
	   target->setOpacity(255);
   };

   //Add listener
   _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
   _eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), this);
   _eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), this);
}
