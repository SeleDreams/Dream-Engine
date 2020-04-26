#include "Components/PhysicObject.hpp"
#include "GlobalHeader.hpp"
#include "GameSystem/Transform.hpp"
#include "GameSystem/Physics.hpp"
#include "GameSystem/GameEntity.hpp"
#include "GameSystem/Time.hpp"

using namespace DreamEngine::GameSystem;
using namespace DreamEngine::Components;

void PhysicObject::SetMass(float mass)
{
    m_Mass = mass;
}

float PhysicObject::GetMass() const
{
    return m_Mass;
}
PhysicObject::PhysicObject() : GameComponent(typeid(this).name())
{
}
PhysicObject::PhysicObject(float mass) : PhysicObject()
{

    SetMass(mass);
}
void PhysicObject::SetVelocity(Position &velocity)
{
m_Velocity = velocity;
}
Position PhysicObject::GetVelocity() const{
    return m_Velocity;
}
void PhysicObject::FixedUpdate()
{
    //  Position cursorWorldPosition = Camera::GetCurrentCamera()->ScreenToWorldPosition(Input::GetCursorPosition());
    // Position cursorDirection = temp.GetDirectionFromPosition(cursorWorldPosition);

    float massObject = GetMass();
    double massOtherObject = 59736000; // cursor object "mass"

    // Position diff = cursorWorldPosition - temp.position;
    Position diff = Physics::GetGravity();
    // distance^2, we just don't take the sqrt
    float distSqr = diff.x * diff.x + diff.y * diff.y;

    // gravitational constant
    double G = 0.000000000066742;

    // gravitational function
    double F = G * massObject * massOtherObject;

    // hack to get zero distance to work, probably want to simply reduce the velocity instead
    F = distSqr <= Float_Epsilon ? 0 : F / distSqr;
    Position acceleration;
    double result = F / (double)massObject;
    if (result != 0)
    {
        acceleration = Physics::GetGravity(); // divide by mass of object we want to move

        // for normal game:
       m_Velocity += acceleration;
       m_Velocity *= Position(0.994f, 0.994f, 0.994f); // some form of friction
     //   float speed = m_Velocity.Length() ;
      //  if (speed > 10.0f)
     //   {
      //      m_Velocity = (m_Velocity / speed) * 100;
     //   }

    }
}
