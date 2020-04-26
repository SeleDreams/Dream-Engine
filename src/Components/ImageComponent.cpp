#include "Components/ImageComponent.hpp"
#include "GlobalHeader.hpp"
#include "GameSystem/GameEntity.hpp"
#include "Misc/Debug.hpp"
#include "GameSystem/Game.hpp"
#include "GameSystem/SceneManager.hpp"
using namespace std;
using namespace DreamEngine::Components;
using namespace DreamEngine::GameSystem;

ImageComponent::ImageComponent(const string &componentname) : DisplayComponent(componentname)
{

}
ImageComponent::ImageComponent() : ImageComponent(typeid(this).name())
{
}
void ImageComponent::Launch()
{
	Debug::Log::PrintLine("Image component of the " + GetGameEntity()->GetName() + " GameEntity successfully initialised");

	SceneManager::GetCurrentScene().GetComponentsToRender().push_back(this);
}

ImageComponent::~ImageComponent()
{
	Debug::Log::PrintLine("test");
}

void ImageComponent::Render()
{
	if (isActive())
	{
		m_Image.Render(*GetGameEntity());
	}
}

void ImageComponent::SetImage(Image image)
{
	m_Image = image;
	m_DisplayObject = &m_Image;
}
Image *ImageComponent::GetImage()
{
	return &m_Image;
}
void ImageComponent::Update()
{
	if (isActive())
	{
		m_Image.Update(*GetGameEntity());
	}
}
