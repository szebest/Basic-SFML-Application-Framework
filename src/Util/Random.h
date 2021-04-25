#ifndef RANDOM_H
#define RANDOM_H

#include <ctime>
#include <random>

class Random
{
public:
	static Random& get()
	{
		return random;
	}

	Random()
		: generator(std::time(nullptr))
	{

	}

	int getIntInRange(int lo, int hi)
	{
		std::uniform_int_distribution<> dis(lo, hi);

		return dis(generator);
	}

	float getFloatInRange(float lo, float hi)
	{
		std::uniform_real_distribution<float> dis(lo, hi);

		return dis(generator);
	}

private:
	static Random random;

	std::default_random_engine generator;
};

Random Random::random;

#endif

