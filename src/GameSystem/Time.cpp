#include "GameSystem/Time.hpp"
#include <iostream>
using namespace std;
using namespace DreamEngine::GameSystem;
double Time::delta = 0.0F;
double Time::lastticktime = 0.0F;
double Time::FPS = 0.0F;
void Time::CalculateDelta()
{
	double currenttick = SDL_GetTicks();
	delta = (currenttick - lastticktime) / 1000;
	lastticktime = currenttick;


}
Uint32 Time::GetFPS()
{
	FPS = 1.0F / delta;
	return FPS;
}
double Time::GetDeltaTime()
{
	return delta;
}
double Time::GetTimeSinceStartup()
{
	return (double)SDL_GetTicks() / 1000;
}
