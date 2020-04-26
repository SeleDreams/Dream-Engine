#include "Components/UIComponent.hpp"
#include "GameSystem/SceneManager.hpp"
#include "GameSystem/Scene.hpp"
#include "Components/Camera.hpp"

using namespace DreamEngine::Components;
using namespace DreamEngine::GameSystem;
UIComponent::UIComponent( const std::string &name) : GameComponent(name)
{
   SceneManager::GetCurrentScene().GetUIToRender().push_back(this);
    m_ID = SceneManager::GetCurrentScene().GetUIToRender().size() - 1;
	m_PreviousZ =GetGameEntity()->transform.position.z;
Camera::GetCurrentCamera()->m_MustSortUI = true;
}
UIComponent::~UIComponent()
{
	if (SceneManager::GetCurrentScene().GetUIToRender().size() >= m_ID - 1)
	{
		SceneManager::GetCurrentScene().GetUIToRender()[m_ID] = nullptr;
	}

}
void UIComponent::Update()
{
	if (!Camera::GetCurrentCamera()->m_MustSortUI &&GetGameEntity()->transform.position.z != m_PreviousZ)
	{
		m_PreviousZ =GetGameEntity()->transform.position.z;

		Camera::GetCurrentCamera()->m_MustSortUI = true;
	}
}
