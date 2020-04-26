#include "GameSystem/Physics.hpp"

using namespace DreamEngine::GameSystem;

Position Physics::m_Gravity = Position(0, 9.81);

Position Physics::GetGravity()
{
    return m_Gravity;
}
void Physics::SetGravity(Position gravity)
{
    m_Gravity = gravity;
}
