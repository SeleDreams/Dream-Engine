/*
 * © Copyright - Pikachuk - 2017 - All rights reserved
 */
#ifndef GAMECOMPONENT_H
#define GAMECOMPONENT_H
#include "GameSystem/Object.hpp"
#include <string>
namespace DreamEngine {
	namespace GameSystem
	{
		class GameEntity;
	};
	namespace Components {
		class GameComponent : public GameSystem::Object {
			friend class GameSystem::GameEntity;
		public:
			GameComponent(const std::string &name);
			GameSystem::GameEntity *GetGameEntity() const;
			virtual ~GameComponent() {};

		protected:

			virtual void Render() {};
			virtual void Launch() {};
			virtual void Update() {};
			virtual void FixedUpdate() {};
			bool m_isLaunched;
			 GameSystem::GameEntity *m_OwnerGameEntity = nullptr;
			int m_ComponentID;

		private:
		};

	};
};
#endif
