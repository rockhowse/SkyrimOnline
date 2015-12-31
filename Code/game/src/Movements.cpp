#include "Movements.h"

float Norm(Messages::Vector3& aPoint)
{
	return std::sqrtf(aPoint.x * aPoint.x + aPoint.y * aPoint.y + aPoint.z * aPoint.z);
}

float Distance(Messages::Vector3 aPointA, Messages::Vector3 aPointB)
{
	Messages::Vector3 AtoB{ aPointA.x - aPointB.x, aPointA.y - aPointB.y, aPointA.z - aPointB.z };
	return Norm(AtoB);
}