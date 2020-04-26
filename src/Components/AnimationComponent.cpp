#include "Components/AnimationComponent.hpp"
#include "GameSystem/Time.hpp"
#include "GlobalHeader.hpp"

using namespace DreamEngine::Components;
using namespace DreamEngine::GameSystem;
using namespace std;

AnimationComponent::AnimationComponent() : ImageComponent(typeid(this).name()), m_Animations(vector<Animation>())
{
}
int AnimationComponent::AddAnimation(const std::string &name, Animation anim)
{
    if (anim.m_FrameCount > 0 && !m_AnimationsDictionnary.count(name))
    {
        anim.SetName(name);

        m_Animations.push_back(anim);
        m_AnimationsDictionnary[name] = m_Animations.size() - 1;
        return EXIT_SUCCESS;

    }
        return EXIT_FAILURE;

}

void AnimationComponent::SetCurrentAnimation(const string &name)
{
    if (m_AnimationsDictionnary.count(name))
    {
      SetCurrentAnimation(m_AnimationsDictionnary[name]);
    }
}

void AnimationComponent::SetCurrentAnimation(Uint32 id)
{
    if (id < m_Animations.size())
    {
        m_CurrentAnimation = id;
    }
}
void AnimationComponent::Update()
{
    if (isActive())
    {
        double ms = (double)Time::GetDeltaTime();
        m_Animations[m_CurrentAnimation].m_FrameDelay -= ms;
        if (m_Animations[m_CurrentAnimation].m_FrameDelay <= 0)
        {
            m_Animations[m_CurrentAnimation].m_FrameDelay = (double)1 / (double)m_Animations[m_CurrentAnimation].m_FPS;
            m_Animations[m_CurrentAnimation].m_CurrentFrame++;
            if ( m_Animations[m_CurrentAnimation].m_CurrentFrame >  m_Animations[m_CurrentAnimation].m_FrameCount - 1)
            {
                m_Animations[m_CurrentAnimation].m_CurrentFrame = 0;
            }
           m_Image.m_SourceRect =  m_Animations[m_CurrentAnimation].m_AnimationFrames[ m_Animations[m_CurrentAnimation].m_CurrentFrame];
        }
        ImageComponent::Update();
    }
}
