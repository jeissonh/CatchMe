#include "Scores.h"

USING_NS_CC;


Scores::ScoreInfo::ScoreInfo(std::string nickname, PointType points, int level)
	: nickname(nickname)
	, points(points)
	, level(level)
{
}

Scores::Scores()
{
	currentPlayer.points = UserDefault::getInstance()->getIntegerForKey("current_user_score", 0);
	loadHighScores();
}

Scores *Scores::create(const std::string &string, const std::string &fontName, float fontSize, const Size &dimensions, TextHAlignment hAlignment, TextVAlignment vAlignment)
{
	Scores *ret = new Scores();
	if(ret && ret->initWithString(string, fontName, fontSize, dimensions, hAlignment, vAlignment))
	{
		ret->showScore();
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
	UserDefault::getInstance()->setIntegerForKey("current_user_score", currentPlayer.points);
	showScore();
}

std::string lliToString(long long int number)
{
	char buffer[32];
	sprintf(buffer, "%04lli", number);
	return buffer;
}

void Scores::showScore()
{
	this->setString( lliToString(currentPlayer.points) );
}

void Scores::showHighScores()
{
	std::string text;
	for ( size_t i = 0; i < scores.size(); ++i )
		text += scores[i].nickname + ' ' + lliToString(scores[i].points) + '\n';

	this->setString(text);
}

void Scores::loadHighScores()
{
	char noplayer[64];
	for (size_t i = 0; i < 10; ++i)
	{
		sprintf(noplayer, "Player-%zi", i + 1);
		std::string nickname = UserDefault::getInstance()->getStringForKey(("scores_nickname_" + lliToString(i)).c_str(), noplayer);
		PointType points = UserDefault::getInstance()->getIntegerForKey(("scores_points_" + lliToString(i)).c_str());
		int level = UserDefault::getInstance()->getIntegerForKey(("scores_level_" + lliToString(i)).c_str());
		scores.push_back( ScoreInfo(nickname, points, level) );
	}
}
