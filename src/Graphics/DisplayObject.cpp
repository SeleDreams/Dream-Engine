#include "Graphics/DisplayObject.hpp"
using namespace DreamEngine::GameSystem;

SDL_Rect *DisplayObject::GetDisplayRect()
{
    return &m_DisplayRect;
}

SDL_Rect *DisplayObject::GetNativeRes()
{
    return &m_NativeRes;
}
SDL_Rect *DisplayObject::GetSourceRect()
{
    return &m_SourceRect;
}
