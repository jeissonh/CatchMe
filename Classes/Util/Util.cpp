#include "Util.h"

bool Util::collides(const Node* node1, const Node* node2, bool useWidthForRadius1, bool useWidthForRadius2)
{
	// Calculate the radius of each sprite
	float r1 = (useWidthForRadius1 ? node1->getBoundingBox().size.width : node1->getBoundingBox().size.height) * 0.5f;
	float r2 = (useWidthForRadius1 ? node2->getBoundingBox().size.width : node1->getBoundingBox().size.height) * 0.5f;

	// Calculate the distance between both sprites
	float dx = node1->getPositionX() - node2->getPositionX();
	float dy = node1->getPositionY() - node2->getPositionY();

	// If distance between sprites is less than the sum of the radius, there is a collision
	float d2 = dx * dx + dy * dy;
	return d2 <= (r1 + r2) * (r1 + r2);
}
