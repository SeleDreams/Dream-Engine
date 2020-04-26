
#include "GlobalHeader.hpp"
#include <Windows.h>
#include "GameSystem/Game.hpp"
#include "Misc/Debug.hpp"
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace DreamEngine::Debug;
using namespace DreamEngine::GameSystem;
using namespace std;
//using  namespace Windows::Storage;
ofstream Log::m_Output = ofstream();

int Log::StartDebugging()
{

	//time_t time(0);
	//time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	//tm *now;
	//now = localtime(&time);

	/*stringstream ss;
	ss << "Log (" << now->tm_mday << "-" << (now->tm_mon + 1) << "-" << (now->tm_year + 1900) << ")"
	   << ".txt";
	string filename = ss.str();
	m_Output = ofstream(Game::GetCacheFile(filename), ios::app | ios::out);

	if (m_Output.fail())
	{
		return EXIT_FAILURE;
	}*/
	return EXIT_SUCCESS;
}
int Log::StopDebugging()
{
	m_Output.flush();
	m_Output.close();
	return EXIT_SUCCESS;
}
void Log::PrintLine(const string &log)
{
#ifdef WINAPI_FAMILY_SYSTEM

	OutputDebugStringA((log + "\n").c_str());
#else
	cout << log.c_str() << endl;
#endif
	if (m_Output)
	{
		m_Output << log.c_str() << endl;
	}
}

void Error::DisplayError(const string &name, const string &message)
{
	Log::PrintLine(message);

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, name.c_str(), message.c_str(), Game::GameInstance->GetGameWindow());
}
void Error::DisplayFatalError(const string &name, const string &message)
{
	DisplayError(name,message);
	abort();
}
