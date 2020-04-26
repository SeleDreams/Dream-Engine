#ifndef SCENE_HPP
#define SCENE_HPP
#include "GlobalHeader.hpp"
#include "Object.hpp"
#include "GameEntity.hpp"
#include <vector>
namespace DreamEngine {

	namespace Components {
		class UIComponent;
		class DisplayComponent;
	};
	namespace GameSystem {
		class GameEntity;
		class SceneManager;
		class Game;
		class Scene : public GameSystem::Object {
			friend class SceneManager;
			friend class Game;
			friend class GameEntity;
		public:
			Scene(const std::string &Pathconst, const std::string &Name = "New Scene");
			virtual ~Scene();
			std::vector<GameEntity*> &GetGameEntities() ;
			std::vector<Components::DisplayComponent*> &GetComponentsToRender() ;
			std::vector<Components::UIComponent*> &GetUIToRender()  ;
		private:
			std::vector<GameEntity*> GameEntities;
			std::vector<GameEntity*> toUpdate;
			std::vector<Components::DisplayComponent*> m_toRender;
			std::vector<Components::UIComponent*> m_RenderUI;

			virtual void Update();
			virtual void FixedUpdate();
			virtual void Render();
			virtual void Launch() {};
		};
	};
};
#endif