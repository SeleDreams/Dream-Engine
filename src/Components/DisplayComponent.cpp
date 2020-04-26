#include "Components/DisplayComponent.hpp"
#include "GameSystem/FileSystem.hpp"
#include "GameSystem/Scene.hpp"
#include "GameSystem/SceneManager.hpp"
#include "Misc/Debug.hpp"
#include "Components/Camera.hpp"
#include <string>
#include <algorithm>

using namespace std;

using namespace DreamEngine::Components;
using namespace DreamEngine::GameSystem;

DisplayComponent::DisplayComponent(const std::string &name) : GameComponent(name)
{


}
void DisplayComponent::Launch()
{
m_PreviousZ = GetGameEntity()->transform.position.z;
Camera::GetCurrentCamera()->m_MustSortDisplay = true;

 SceneManager::GetCurrentScene().GetComponentsToRender().push_back(this);
 m_DisplayID = SceneManager::GetCurrentScene().GetComponentsToRender().size() -1;
}

DisplayComponent::~DisplayComponent()
{
	if (SceneManager::GetCurrentScene().GetComponentsToRender().size() >= m_DisplayID - 1)
	{
		SceneManager::GetCurrentScene().GetComponentsToRender()[m_DisplayID] = nullptr;
	}
}

 void DisplayComponent::Update()
 {
	 if (!Camera::GetCurrentCamera()->m_MustSortDisplay && GetGameEntity()->transform.position.z != m_PreviousZ)
	 {
		 m_PreviousZ = GetGameEntity()->transform.position.z;

		 Camera::GetCurrentCamera()->m_MustSortDisplay = true;
	 }
 }
