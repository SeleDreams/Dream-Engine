#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "GlobalHeader.hpp"
#include "Components/GameComponent.hpp"
#include "Components/DisplayComponent.hpp"
#include "GameSystem/Transform.hpp"
#include "GameSystem/Object.hpp"
namespace DreamEngine
{
namespace Components
{
class Camera : public GameComponent
{
	friend class DisplayComponent;
	friend class UIComponent;

  public:
	Camera();
	~Camera();
	void SetResolution(int w, int h);
	static void SetCurrentCamera(Camera *current);
	static void DeleteCamera(Camera &current);
	static Camera *GetCurrentCamera();
	void RenderFrame();
	void CalculateScreenBoundaries();
	bool MustRender(DisplayComponent &instance);

	GameSystem::Position WorldToScreenPosition(const GameSystem::Position &WorldPos);
	GameSystem::Position ScreenToWorldPosition(const GameSystem::Position &ScreenPos);

  private:
	SDL_Rect m_RenderRect;
	Boundary CameraBoundaries;
	static Camera *CurrentCamera;
	bool m_MustSortDisplay;
	bool m_MustSortUI;

  protected:
	virtual void Update();

	virtual void Launch();
	virtual void Render(){};
};
};
};
#endif
