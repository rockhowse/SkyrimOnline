#ifndef WORLD_H
#define WORLD_H

#include <boost/functional/hash.hpp>

struct Point2D
{
	int16_t x;
	int16_t y;

	bool operator==(const Point2D& aRhs) const
	{
		return (x == aRhs.x) && (y == aRhs.y);
	}
};

namespace std 
{
	template <> struct hash < Point2D >
	{
		size_t operator()(const Point2D & x) const
		{
			using boost::hash_value;
			using boost::hash_combine;

			std::size_t seed = 0;

			hash_combine(seed, hash_value(x.x));
			hash_combine(seed, hash_value(x.y));

			return seed;
		}
	};
}

class Player;
class Zone;
class World
{
public:

	World();
	~World();

	void Update();

	void Enter(Player* apPlayer);
	void Leave(Player* apPlayer);

private:
};

#endif // WORLD_H