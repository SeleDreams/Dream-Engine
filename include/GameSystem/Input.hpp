#ifndef INPUT_HPP
#define INPUT_HPP
#include "GlobalHeader.hpp"
#include "Position.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
namespace DreamEngine
{
	namespace GameSystem
	{
		enum AxisID {
			LHorizontal = 0,LVertical = 1,RHorizontal = 2,RVertical = 3
		};
		enum ButtonID {
			A,B,X,Y,LB,RB,Back,Start,L3,R3
		};
		enum KeyStates {
			Down = 1, Held = 2, Up = 0, Released = -1
		};
		class Key {
			friend class Input;
			Key(const std::string &n, const SDL_Scancode &codearg) : name(n), code(codearg) {};
			KeyStates keystate = KeyStates::Released;
			std::string name;
			SDL_Scancode code;
		};
		class Mouse
		{
			friend class Input;
			Position position;
			KeyStates LeftClick = KeyStates::Released;
			//KeyStates RightClick = KeyStates::Released;
		};
		class Button {
			friend class Input;
			int ID;
			std::string name;
			KeyStates keystate = KeyStates::Released;
		};
		class Axis {
			friend class Input;
			int ID;
			std::string name;
			float value;
			Sint16 DefaultPosition;

		};
		class Hat {
			friend class Input;
			int ID;
			KeyStates keystate = KeyStates::Released;
			enum direction {
				Up,Down,Left,Right
			};
		};
		class Joystick {
			friend class Input;
			std::string name;
			int ID;
			std::vector<Button*> buttons;
			std::vector<Axis*> axis;
			std::vector<Hat*> hats;
			SDL_Haptic *haptic;
			SDL_Joystick *joystick;
			~Joystick()
			{
				for (auto button : buttons)
				{
					delete button;
				}
				for (auto ax : axis)
				{
					delete ax;
				}
				for (auto ht : hats)
				{
					delete ht;
				}
				SDL_HapticClose(haptic);
				SDL_JoystickClose(joystick);
				
			}

		};
		class Input {
			friend class Game;
		public:

			static bool GetKeyDown(const std::string &key);
			static bool GetKeyUp(const std::string &key);
			static bool GetKey(const std::string &key);
			static bool GetMouseLeftButton();
			static bool GetHat(Hat::direction dir);
			static float GetAxis(AxisID id);
			static Position GetCursorPosition();
		private:
			static int event_filter(void* unused, SDL_Event* events);
			static std::map<std::string, Key*> m_KeyDictionnary;
			static Mouse m_Mouse;
			static int m_NumJoysticks;
			static bool m_firstRun;
			static std::vector<Joystick*> m_Joysticks;
			static void UPDATEJOYSTICKS();
			static int INITIALIZEKEYS();
			static void UPDATEKEYS();
			static void UpdateState(KeyStates &state, bool pressed = true);
			static void UPDATEKEYBOARD();
			static const Uint8* keyboard_state_array;
			static SDL_Event events;
		};
	};
};
#endif