#ifndef PHYSICS_HPP
#define PHYSICS_HPP
#include "Position.hpp"
namespace DreamEngine
{
namespace GameSystem
{
class Physics
{
  public:
    static Position GetGravity();
    static void SetGravity(Position gravity);

  private:
    static Position m_Gravity;
};
}; // namespace GameSystem
}; // namespace DreamEngine
#endif