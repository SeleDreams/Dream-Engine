#include "GameSystem/GameEntity.hpp"
#include "GameSystem/Scene.hpp"
#include "GameSystem/SceneManager.hpp"
#include "Misc/Debug.hpp"
using namespace std;
using namespace DreamEngine::Components;
using namespace DreamEngine::GameSystem;

GameEntity::GameEntity(const std::string &Name) :
	Object(Name)

{
	AddComponent<Transform>(&transform);

	SceneManager::GetCurrentScene().GameEntities.push_back(this);

	SetActive(true);


	//Get the ID of the current entity
	m_ID = SceneManager::GetCurrentScene().GameEntities.size() - 1;

}
void GameEntity::SetActive(bool Active)
{
	Object::SetActive(Active);
	if (Active)
	{
		SceneManager::GetCurrentScene().toUpdate.push_back(this);
		m_UpdateID = SceneManager::GetCurrentScene().toUpdate.size() - 1;
	}
	else {
		// Avoid to try to update an object not even active, just skip it for performances
		SceneManager::GetCurrentScene().toUpdate[m_UpdateID] = nullptr;
		m_UpdateID = 0;
	}
}
GameEntity::~GameEntity() {

	//Delete all the components used by this entity to free memory
	for (auto c : m_Components)
	{
		if (c && typeid(*c) != typeid(transform))
		{
			c->m_OwnerGameEntity = nullptr;
			delete c;
		}
	}

	//Get a constant reference to the vector of child transforms
	const vector <Transform*> &childs(transform.GetChilds());

		//for each child i the vector, get the GameEntity and delete it
		for (const auto child : childs)
		{
			if (child)
			{
				GameEntity *entity = child->GetGameEntity();
				if (entity)
				{
					delete entity;
				}
				else
				{
					DreamEngine::Debug::Log::PrintLine("Error, the GameEntity of this Component from the delete function of GameEntity.cpp is null,\n"
						"please, check the code");
				}
			}
		}

		SceneManager::GetCurrentScene().GetGameEntities()[m_ID] = nullptr;
	if (m_Active)
	{
		SceneManager::GetCurrentScene().toUpdate[m_UpdateID] = nullptr;
	}
	Debug::Log::PrintLine("The GameEntity " + GetName() + " has been deleted");
}
void GameEntity::Update() {


		//Starts all the components not initialised and updates them
		for (const auto &c : m_Components)
		{
			if (c && c->isActive())
			{
				if (!c->m_isLaunched)
				{
					c->Launch();
				c->m_isLaunched = true;
				}
				c->Update();
			}
		}

		for (auto child : transform.m_Childs)
		{
			child->GetGameEntity()->Update();
		}

}

void GameEntity::FixedUpdate() {



		//Starts all the components not initialised and updates them
		for (const auto &c : m_Components)
		{
			if (c && c->isActive())
			{
				c->FixedUpdate();
			}
		}

		for (auto child : transform.m_Childs)
		{
			child->GetGameEntity()->FixedUpdate();
		}

}
int GameEntity::GetID() const {
	return m_ID;
}
