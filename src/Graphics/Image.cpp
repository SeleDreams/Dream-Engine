#include "Graphics/Image.hpp"
#include "Misc/Debug.hpp"
#include "GameSystem/Game.hpp"
#include "GameSystem/GameEntity.hpp"
using namespace std;
using namespace DreamEngine::Components;
using namespace DreamEngine::GameSystem;
map<string, SDL_Surface *> Image::LoadedTextures = map<string, SDL_Surface *>();

void Image::Render(GameEntity &Entity)
{
    if (m_Texture)
    {

        SDL_BlitSurface(m_Texture,&m_SourceRect,Game::GetGlobalSurface(),&m_DisplayRect);
      //  SDL_RenderCopyEx(GameSystem::Game::GetGameRenderer(), m_Texture, &m_SourceRect, &m_DisplayRect, Entity.transform.rotation.Angle,
        //                 NULL, SDL_FLIP_NONE);
    }
}
void Image::Update(GameEntity &entity)
{
    m_DisplayRect.w = (m_SourceRect.w * entity.transform.scale.w);
    m_DisplayRect.h = (m_SourceRect.h * entity.transform.scale.h);
}

int Image::LoadImageFromMemory(const char *data, Sint64 size)
{

    if (data)
    {
        //Get the image from the file in memory
        SDL_RWops *rw = SDL_RWFromConstMem(data, size);
        if (rw)
        {
        SDL_Surface *TempSurface = nullptr;
         TempSurface =IMG_LoadPNG_RW(rw) ;
         m_Texture = SDL_ConvertSurfaceFormat(TempSurface,SDL_GetWindowPixelFormat(Game::GetGameWindow()),(Uint32)NULL);
         SDL_FreeSurface(TempSurface);
            if (!m_Texture)
            {
                Debug::Log::PrintLine("An error occured while loading the image from memory.\nPlease check that the file is correct and that your path doesn't contain errors.\n" + string(IMG_GetError()));
                return EXIT_FAILURE;
            }

         //   m_Texture = SDL_CreateTextureFromSurface(GameSystem::Game::GetGameRenderer(), TempSurface);

         //   SDL_FreeSurface(TempSurface);

            if (data)
            {
                delete[] data;
            }
            InitializeImageProperties();
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}
int Image::LoadImageFromDirectory(const string &RelativePath)
{
    m_Center.x = 0;
    m_Center.y = 0;
    if (!Image::LoadedTextures.count(RelativePath) || Image::LoadedTextures[RelativePath] == nullptr)
    {
        char *buffer(nullptr);
        Sint64 size;
        if (FileSystem::GetBytesFromFile(RelativePath, buffer, size) == EXIT_SUCCESS)
        {

            int result = LoadImageFromMemory(buffer, size);
            if (result == EXIT_SUCCESS)
            {
                Image::LoadedTextures[RelativePath] = m_Texture;
                return result;
            }
            else
            {
                return EXIT_FAILURE;
            }
        }
    }
    else
    {
        m_Texture = Image::LoadedTextures[RelativePath];
        return EXIT_SUCCESS;
    }
    Debug::Log::PrintLine("An error occured while loading the image " + RelativePath + " from disk." + "\n" + "Please check that the file is correct and that your path doesn't contain errors." + "\n" + string(IMG_GetError()));
    return EXIT_FAILURE;
}
void Image::InitializeImageProperties()
{
    int w, h = 0;
    UpdateScale(w, h);
    m_NativeRes.w = w;
    m_NativeRes.h = h;

    m_SourceRect.w = m_NativeRes.w;
    m_SourceRect.h = m_NativeRes.h;
    m_SourceRect.x = 0;
    m_SourceRect.y = 0;
    m_DisplayRect.w = m_NativeRes.w;
    m_DisplayRect.h = m_NativeRes.h;
    m_DisplayRect.x = 0;
    m_DisplayRect.y = 0;
}
void Image::UpdateScale(int &w, int &h)
{

   w =  m_Texture->w;
   h = m_Texture->h;
   // SDL_QueryTexture(m_Texture, NULL, NULL, &w, &h);
}
void Image::Crop(Uint32 x, Uint32 y, Uint32 width, Uint32 height)
{
    m_SourceRect.x = x;
    m_SourceRect.y = y;
    m_SourceRect.h = height;
    m_SourceRect.w = width;
}
