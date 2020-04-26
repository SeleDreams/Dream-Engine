#include "Components/Camera.hpp"
#include "GameSystem/Object.hpp"
#include "GameSystem/Game.hpp"
#include "GameSystem/SceneManager.hpp"
#include "Components/DisplayComponent.hpp"
#include "Components/GameComponent.hpp"
#include "Misc/Debug.hpp"

#include <algorithm>
using namespace std;
using namespace DreamEngine::Components;
using namespace DreamEngine::GameSystem;
using namespace DreamEngine::Debug;
Camera *Camera::CurrentCamera(nullptr);
Camera::Camera() : GameComponent(typeid(this).name())
{

	SetResolution(Game::GetResolution().w, Game::GetResolution().h);
	if (!GetCurrentCamera())
	{
		SetCurrentCamera(this);
	}

}
Camera::~Camera()
{

}
/**
 * @brief Sets the resolution of the camera in order to set the correct rendering boundaries
 *
 * @param w
 * @param h
 */
void Camera::SetResolution(int w, int h)
{
	m_RenderRect.w = w;
	m_RenderRect.h = h;
}
/**
 * @brief Get the current active camera
 *
 * @return a pointer to the current Camera*
 */
Camera *Camera::GetCurrentCamera()
{
	return CurrentCamera;
}
/**
 * @brief Sets the current active camera
 *
 * @param pointer to the camera to use
 */
void Camera::SetCurrentCamera(Camera *current)
{
	CurrentCamera = current;
}

/**
 * @brief Disables the current camera
 *
 * @param current
 */
void  DeleteCamera(Camera &current)
{
	for (auto cam : SceneManager::GetCurrentScene().GetGameEntities())
	{

		 Camera *temp = cam->GetComponent<Camera>();
		if (temp && temp != &current)
		{
			Camera::SetCurrentCamera(temp);
		}

	}
}
/**
 * @brief Renders the current frame, the disabled GameEntities and
 * the disabled  DisplayComponent and UIComponent are ignored
 * the UIComponent is always rendered after the DisplayComponent
 */
void Camera::RenderFrame()
{
	if (m_Active)
	{
		CalculateScreenBoundaries();

		vector<DisplayComponent*> &RenderList = SceneManager::GetCurrentScene().GetComponentsToRender();
		if (m_MustSortDisplay)
		{
			std::sort(RenderList.begin(), RenderList.end(), DisplayComponent::Sort_By_Z());
			m_MustSortDisplay = false;
		}
		for (auto renderObject : RenderList)
		{
			if (renderObject && renderObject->m_DisplayObject && MustRender(*renderObject))
			{
				// cout << renderObject->m_DisplayObject->GetName() << endl;
				Position current = WorldToScreenPosition(renderObject->GetGameEntity()->transform.position);
				renderObject->m_DisplayObject->GetDisplayRect()->x = (current.x - renderObject->m_DisplayObject->GetDisplayRect()->w / 2) + Game::GetResolution().w / 2;
				renderObject->m_DisplayObject->GetDisplayRect()->y = (current.y - renderObject->m_DisplayObject->GetDisplayRect()->h / 2) + Game::GetResolution().h / 2;
				Game::RenderObject(renderObject);
			}
			else if (renderObject){
				//Debug::Log::PrintLine("Sprite " + renderObject->m_DisplayObject->GetGameEntity()->GetName() + " not rendered because out of camera boundaries");

			}
		}
		vector <UIComponent*> &UIList = SceneManager::GetCurrentScene().GetUIToRender();
		if (m_MustSortUI)
		{
			std::sort(UIList.begin(), UIList.end(), UIComponent::Sort_By_Z());
			m_MustSortUI = false;
		}
		for (auto uiObject : UIList)
		{
			Game::RenderObject(uiObject);

		}
	}
}
/**
 * @brief Checks if the camera must render the current displaycomponent based on the boundaries of the camera
 *
 * @param reference to a DisplayComponent instance
 * @return true if the displaycomponent is in the camera boundaries
 * @return false if the displaycomponent is outside the camera boundaries
 */
bool Camera::MustRender(DisplayComponent &instance) {
	Position pos = instance.GetGameEntity()->transform.position;
	Boundary instanceBoundaries;
	SDL_Rect *temp = instance.m_DisplayObject->GetDisplayRect();

	//calculate the boundaries of the sprite
	instanceBoundaries.MinX = pos.x - (temp->w / 2);
	instanceBoundaries.MinY = pos.y - (temp->h / 2);
	instanceBoundaries.MaxX = pos.x + (temp->w / 2);
	instanceBoundaries.MaxY = pos.y + (temp->h / 2);

	return instanceBoundaries.CollidesWith(CameraBoundaries);

}

/**
 * @brief Calculates the screen boundaries depending on the camera resolution
 *
 */
void Camera::CalculateScreenBoundaries()
{
	//A boundary is calculated by calculating the position minus the resolution divided by two
	CameraBoundaries.MinX = GetGameEntity()->transform.position.x - (Game::GetResolution().w / 2);
	CameraBoundaries.MinY = GetGameEntity()->transform.position.y - (Game::GetResolution().h / 2);
	CameraBoundaries.MaxX = GetGameEntity()->transform.position.x + (Game::GetResolution().w / 2);
	CameraBoundaries.MaxY = GetGameEntity()->transform.position.y + (Game::GetResolution().h / 2);
}


void Camera::Launch()
{

}

void Camera::Update()
{
	CalculateScreenBoundaries();
	if (m_Active)
	{
		//cout << "test" << endl;
		// GetGameEntity()->transform.position.x -= 1;
		// GetGameEntity()->transform.position.y -= 1;
	}
}

Position Camera::WorldToScreenPosition(const Position &WorldPos)
{
    Position temp = WorldPos;
    temp -= GetGameEntity()->transform.position;
    return temp;
}

Position Camera::ScreenToWorldPosition(const Position &WorldPos)
{
    Scale tempscale = Game::GetResolution();
    Position temp = WorldPos;
    temp.x += GetGameEntity()->transform.position.x - tempscale.w /2;
    temp.y += GetGameEntity()->transform.position.y - tempscale.h /2;
    return temp;
}
