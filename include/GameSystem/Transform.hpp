#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP
#include "GameSystem/Position.hpp"
#include "GameSystem/Rotation.hpp"
#include "GameSystem/Scale.hpp"
#include "Components/GameComponent.hpp"
#include <vector>
namespace DreamEngine
{
namespace Components
{

class Transform : public GameComponent
{
	friend class GameSystem::GameEntity;

  public:
	Transform();
	~Transform();
	Transform *GetParent() const;
	void SetParent(Transform &Parent);
	const std::vector<Transform *> &GetChilds() const;
	void AddChild(Transform &child);
	GameSystem::Position position;
	GameSystem::Position relativePosition;
	GameSystem::Scale scale;
	GameSystem::Rotation rotation;
	GameSystem::Rotation relativeRotation;
	GameSystem::Position GetDirectionFromPosition(const GameSystem::Position &position);
	void MoveTo(const GameSystem::Position &pos, float distance);
	void Move(const GameSystem::Position &direction, float distance);

  private:
	int childnumber;
	Transform *m_Parent;
	std::vector<Transform *> m_Childs;
	GameSystem::Position m_Previous = GameSystem::Position();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void Launch(){};
	virtual void Render(){};
};
};
};
#endif
