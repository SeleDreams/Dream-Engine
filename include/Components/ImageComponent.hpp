
/*
 * © Copyright - Pikachuk - 2018 - All rights reserved
 */
#ifndef IMAGECOMPONENT_HPP
#define IMAGECOMPONENT_HPP
#include "GlobalHeader.hpp"
#include "Components/DisplayComponent.hpp"
#include "Graphics/Image.hpp"
#include <map>

namespace DreamEngine
{
namespace GameSystem
{
class GameEntity;
class Scene;
class Game;
};
namespace Components
{
class ImageComponent : public DisplayComponent
{
	friend class GameSystem::Scene;
	friend class GameSystem::Game;

  public:
	ImageComponent();
	ImageComponent(const std::string &componentname);
	virtual ~ImageComponent();
	GameSystem::Image *GetImage();
	void SetImage(GameSystem::Image image);

  protected:
	GameSystem::Image m_Image;
	virtual void Update();
	virtual void Render();
	virtual void Launch();
};
};
};
#endif
