#ifndef MOVEMENTS_H
#define MOVEMENTS_H

#include <cstdint>
#include <list>
#include <string>

class Movement
{
public:

	float m_x;
	float m_y;
	float m_z;
	float m_heading;
};

template <uint32_t ToHold>
class MovementTracker
{
public:

	MovementTracker()
	{}
	~MovementTracker()
	{}

	void Add(const Movement& acMovement)
	{
		if (m_movements.size() >= ToHold)
		{
			m_movements.pop_front();
		}
		m_movements.push_back(acMovement);
	}

	Movement GetLatest()
	{
		return m_movements.back();
	}

	const std::list<Movement>& GetMovements()
	{
		return m_movements;
	}

private:

	std::list<Movement> m_movements;
};


#endif // MOVEMENTS_H