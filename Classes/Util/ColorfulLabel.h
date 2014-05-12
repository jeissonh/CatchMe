#ifndef COLORFULLABEL_H
#define COLORFULLABEL_H

#include <cocos2d.h>

class ColorfulLabel : public cocos2d::LabelTTF
{
  protected:
	GLubyte _red;
	GLubyte _green;
	GLubyte _blue;
	bool _increasing = false; // C++11

  public:
	ColorfulLabel();
	static ColorfulLabel * create(const std::string& string, const std::string& fontName, float fontSize,
		const cocos2d::Size& dimensions = cocos2d::Size::ZERO, cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::CENTER,
		cocos2d::TextVAlignment vAlignment = cocos2d::TextVAlignment::TOP);

	/// Changes the color of this label for a similar one
	/// The change is inmediately shown on screen
	void nextColor();
	/// ToDo: comments
	void setEventHandlers();
};

#endif // COLORFULLABEL_H
