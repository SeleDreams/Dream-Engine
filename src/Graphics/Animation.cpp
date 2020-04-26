#include "Graphics/Animation.hpp"
#include <math.h>
using namespace DreamEngine::GameSystem;
using namespace DreamEngine::Components;
using namespace std;

Animation::Animation(const string &name) : Object(name)
{

}
void Animation::CreateAnimation(const Position &BasePosition, const Scale &FrameScale, Uint32 FrameCount, Uint32 FramesPerLine, Uint32 FPS)
{
    // first let's clear the vector and reserve the right amount of frames
    m_AnimationFrames.clear();
    m_AnimationFrames.reserve(FrameCount);
//Let's set the private variables
    m_FPS = FPS;
    m_FrameDelay = (double)1 / (double)FPS;
    m_FrameCount = FrameCount;

    //Now we can create the temp variable made to store the frame data
    SDL_Rect temp;
    temp.h = FrameScale.h;
    temp.w = FrameScale.w;

    int reallinescount = ceil(FrameCount / FramesPerLine) + 1;
    for (int line = 0; line < reallinescount; line++)
    {
        temp.y = BasePosition.y + line * (FrameScale.h + BasePosition.y);
        if (line != reallinescount)
        {
            for (Uint32 i = 0; i < FramesPerLine; i++)
            {
                temp.x = BasePosition.x + (i * FrameScale.w);
                m_AnimationFrames.push_back(temp);
            }
        }

        else
        {
            int frames = FrameCount - ((reallinescount - 1) * FramesPerLine);
            for (int i = 0; i < frames; i++)
            {
                temp.x = BasePosition.x + (i * FrameScale.w);
                m_AnimationFrames.push_back(temp);
            }
        }
    }
}

void Animation::SetCurrentFrame(Uint32 frame)
{
    if (m_FrameCount > 0)
    {
        m_CurrentFrame = frame;
    }
}

void Animation::SetLoop(bool loop, Uint32 Start, Uint32 End)
{
    m_loop = loop;
    m_LoopStart = Start;
    m_LoopEnd = End;
}

Uint32 Animation::GetCurrentFrame() const
{
    return m_CurrentFrame;
}

Position Animation::GetCurrentPosition() const
{
    Position temp;
    temp.x = m_CurrentRect.x;
    temp.y = m_CurrentRect.y;
    return temp;
}

Scale Animation::GetFrameScale() const
{
    Scale temp;
    temp.w = m_CurrentRect.w;
    temp.h = m_CurrentRect.h;
    return temp;
}

bool Animation::isPlaying() const{
    return m_isPlaying;
}

bool Animation::isLooping() const{
    return m_loop;
}
