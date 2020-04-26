#include "GameSystem/SceneManager.hpp"
#include "GameSystem/Scene.hpp"
#include "Misc/Debug.hpp"
using namespace std;
using namespace DreamEngine::GameSystem;

DreamEngine::GameSystem::Scene *SceneManager::m_CurrentScene = nullptr;
vector<DreamEngine::GameSystem::Scene*> SceneManager::m_Scenes = vector<DreamEngine::GameSystem::Scene*>();
void SceneManager::Init()
{
	Scene *rootscene = new Scene("RootScene");
	m_Scenes.push_back(rootscene);
	m_CurrentScene = rootscene;
}
/*vector<Scene*> *SceneManager::GetScenes() const{
return m_Scenes;
}*/
void SceneManager::Unload()
{

    for (auto scene : m_Scenes)
    {

        delete scene;
		scene = nullptr;
    }

}

DreamEngine::GameSystem::Scene &SceneManager::GetCurrentScene()  {

    return *m_CurrentScene;

}
int SceneManager::GetSceneCount() {
    return m_Scenes.size();
}
