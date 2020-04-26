#include "GameSystem/GameEntity.hpp"
#include "Audio/MusicManager.hpp"
#include "Audio/Music.hpp"
#include "GameSystem/Object.hpp"
#include "Misc/Debug.hpp"
#include "GameSystem/Time.hpp"
#include <iostream>
using namespace std;
using namespace DreamEngine::Components;
using namespace DreamEngine::GameSystem;
using namespace DreamEngine::Debug;
// Defines the global loaded musics dictionnary
int MusicManager::m_CurrentState = Stopped;
double MusicManager::m_CurrentPosition = 0;
int MusicManager::m_LoopCounter = 0;
Music MusicManager::m_Music = Music();
int MusicManager::m_PlayedBytes = 0;
double MusicManager::m_SecondsSinceStart = 0;
double MusicManager::m_PreviousSeconds = 0;
void MusicManager::MusicEnded()
{
	if (m_Music.m_loopStart == 0 && m_Music.m_loopEnd == 0)
	{
		m_CurrentState = Stopped;
		m_CurrentPosition = 0;
	}
	else
	{
		m_CurrentPosition = m_Music.m_loopStart;
		m_SecondsSinceStart = m_Music.m_loopStart;
		Mix_SetMusicPosition(m_Music.m_loopStart);
	}
}
Music &MusicManager::SetMusic(Music music)
{
	m_Music = music;
	m_PlayedBytes = 0;
	m_CurrentPosition = 0;
	Mix_SetPostMix(&LengthCallback, NULL);
	return m_Music;
}

Music &MusicManager::GetMusic()
{
	return m_Music;
}

void MusicManager::UpdateMusic()
{
}
void MusicManager::LengthCallback(void *udata, Uint8 *stream, int len)
{
	double currenttime = Time::GetTimeSinceStartup();

	if (m_PreviousSeconds != 0)
	{

		m_SecondsSinceStart = currenttime - m_PreviousSeconds;
		m_CurrentPosition += m_SecondsSinceStart;
		//Log::PrintLine(string("the music is at position ") + to_string(m_CurrentPosition));
		if (m_CurrentPosition >= m_Music.m_loopEnd && m_Music.m_loopEnd)
		{
			m_CurrentPosition = m_Music.m_loopStart;

			m_SecondsSinceStart = m_Music.m_loopStart;
			Mix_SetMusicPosition(m_Music.m_loopStart);
		}
	}
	m_PreviousSeconds = currenttime;
}

void MusicManager::ChangeMusicState(AudioStates state)
{
	Debug::Log::PrintLine("music state changed");
	if (m_Music.m_Music)
	{
		switch (state)
		{
		case Playing:
			if (m_CurrentState == Stopped)
			{
				Mix_PlayMusic(m_Music.m_Music, 1);
				m_PreviousSeconds = Time::GetTimeSinceStartup();
				m_CurrentState = AudioStates::Playing;

				Mix_VolumeMusic(100);
			}
			else if (m_CurrentState == Paused)
			{
				Mix_ResumeMusic();
				m_CurrentState = AudioStates::Playing;
			}
			break;
		case Paused:
			Mix_PauseMusic();
			m_CurrentState = AudioStates::Paused;
			break;
		case Stopped:
			Mix_HaltMusic();

			Mix_RewindMusic();
			m_CurrentState = AudioStates::Stopped;
			m_CurrentPosition = 0;
			m_LoopCounter = 0;
			break;
		default:
			break;
		}
	}
}
