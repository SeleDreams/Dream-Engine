#include "GameSystem/Transform.hpp"
#include "GameSystem/GameEntity.hpp"
#include "Components/PhysicObject.hpp"
#include "GameSystem/Time.hpp"
#include <cmath>

using namespace std;
using namespace DreamEngine::Components;
using namespace DreamEngine::GameSystem;
Transform::Transform() : GameComponent("Transform"), position(Position()), scale(Scale()), rotation(Rotation()), m_Parent(nullptr)
{
}
Transform::~Transform()
{
}
Transform *Transform::GetParent() const
{
	return m_Parent;
}
void Transform::FixedUpdate()
{

}

void Transform::Update()
{
	PhysicObject *obj = GetGameEntity()->GetComponent<PhysicObject>();
	if (obj)
	{
		Position pos = Position(obj->GetVelocity().x, obj->GetVelocity().y) * Time::GetDeltaTime();

		position += ((m_Previous + pos) / 2.0f) ;
		m_Previous = pos;
	}
	if (m_Parent)
	{
		float xdif = position.x - m_Parent->position.x;
		float ydif = position.y - m_Parent->position.y;
		if (relativePosition.x != xdif)
		{
			relativePosition.x = xdif;
		}
		if (relativePosition.y != ydif)
		{
			relativePosition.y = ydif;
		}
		scale.w = m_Parent->scale.w * scale.w;
		scale.h = m_Parent->scale.h * scale.h;
	}
	if (rotation.Angle > 360)
	{

		rotation.Angle -= 360;
	}
	else if (rotation.Angle < 0)
	{
		rotation.Angle += 360;
	}
}
void Transform::SetParent(Transform &Parent)
{

	Parent.AddChild(*this);
}
const vector<Transform *> &Transform::GetChilds() const
{
	return m_Childs;
}
void Transform::AddChild(Transform &child)
{
	child.m_Parent = this;
	m_Childs.push_back(&child);
}
Position Transform::GetDirectionFromPosition(const Position &position)
{
	float XDif = position.x - this->position.x;
	float YDif = position.y - this->position.y;
	float result = sqrt(XDif * XDif + YDif * YDif);

	// should returns the facing of the current transform
	if (result <= Float_Epsilon)
		return Position();

	XDif /= result;
	YDif /= result;
	return Position(XDif, YDif, 0);
}
void Transform::MoveTo(const Position &pos, float distance)
{
	Move(GetDirectionFromPosition(pos), distance);
}

void Transform::Move(const Position &direction, float distance)
{
	this->position += direction * distance;
}
