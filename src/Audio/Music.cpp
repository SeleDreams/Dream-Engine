#include "Audio/Music.hpp"
#include "GameSystem/FileSystem.hpp"
#include "Misc/Debug.hpp"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
using namespace DreamEngine::GameSystem;
using namespace DreamEngine::Debug;
using namespace std;

map<string, Mix_Music *> Music::LoadedMusics = map<string, Mix_Music *>();

int Music::LoadMusicFromDirectory(const std::string &relativePath)
{
	if (!LoadedMusics.count(relativePath))
	{

        char *buffer = nullptr;
        Sint64 size;

			if (FileSystem::GetBytesFromFile(relativePath,buffer,size) == EXIT_SUCCESS)
			{
				SDL_RWops *RWhandle = SDL_RWFromMem(buffer, size);
				if (RWhandle)
				{
					m_Music = Mix_LoadMUS_RW(RWhandle, 0);
					LoadedMusics[relativePath] = m_Music;
					Log::PrintLine("The audio " + relativePath + " has been successfully loaded");
				}

				return EXIT_SUCCESS;

		}
	}
	else
	{
		m_Music = LoadedMusics[relativePath];
		Log::PrintLine("The music " + relativePath + " was already loaded, so this object will use the same instance");
		return EXIT_SUCCESS;
	}
	Log::PrintLine("Error while loading the music " + relativePath + " Please, check the path and the file");
	return EXIT_FAILURE;
}
void Music::SetLoopPoints(double start, double end)
{
	m_loopStart = start;
	m_loopEnd = end;
}
