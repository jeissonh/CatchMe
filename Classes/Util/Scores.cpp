#include "Scores.h"

USING_NS_CC;

Scores::Scores()
{
}

Scores *Scores::create(const std::string &string, const std::string &fontName, float fontSize, const Size &dimensions, TextHAlignment hAlignment, TextVAlignment vAlignment)
{
	Scores *ret = new Scores();
	if(ret && ret->initWithString(string, fontName, fontSize, dimensions, hAlignment, vAlignment))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

void Scores::addPoints(PointType points)
{/*
	currentPlayer.points += points;
	if ( currentPlayer.points < 0 )
		currentPlayer.points = 0;
	*/
	currentPlayer.points = std::max(currentPlayer.points + points, 0ll);

	char buffer[32];
	sprintf(buffer, "%04lli", currentPlayer.points);
	this->setString(buffer);
}
