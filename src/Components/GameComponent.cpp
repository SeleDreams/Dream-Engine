#include "Components/GameComponent.hpp"
#include "GameSystem/GameEntity.hpp"
using namespace DreamEngine::Components;
using namespace DreamEngine::GameSystem;
GameComponent::GameComponent(const ::std::string &name) : Object(name)
{
	m_Active = true;
}

 GameEntity *GameComponent::GetGameEntity() const
{
	return m_OwnerGameEntity;
}
