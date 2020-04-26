/*
 * © Copyright - Pikachuk - 2017 - All rights reserved
 */
#ifndef GLOBALHEADER_HPP
#define GLOBALHEADER_HPP

#define SDL_MAIN_HANDLED
#ifdef  __cplusplus_winrt
#include <winapifamily.h>
#ifdef WINAPI_FAMILY_SYSTEM
//#include <windows.h>
#define NOMINMAX
#endif
#endif
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <physfs.h>
#include <typeinfo>
#include <limits>

// usually this is in something like a utils or constants header
//

constexpr float Float_Epsilon = std::numeric_limits<float>::min();

#endif
