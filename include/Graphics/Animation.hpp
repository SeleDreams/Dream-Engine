#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include "GlobalHeader.hpp"
#include "GameSystem/Object.hpp"
#include "GameSystem/Scale.hpp"
#include "GameSystem/Position.hpp"
#include <vector>
namespace DreamEngine
{
namespace Components
{
class AnimationComponent;
};

namespace GameSystem
{
class Animation : public Object
{
    ////////////////////////////////////////////////Friends
    friend class Components::AnimationComponent;

  public:
    ////////////////////////////////////////////Public Functions

    Animation(const std::string &name);

    /**
     * @brief Creates an Animation from the informations
     *
    * @param Base position to start the animation
    * @param Scale of a single frame
    * @param Number of frames
    * @param Number of frames for one line
    * @param Frames per second
    */
    void CreateAnimation(const GameSystem::Position &BasePosition, const GameSystem::Scale &FrameScale, Uint32 FrameCount, Uint32 FramesPerLine, Uint32 FPS = 24);

    /**
    * @brief Sets the current animation frame
    *
    * @param frame
    */
    void SetCurrentFrame(Uint32 frame);

    /**
     * @brief Gets the Current Frame
     *
     * @return Uint32
     */
    Uint32 GetCurrentFrame() const;

    /**
     * @brief Gets the scale of one frame
     *
     * @return Scale
     */
    Scale GetFrameScale() const;

    /**
     * @brief Gets the current position of the frame
     *
     * @return GameSystem::Position
     */
    GameSystem::Position GetCurrentPosition() const;

    /**
     * @brief Gets whether or not the animation is playing
     *
     * @return true if playing
     * @return false if stopped
     */
    bool isPlaying() const;

    /**
     * @brief Gets wether or not the animation is looping
     *
     * @return true if looping
     * @return false if not
     */
    bool isLooping() const;

    /**
     * @brief Sets the animation loop
     *
     * @param must loop ?
     * @param Start loop frame
     * @param End loop frame
     */
    void SetLoop(bool loop, Uint32 Start = 0, Uint32 End = 0);

  protected:
    ////////////////////////////////////////////Protected Variables

Uint32 m_LoopStart,m_LoopEnd = 0;
    /**
     * @brief ID of the current frame
     *
     */
    Uint32 m_CurrentFrame = 0;

    /**
    * @brief Number of frames for the current animation
    *
    */
    Uint32 m_FrameCount = 0;

    /**
     * @brief FPS count of the current animation
     *
     */
    Uint32 m_FPS = 0;
    /**
   * @brief Vector containing the rects for all the frames
   *
   */
    std::vector<SDL_Rect> m_AnimationFrames;

    /**
    * @brief Current frame's rect
    *
    */
    SDL_Rect m_CurrentRect;

    /**
    * @brief Delay in milliseconds before next frame
    *
    */
    double m_FrameDelay = 0;

    /**
     * @brief Sets whether or not the animation is looping
    *
    */
    bool m_loop = true;

    /**
     * @brief Sets whether or not the animation is playing
     *
     */
    bool m_isPlaying;
};
};
};
#endif
