#ifndef UICOMPONENT_HPP
#define UICOMPONENT_HPP
#include <string>
#include "GlobalHeader.hpp"
#include "Components/GameComponent.hpp"
#include "GameSystem/GameEntity.hpp"
namespace DreamEngine{
	namespace Components {
		class Camera;
		class UIComponent : public GameComponent
		{
			friend class GameSystem::Game;
			friend class Components::Camera;
		public:
			void SetOpacity(float newOpacity);
		protected:
			UIComponent(const std::string &name);
			virtual ~UIComponent();
			struct Sort_By_Z
			{

				bool operator()(UIComponent *a, UIComponent *b) {
					return a->GetGameEntity()->transform.position.z < b->GetGameEntity()->transform.position.z;
				}
			};
			Uint32 m_ID;
			SDL_Rect m_TextRect;
			float m_PreviousZ;
			float m_Opacity;
			virtual void Render() {};
			virtual void Update();
			virtual void Launch() {};
		};
	};
};
#endif
