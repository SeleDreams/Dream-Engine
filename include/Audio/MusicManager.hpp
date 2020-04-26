#ifndef MusicManager_HPP
#define MusicManager_HPP
#include "GlobalHeader.hpp"
#include "Components/GameComponent.hpp"
#include "GameSystem/Object.hpp"
#include "Audio/Music.hpp"
namespace DreamEngine
{
namespace GameSystem
{
enum AudioStates
{
	Playing,
	Paused,
	Stopped,
	Ended
};

class MusicManager
{
	friend class Game;
	friend class Scene;

  public:


	/**
	 * @brief This function changes the state of the current MusicManager depending on the parameter.
	 * If the parameter is AudioStates::Playing, the audio file, if it exists, will start playing
	 * If the parameter is AudioStates::Paused, the audio file would be paused, but would keep its position
	 * If the parameter is AudioStates::Stopped, the audio file would be stopped and resetted
	 * @param AudioState enum value
	 * @return void
	*/
	static void ChangeMusicState(AudioStates state);
	/**
	 * @brief Sets the Music object to be played
	 *
	 * @param music object const reference
	 * @return a reference to the music
	*/
	static GameSystem::Music &SetMusic(GameSystem::Music music);
	static GameSystem::Music &GetMusic();

  protected:
  static void LengthCallback(void *udata,Uint8 *stream ,int len );
	static void UpdateMusic();

	static void MusicEnded();
	static int m_LoopCounter;
	static int m_CurrentState;
	static double m_CurrentPosition;
	static int m_PlayedBytes;
	static double m_SecondsSinceStart;
	static double m_PreviousSeconds;
	static GameSystem::Music m_Music;


};
};
};
#endif
