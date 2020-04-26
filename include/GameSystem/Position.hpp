#ifndef POSITION_HPP
#define POSITION_HPP
#include "MathHelper.hpp"
#include <cmath>

namespace DreamEngine
{
namespace GameSystem
{
class Position
{
  public:
	Position(float x = 0, float y = 0, float z = 0);
	float x, y, z = 0;

	inline float Length() { return sqrt(LengthSqr()); }
	inline float LengthSqr() { return x*x + y*y + z*z; }
};
};
};

#endif