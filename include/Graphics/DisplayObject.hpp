#ifndef DISPLAYOBJECT_HPP
#define DISPLAYOBJECT_HPP
#include "GlobalHeader.hpp"
namespace DreamEngine
{
namespace GameSystem
{
class DisplayObject
{
  public:
    SDL_Rect *GetNativeRes();
    SDL_Rect *GetDisplayRect() ;
    SDL_Rect *GetSourceRect();

    protected:
    SDL_Rect m_DisplayRect,m_SourceRect,m_NativeRes;
};
};
};
#endif