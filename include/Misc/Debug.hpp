#ifndef DEBUG_HPP
#define DEBUG_HPP
#include <fstream>
#include <string>
#ifdef _DEBUG
#define PrintError(x) (::DreamEngine::Debug::Log::PrintLine(string(__FILE__) + " in " + string(__func__) + " line " + to_string(__LINE__) + " " + string(x)))
#else
#define PrintError(x) (::DreamEngine::Debug::Log::PrintLine(x))
#endif
namespace DreamEngine
{
namespace GameSystem
{
class Game;
};
namespace Debug
{
class Log
{
	friend class GameSystem::Game;

  public:
	static void PrintLine(const std::string &log);

  private:
  /**
   * Creates a log file stream in order to write to this file
   */ 
	static int StartDebugging();
	static int StopDebugging();
	static int m_Line;
	static std::ofstream m_Output;
};
class Error
{
  public:
	/**
 * Displays an error pop-up
 * */
	static void DisplayError(const std::string &name, const std::string &message);

	/**
	 *Displays an error popup, then closes the game 
	 */
	static void DisplayFatalError(const std::string &name, const std::string &message);
};
}; // namespace Debug
}; // namespace DreamEngine
#endif