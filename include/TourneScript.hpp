#ifndef TOURNESCRIPT_HPP
#define TOURNESCRIPT_HPP
#include "GlobalHeader.hpp"
#include "Components/GameComponent.hpp"
namespace DreamEngine {
	namespace Components
	{
		class TourneScript : public GameComponent
		{

		public:
			TourneScript();
			int value;
		protected:
			void Update();
			virtual void Launch();
			virtual void Render() {};
		};
	};
};
#endif
