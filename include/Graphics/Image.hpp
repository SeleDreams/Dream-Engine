#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <map>
#include "GameSystem/Object.hpp"
#include "GlobalHeader.hpp"
#include "Graphics/DisplayObject.hpp"
namespace DreamEngine
{
namespace Components
{
class ImageComponent;
class Transform;
class AnimationComponent;
};
namespace GameSystem
{
class Scene;
class GameEntity;
class Image : public DisplayObject
{

    friend class Components::ImageComponent;
    friend class Components::AnimationComponent;
    friend class Scene;

  public:
    ///////////////////////////////////////////////////////Public Functions
    /**
             * @brief Loads an image from a char array
             *
             * @param char array containing the image
             * @return EXIT_SUCCESS if the image is loaded, EXIT_FAILURE if it failed
             */
    int LoadImageFromMemory(const char *data, Sint64 size);

    /**
             * @brief Loads an image from a path
             *
             * @param Path to the file relative to the current process directory
             * @return EXIT_SUCCESS if the image is loaded, EXIT_FAILURE if it failed
             */
    int LoadImageFromDirectory(const std::string &RelativePath);

    /**
             * @brief Crops an image to display only a part of it
             *
             * @param x
             * @param y
             * @param width
             * @param height
             */
    void Crop(Uint32 x = 0, Uint32 y = 0, Uint32 width = 0, Uint32 height = 0);

  private:
    ////////////////////////////////////////////////////Private Functions
    /**
     * updates the native scale of the image
     */
    virtual void UpdateScale(int &w, int &h);
    virtual void InitializeImageProperties();
    virtual void Render(GameEntity &Entity);
    virtual void Update(GameEntity &Entity);
    ////////////////////////////////////////////////////Private Members
    SDL_Surface *m_Texture = nullptr;
    static std::map<std::string, SDL_Surface *> LoadedTextures;
    SDL_Point m_Center;
    bool m_LoadedFromMemory = false;
    bool m_LoadedFromDirectory = false;
};
};
};
#endif
