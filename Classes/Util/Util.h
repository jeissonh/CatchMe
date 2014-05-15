#ifndef UTIL_H
#define UTIL_H

#include <cocos2d.h>

USING_NS_CC;

/** Class with some common utility methods
*/
class Util
{
  public:
	/// Do not make instances of this class
	Util() = delete;
	/// @brief Returns true if there is a collision between sprites @a node1 and @a node2
	/// @details Determines if the two images collides calculating a circle around them
	/// @param node1 The first sprite
	/// @param node2 The second sprite
	/// @param useWidthForRadius1 Send true if half width of node1 should be used as radius,
	/// false if half height should be used as radius
	/// @param useWidthForRadius2 Send true if half width of node2 should be used as radius,
	/// false if half height should be used as radius
	/// @return true if there is collsion, false otherwise
	static bool collides(const Node* node1, const Node* node2, bool useWidthForRadius1 = true, bool useWidthForRadius2 = true);
};

#endif // UTIL_H
