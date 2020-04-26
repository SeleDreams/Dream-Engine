#ifndef TIME_HPP
#define TIME_HPP
#include "GlobalHeader.hpp"
#include "Game.hpp"

namespace DreamEngine {
	namespace GameSystem {
		enum Days : char;
		struct TimePoint
		{
			Days day;
		};
		class Time
		{

			friend Game;
		public:
			static double GetDeltaTime();
			static  Uint32 GetFPS();
			static double GetTimeSinceStartup();
			enum Days : char {
				Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday
			};
		private:
			static void CalculateDelta();
			static double delta;
			static double FPS;
			static double lastticktime;
		};
	};
};
#endif