#ifndef SCORES_H
#define SCORES_H

#include <algorithm>
#include <vector>
#include <cocos2d.h>

typedef long long int PointType;

class Scores : public cocos2d::LabelTTF
{
  public:
	struct ScoreInfo
	{
	  friend class Scores;
	  protected:
		std::string nickname;
		PointType points = 0;
		int level = 0;
	  public:
		ScoreInfo(std::string nickname = "", PointType points = 0ll, int level = 0);
	};

  protected:
	std::vector<ScoreInfo> scores;
	ScoreInfo currentPlayer;

	void loadHighScores();
public:
	Scores();

	static Scores * create(const std::string& string, const std::string& fontName, float fontSize,
							 const cocos2d::Size& dimensions = cocos2d::Size::ZERO, cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::CENTER,
							 cocos2d::TextVAlignment vAlignment = cocos2d::TextVAlignment::TOP);

	/// Add the given points to the current player
	/// @param points the amount to be acredited to the player,
	/// send a negative number if player loses that points
	void addPoints(PointType points);
	void showScore();
	void showHighScores();
};

#endif // SCORES_H
