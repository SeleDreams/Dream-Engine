/*
 * © Copyright - Pikachuk - 2017 - All rights reserved
 */
#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP
#include "GlobalHeader.hpp"
#include "Transform.hpp"
#include "Scene.hpp"
#include <map>

namespace DreamEngine
{
namespace Components
{
class GameComponent;
};

namespace GameSystem
{
class Scene;
class GameEntity : public Object

{

	friend class Scene;

  public:
	/**Initialises the GameEntity and set its name*/
	GameEntity(const std::string &name);
	virtual ~GameEntity();

	/**Get the ID of the current GameEntity*/
	int GetID() const;
	void SetActive(bool active);
	template <class T>
	T *GetComponent()
	{
		for (auto *c : m_Components)
		{
			//try to cast the gamecomponent to the specified type, if it's succesfull, returns it
			T *temp = dynamic_cast<T*>(c);
			
			if (temp)
			{
				return temp;
			}
		}
		return nullptr;
	}
	template <class T>
	T *AddComponent(T *declared = nullptr)
	{
		if (!declared)
		{
			T *tempcomponent = new T;
			//Casts the specified component to the gamecomponent type and adds it to the components vector
			Components::GameComponent *temp = dynamic_cast<Components::GameComponent *>(tempcomponent);
			if (temp)
			{
				temp->m_OwnerGameEntity = this;

				m_Components.push_back(temp);
				temp->m_ComponentID = m_Components.size() - 1;
				return tempcomponent;
			}
			delete tempcomponent;
			return nullptr;
		}
		else
		{
			//if the component is already defined manually, simply add it to the vector
			Components::GameComponent *temp = (Components::GameComponent *)declared;
			if (temp)
			{
				m_Components.push_back(temp);
				temp->m_OwnerGameEntity = this;
				temp->m_ComponentID = m_Components.size() - 1;
				
				return declared;
			}
			return nullptr;
		}
	}

	/**Transform that represents the transform of the current GameEntity*/
	Components::Transform transform = Components::Transform();
	/**Function made in order to search the gameentity in the scene by its name*/
	static GameEntity *SearchEntity(const std::string &entity);

  private:
	virtual void Update();
	virtual void FixedUpdate();
	bool isLaunched;
	/**int that represents the index of the GameEntity in the GameEntities vector*/
	int m_ID;
	int m_UpdateID;
	/**Vector containing all the components of the entity*/
	std::vector<Components::GameComponent *> m_Components = std::vector<Components::GameComponent *>();
	virtual void Launch(){};
	virtual void Render(){};
};
};
};
#endif