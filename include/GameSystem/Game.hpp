/*
 * © Copyright - Pikachuk - 2017 - All rights reserved
 */
#ifndef GAME_HPP
#define GAME_HPP
#include "GlobalHeader.hpp"
#include "GameSystem/GameEntity.hpp"
#include "GameSystem/Transform.hpp"
#include "GameSystem/FileSystem.hpp"
#include "Components/DisplayComponent.hpp"
#include "Components/UIComponent.hpp"
#include "Misc/Boundary.hpp"
#include "GameSystem/Input.hpp"


namespace DreamEngine {
	namespace GameSystem {
		class Scene;
		 class Game {
			friend class Input;
		public:
			Game(const std::string &Name);
			~Game();

			/**Initialise the main game window and the main renderer in order to start the game*/
			int Init(int xpos, int ypos, float w, float h, bool Fullscreen = false);
			 int Run();
			/**Get the input events*/
			void HandleEvents();
			/**Update all the GameEntities of the scene*/
			void Update();
			void FixedUpdate();
			/**Render all the sprites on the screen*/
			void Render();
			void Refresh();
			/**Render false is the game must close*/
			bool Running() const;
			void UpdateRatio(float w, float h);
			/**Get the full path of a relative path to a file (based on the binary location, READ ACCESS ONLY)*/
			static const std::string GetLocalFile(const std::string &file);
			/** Get the full path of a relative path to a file (based on the localdata location, WRITE AND READ ACCESS ALLOWED)*/
			static const std::string GetDataFile(const std::string &file);
			/** Get the full path of a relative path to a file (based on the localcache location, WRITE AND READ ACCESS ALLOWED*/
			static const std::string GetCacheFile(const std::string &file);
			/**Get the current resolution*/
			static const Scale GetResolution();
			/**Get the current SDL_Renderer*/
			static SDL_Renderer *GetGameRenderer();
			/**Get the current SDL_Window*/
			static SDL_Window *GetGameWindow();
			static SDL_Surface *GetGlobalSurface();
			/**Call the render function of any object*/
			template<class T>
			static void RenderObject(T *current) {
				if ((Components::DisplayComponent*)current || (Components::UIComponent*)current)
				{
					current->Render();
				}
			}
			/**Get the current Game instance*/
			static  Game *GameInstance;

		private:
			SDL_Window * GameWindow = nullptr;
			SDL_Renderer *GameRenderer = nullptr;
			SDL_Surface *GlobalSurface = nullptr;
			FileSystem fs;
			Scale m_Resolution;
			Scene *RootScene = nullptr;
			float m_ScaleFactor;
			std::string m_Name;
			//int count;
			bool isRunning;
		};
	};
};
#endif
