#include "GameSystem/Scene.hpp"
#include "GameSystem/SceneManager.hpp"
#include "Components/ImageComponent.hpp"
#include "Audio/MusicManager.hpp"
#include "Misc/Debug.hpp"
#include "Components/Camera.hpp"
#include "GameSystem/GameEntity.hpp"
using namespace std;
using namespace DreamEngine::GameSystem;
using namespace DreamEngine::Components;
using namespace DreamEngine::Debug;

Scene::Scene(const std::string &Pathconst, const std::string &Name) :
	Object(Name),
	GameEntities(vector<GameEntity*>()),
	toUpdate(vector<GameEntity*>()),
	m_toRender(vector<DisplayComponent*>()),
	m_RenderUI(vector<UIComponent*>())
{

}
Scene::~Scene()
{

		for (auto entity : GameEntities)
		{
			delete entity;
		}

	for ( auto &tex : Image::LoadedTextures)
	{
		SDL_FreeSurface(tex.second);
		Debug::Log::PrintLine("Sprite " + tex.first + " successfully deleted");
	}
/*	for (auto &mus : MusicManager::LoadedMusics)
	{
		Mix_FreeMusic(mus.second);
		Debug::Log::PrintLine("Music " + mus.first + " Successfully deleted");
	}*/
}

vector<GameEntity*> &Scene::GetGameEntities() {
	return GameEntities;
}

void Scene::Update()
{
		//for each GameEntity in the vector
		for (auto entity : toUpdate)
		{
			//if the GameEntity exists, is active and doesn't have a parent
			if (entity && entity->isActive() && !(entity->transform.GetParent()))
			{
				entity->Update();
			}
		}

}
void Scene::FixedUpdate()
{
		//for each GameEntity in the vector
		for (auto entity : toUpdate)
		{
			//if the GameEntity exists, is active and doesn't have a parent
			if (entity && entity->isActive() && !(entity->transform.GetParent()))
			{
				entity->FixedUpdate();
			}
		}
}
vector<DisplayComponent*> &Scene::GetComponentsToRender()
{
	return m_toRender;
}
vector<UIComponent*> &Scene::GetUIToRender()
{
	return m_RenderUI;
}
void Scene::Render()
{
	if (Camera::GetCurrentCamera() && Camera::GetCurrentCamera()->isActive())
	{
		Camera::GetCurrentCamera()->RenderFrame();
	}
	else {
		Debug::Log::PrintLine("RENDER ERROR : There isn't any active camera in the current Scene");
	}
}
