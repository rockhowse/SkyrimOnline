#ifndef MOVEMENTS_H
#define MOVEMENTS_H

#include <cstdint>
#include <list>
#include <string>
#include "CliGame_Handler.h"

float Norm(Messages::Vector3& aPoint);
float Distance(Messages::Vector3 aPointA, Messages::Vector3 aPointB);

template <uint32_t ToHold>
class MovementTracker
{
public:

	MovementTracker()
	{}
	~MovementTracker()
	{}

	void Add(const Messages::Movement& acMovement)
	{
		if (m_movements.size() >= ToHold)
		{
			m_movements.pop_front();
		}
		m_movements.push_back(acMovement);
	}

	const Messages::Movement& GetLatest() const
	{
		return m_movements.back();
	}

	const std::list<Messages::Movement>& GetMovements()
	{
		return m_movements;
	}

private:

	std::list<Messages::Movement> m_movements;
};


#endif // MOVEMENTS_H