
#include "GlobalHeader.hpp"
#include "GameSystem/SceneManager.hpp"
#include "GameSystem/Scene.hpp"
#include "Misc/Debug.hpp"
#include "Components/ImageComponent.hpp"
#include "Components/TextComponent.hpp"
#include "Audio/MusicManager.hpp"
#include "TourneScript.hpp"
#include "Components/AnimationComponent.hpp"
#include "Components/PhysicObject.hpp"
#include "Components/Camera.hpp"
#include "GameSystem/Input.hpp"
#include "GameSystem/Time.hpp"
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;
using namespace DreamEngine::GameSystem;
using namespace DreamEngine::Components;
using namespace DreamEngine;

Game *Game::GameInstance = nullptr;

Game::Game(const string &Name) : m_Name(Name)

{

	m_Name = Name;
}

int Game::Init(int xpos, int ypos, float w, float h, bool Fullscreen)
{
	m_Resolution.h = h;
	m_Resolution.w = w;
	SceneManager::Init();

	Game::GameInstance = this;
	Debug::Log::StartDebugging();

	//Checks if the SDL is correctly initialised
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		Debug::Error::DisplayFatalError("SDL error", "An error occured while initialising SDL : " + string(SDL_GetError()));
	}

	if (TTF_Init() < 0)
	{
		Debug::Error::DisplayFatalError("SDL_ttf error", "An error occured while initialising SDL_ttf : " + string(TTF_GetError()));
	}

	if (!IMG_Init(IMG_INIT_PNG))
	{
		Debug::Error::DisplayFatalError("SDL_IMG error", "An error occured while initialising SDL_IMG : " + string(IMG_GetError()));
	}

	/*	if (!Mix_Init(MIX_INIT_OGG))
	{
		Debug::Error::DisplayFatalError("SDL_mixer error", "An error occured while initialising SDL_mixer : " + string(Mix_GetError()));
	}*/
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
	{
		Debug::Error::DisplayFatalError("SDL_mixer error", "An error occured while opening audio : " + string(Mix_GetError()));
	}

	int flags = SDL_WINDOW_RESIZABLE;
	if (Fullscreen)
	{
		flags += SDL_WINDOW_FULLSCREEN;
	}

	GameWindow = SDL_CreateWindow(m_Name.c_str(), xpos, ypos, w, h, flags);
	if (!GameWindow)
	{
		Debug::Error::DisplayFatalError("SDL error", "An error occured while creating the SDL window : " + string(SDL_GetError()));
	}

	//Now, create the main renderer
	GameRenderer = SDL_CreateRenderer(GameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!GameRenderer)
	{
		Debug::Error::DisplayFatalError("SDL error", "An error occured while creating the SDL renderer : " + string(SDL_GetError()));
	}
	isRunning = true;
	SDL_SetRenderDrawColor(GameRenderer, 0, 0, 0, 255);
	fs.InitPath(GetLocalFile("Assets/GRAPHICS.PEA").c_str(), "GRAPHICS");
	fs.InitPath(GetLocalFile("Assets/FONTS.PEA").c_str(), "FONTS");
	fs.InitPath(GetLocalFile("Assets/AUDIO.PEA").c_str(), "AUDIO");

	Input::INITIALIZEKEYS();
	UpdateRatio(w, h);
	GlobalSurface = SDL_CreateRGBSurface(SDL_GetWindowPixelFormat(GameWindow), w, h, 32, 0, 0, 0, 0);
	if (GlobalSurface == NULL)
	{
		Debug::Log::PrintLine(string("SDL_CreateRGBSurface() failed: ") + SDL_GetError());
	}

	return EXIT_SUCCESS;
}
SDL_Surface *Game::GetGlobalSurface()
{
	return GameInstance->GlobalSurface;
}
int Game::Run()
{
	int count = 0;

	const int targetFPS = 144;
	const int framedelay = 1000 / targetFPS;
//	double accumulator = 0;
//	const int FixedDeltaTime = 10;
	Uint32 FrameStart = 0;
	Uint32 delta = 0;
	Uint32 previoustime = 0;
	int temp = 0;
	int value = 0;
	while (Running())
	{
		FrameStart = SDL_GetTicks();
		delta = FrameStart - previoustime;
		value = delta;

		temp += value;
	//	accumulator += 1;
		if (temp >= framedelay)
		{
			while (temp > 0)
			{
				FixedUpdate();
				temp -= 1;
			}
			++count;
			Time::CalculateDelta();
			HandleEvents();

			Update();
			Render();

			Debug::Log::PrintLine(to_string(Time::GetFPS()) + " FPS");
		}

		previoustime = FrameStart;
	}
	return EXIT_SUCCESS;
}
//Clean the game window and renderer
Game::~Game()
{
	SceneManager::Unload();

	//Destroy the renderer
	if (GameRenderer)
	{
		SDL_DestroyRenderer(GameRenderer);
	}
	//Destroy the window
	if (GameWindow)
	{
		SDL_DestroyWindow(GameWindow);
	}
	if (GlobalSurface)
	{
		SDL_FreeSurface(GlobalSurface);
	}
	IMG_Quit();
	TTF_Quit();
	Mix_CloseAudio();
	SDL_Quit();
	Debug::Log::PrintLine("Game Cleaned");
	Debug::Log::StopDebugging();
}
GameEntity *latest = nullptr;
//Update the scripts each frame and add one frame everytime
void Game::Update()
{

	MusicManager::UpdateMusic();
	/*	if (MusicManager::m_CurrentState == Playing)
	{
		MusicManager::UpdatePosition();
	}*/
	//	float v =  Input::GetAxis(AxisID::RVertical);
	//	float h = Input::GetAxis(AxisID::RHorizontal);
	if (Input::GetKey("Up"))
	{
		Camera::GetCurrentCamera()->GetGameEntity()->transform.position.y -= (double)10 * Time::GetDeltaTime() * 100;
		//Debug::Log::PrintLine(to_string(v));
	}
	if (Input::GetKey("Down"))
	{
		Camera::GetCurrentCamera()->GetGameEntity()->transform.position.y += (double)10 * Time::GetDeltaTime() * 100;
		//Debug::Log::PrintLine(to_string(v));
	}
	if (Input::GetKey("Left"))
	{
		Camera::GetCurrentCamera()->GetGameEntity()->transform.position.x -= (double)10 * Time::GetDeltaTime() * 100;
	}
	if (Input::GetKey("Right"))
	{
		Camera::GetCurrentCamera()->GetGameEntity()->transform.position.x += (double)10 * Time::GetDeltaTime() * 100;
	}
	if (Input::GetKey("E"))
	{
		Camera::GetCurrentCamera()->GetGameEntity()->transform.position = latest->transform.position;
	}
	if (Input::GetMouseLeftButton())
	{
		Position mousepos = Input::GetCursorPosition();
		Scale res = Game::GetResolution();
		mousepos.x += Camera::GetCurrentCamera()->GetGameEntity()->transform.position.x - res.w / 2;
		mousepos.y += Camera::GetCurrentCamera()->GetGameEntity()->transform.position.y - res.h / 2;
		//high_resolution_clock::time_point t1 = high_resolution_clock::now());
		GameEntity *test(new GameEntity("Sonic"));

		AnimationComponent *animation(test->AddComponent<AnimationComponent>(nullptr));

		Image image = Image();
		image.LoadImageFromDirectory("GRAPHICS/Sprites/spritesheet.png");
		animation->SetImage(image);
		Position pos;
		pos.x = 0;
		pos.y = 0;
		Scale sc;
		sc.w = 130;
		sc.h = 130;
		Animation anim = Animation("anim");
		anim.CreateAnimation(pos, sc, 4, 4, 24);
		animation->AddAnimation("BasicTest", anim);
		animation->SetCurrentAnimation("BasicTest");
		test->transform.position.x = mousepos.x;
		test->transform.position.y = mousepos.y;
		PhysicObject *ts(test->AddComponent<PhysicObject>(nullptr));
		ts->SetMass(50);
	}

	SceneManager::GetCurrentScene().Update();
	//Debug::Log::PrintLine("Current FPS : " + to_string(1000 / Time::GetDeltaTime()));
}

void Game::FixedUpdate()
{
	SceneManager::GetCurrentScene().FixedUpdate();
}
//update all the graphics
void Game::Render()
{
	if (!GlobalSurface)
	{
		GlobalSurface = SDL_CreateRGBSurface(SDL_GetWindowPixelFormat(GameWindow), GetResolution().w, GetResolution().h, 32, 0, 0, 0, 0);
	}

	SceneManager::GetCurrentScene().Render();
	SDL_Texture *texture = SDL_CreateTextureFromSurface(GetGameRenderer(), GetGlobalSurface());
	SDL_Rect res;
	res.w = GetGlobalSurface()->w;
	res.h = GetGlobalSurface()->h;
	res.x = 0;
	res.y = 0;
	SDL_RenderCopyEx(GetGameRenderer(), texture, &res, &res, 0, nullptr, SDL_FLIP_NONE);
	SDL_DestroyTexture(texture);
	SDL_FillRect(GlobalSurface, &res, SDL_MapRGB(GetGlobalSurface()->format, 255, 255, 255));
	SDL_RenderPresent(GameRenderer);
}

const string Game::GetLocalFile(const string &file)
{
	string tempstring(SDL_GetBasePath());
	tempstring += file;
	Debug::Log::PrintLine(tempstring);
	return tempstring;
}
const string Game::GetCacheFile(const string &file)
{
	return Game::GetLocalFile(file);
}
const string Game::GetDataFile(const string &file)
{
	return Game::GetLocalFile(file);
}
const Scale Game::GetResolution()
{

	Scale temp;
	int w, h;
	//SDL_RenderGetLogicalSize(Game::GameInstance->GameRenderer, &w, &h);
	SDL_GetWindowSize(Game::GameInstance->GameWindow, &w, &h);
	temp.w = w;
	temp.h = h;

	return temp;
}
SDL_Renderer *Game::GetGameRenderer()
{
	return Game::GameInstance->GameRenderer;
}
SDL_Window *Game::GetGameWindow()
{
	return Game::GameInstance->GameWindow;
}
bool Game::Running() const
{
	return isRunning;
}
void Game::UpdateRatio(float w, float h)
{
	/*if (w < 800 || h < 600)
	{
		float temp = w / h;

		if ((float)16 / (float)9 == temp)
		{
			SDL_RenderSetLogicalSize(GameRenderer, 1280, 720);
		}
		else  if ((float)5 / (float)3 == temp)
		{
			SDL_RenderSetLogicalSize(GameRenderer, 1280, 768);
		}
		else if ((float)16 / (float)10 == temp)
		{
			SDL_RenderSetLogicalSize(GameRenderer, 1280, 800);
		}
		else if ((float)4 / (float)3 == temp)
		{
			SDL_RenderSetLogicalSize(GameRenderer, 800, 600);
		}

		else {

			SDL_RenderSetLogicalSize(GameRenderer, 1280, 720);
		}
	}
	else if (w >= 1920 || h >= 1080)
	{
		SDL_RenderSetLogicalSize(GameRenderer, w, h);
	}*/
}
float value = 0;
void Game::HandleEvents()
{
	Input::UPDATEKEYS();
}
