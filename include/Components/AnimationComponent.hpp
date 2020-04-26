#ifndef ANIMATIONCOMPONENT_HPP
#define ANIMATIONCOMPONENT_HPP
#include "GlobalHeader.hpp"
#include "Components/ImageComponent.hpp"
#include "GameSystem/Transform.hpp"
#include "Graphics/Animation.hpp"
#include <vector>
#include <map>

namespace DreamEngine
{
namespace Components
{
class AnimationComponent : public ImageComponent
{
public:
  AnimationComponent();
  /**
  * @brief Adds an animation and returns its ID
  *
  * @param Name of the added animation in the map
  * @param Animation to add
  * @return -1 if failed
  */
  int AddAnimation(const std::string &name,GameSystem::Animation anim);

  /**
   * @brief Plays the animation
   *
   * @param name
   */
  void Play();

  /**
   * @brief Stops the currently playing animation
   *
   */
  void StopAnimation();

void SetCurrentAnimation(const std::string &name);
void SetCurrentAnimation(Uint32 id);
protected:
  virtual void Update();
  int m_CurrentAnimation = 0;
 std::vector<GameSystem::Animation> m_Animations;
 std::map<std::string,int> m_AnimationsDictionnary;
};
};
};
#endif
