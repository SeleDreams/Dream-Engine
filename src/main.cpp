#include "GlobalHeader.hpp"
#include "GameSystem/Game.hpp"
#include "Components/Camera.hpp"
#include "Misc/Debug.hpp"
#include "Components/ImageComponent.hpp"
#include "Audio/MusicManager.hpp"
#include <iostream>
using namespace DreamEngine::GameSystem;
using namespace DreamEngine::Components;
using namespace std;

void InitObjects()
{
	GameEntity *camera(new GameEntity("Camera"));
	camera->AddComponent<Camera>(nullptr);
	GameEntity *background = new GameEntity("Background");
	ImageComponent *component = background->AddComponent<ImageComponent>();
	Image image;
	image.LoadImageFromDirectory("GRAPHICS/Sprites/ghill.png");
	component->SetImage(image);
	background->transform.position.x = 0;
	//PrintError("An error occured");
	Music mus;
	mus.LoadMusicFromDirectory("AUDIO/MUSIC/act 1.ogg");
	mus.SetLoopPoints(38.4, 134.325);
	MusicManager::SetMusic(mus);
	MusicManager::ChangeMusicState(Playing);
}

int main(int argc, char **argv)
{
	Game game = Game("Test");
	//	auto displayInformation = DisplayInformation::GetForCurrentView();
	//Uint32 w = displayInformation->ScreenWidthInRawPixels;
	//Uint32 h = displayInformation->ScreenHeightInRawPixels;
	if (game.Init(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false))
	{
		return EXIT_FAILURE;
	}

	InitObjects();
	return game.Run();
}

/**
*Small workaround for UWP
**/
int SDL_main(int argc, char **argv)
{
	return main(argc, argv);
}
