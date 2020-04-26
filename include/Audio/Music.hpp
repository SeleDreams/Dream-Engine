
#ifndef MUSIC_HPP
#define MUSIC_HPP
#include "GlobalHeader.hpp"
#include <string>
#include <map>

namespace DreamEngine::GameSystem{
     class MusicManager;
class Music{
    friend class MusicManager;
public:
int LoadMusicFromDirectory(const std::string &relativePath);
void SetLoopPoints(double start, double end);
Uint32 GetPosition();
void SetPosition(Uint32 value);
private:

Mix_Music *m_Music = nullptr;
double m_loopStart, m_loopEnd;
int m_LoopCounter;
static std::map<std::string, Mix_Music*> LoadedMusics;
};
};
#endif