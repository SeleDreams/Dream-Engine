#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP
#include "GlobalHeader.hpp"
#include "Scene.hpp"
#include <vector>

namespace DreamEngine
{
	namespace GameSystem
	{
		class SceneManager {
			friend class Scene;
			friend class Game;
		public:
			/**Get the current Scene instance*/
		static	Scene &GetCurrentScene() ;
	//	static	std::vector<Scene*> *GetScenes() ;
		static	int GetSceneCount() ;
		static	void LoadScene(int ID);
		
			static void LoadScene(const std::string &Name);
		static	void LoadSceneAdditive(int ID);
		static	void LoadSceneAdditive(const std::string &Name);
		private:
			static void Init();
			static void Unload();
			static void AddScene();
		static	Scene *m_CurrentScene ;
		static	std::vector<Scene*> m_Scenes;

		};
	};
};
#endif