#include "TourneScript.hpp"
#include "GameSystem/Transform.hpp"
#include "GameSystem/GameEntity.hpp"
#include "Components/Camera.hpp"
#include "GameSystem/Position.hpp"
#include "GameSystem/Input.hpp"
#include "Components/PhysicObject.hpp"
#include "GameSystem/Physics.hpp"
#include "GameSystem/Time.hpp"
using namespace DreamEngine::Components;
using namespace DreamEngine::GameSystem;

TourneScript::TourneScript() : GameComponent(typeid(this).name()), value(0)
{
}
void TourneScript::Launch()
{

}
void TourneScript::Update()
{

}
