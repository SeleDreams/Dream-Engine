#ifndef DISPLAYCOMPONENT_HPP
#define DISPLAYCOMPONENT_HPP
#include "GlobalHeader.hpp"
#include "GameSystem/Transform.hpp"
#include "Misc/Boundary.hpp"
#include "GameSystem/GameEntity.hpp"
#include "Graphics/DisplayObject.hpp"
namespace DreamEngine {
	namespace GameSystem
	{
		class Game;
		class GameEntity;
	};
	namespace Components {
		class GameComponent;
		class Camera;
		class DisplayComponent : public GameComponent
		{
			friend class GameSystem::Game;
			friend class Camera;
		public:



		protected:
			DisplayComponent(const std::string &name);
			DisplayComponent();
			virtual ~DisplayComponent();
			virtual void Launch();
			virtual void Render() {};
			Uint32 m_DisplayID = 0;
			int m_Depth = 0;
			Boundary m_RenderBoundary = Boundary();
			SDL_Rect m_ScreenRect = SDL_Rect();
			virtual void Update();
			float m_PreviousZ = 0;
			float m_Opacity = 1;
			GameSystem::DisplayObject *m_DisplayObject = nullptr;
			struct Sort_By_Z
			{
				bool operator()(DisplayComponent *a, DisplayComponent *b) {
					return a->GetGameEntity()->transform.position.z < b->GetGameEntity()->transform.position.z;
				}
			};
		};

	};
};
#endif
