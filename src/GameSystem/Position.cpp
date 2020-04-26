#include "GameSystem/MathHelper.hpp"
#include "GameSystem/Position.hpp"
#include "Components/Camera.hpp"
#include "GameSystem/Game.hpp"
#include <cmath>

using namespace std;
using namespace DreamEngine::GameSystem;
using namespace DreamEngine::Components;
Position::Position(float x, float y, float z) : x(x), y(y), z(z)
{
}
