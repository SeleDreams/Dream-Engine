#ifndef PHYSICOBJECT_HPP
#define PHYSICOBJECT_HPP
#include "GlobalHeader.hpp"
#include "Components/GameComponent.hpp"
#include "GameSystem/Position.hpp"
namespace DreamEngine
{
namespace Components
{
class PhysicObject : public GameComponent
{
  public:
    PhysicObject();
    PhysicObject(float mass);
    void SetMass(float mass);
    float GetMass() const;
    void SetVelocity(GameSystem::Position &velocity);
    GameSystem::Position GetVelocity() const;

  protected:
  GameSystem::Position m_Velocity;
    virtual void FixedUpdate();
    float m_Mass = 0.0F;

};
}; // namespace Components
}; // namespace DreamEngine
#endif
