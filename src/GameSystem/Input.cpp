#include "GameSystem/Input.hpp"
#include "Misc/Color.hpp"
#include "Misc/Debug.hpp"
#include "Components/Camera.hpp"
#include "Components/ImageComponent.hpp"
#include "GameSystem/Game.hpp"
#include "GameSystem/Time.hpp"
#include "GameSystem/GameEntity.hpp"
#include "TourneScript.hpp"
using namespace std;
using namespace DreamEngine::GameSystem;
using namespace DreamEngine::Components;
using namespace DreamEngine::Debug;
map<string, Key*> Input::m_KeyDictionnary = map<string, Key*>();
vector<Joystick*> Input::m_Joysticks = vector<Joystick*>();
const Uint8* Input::keyboard_state_array = nullptr;
bool Input::m_firstRun = true;
int Input::m_NumJoysticks = 0;
Mouse Input::m_Mouse = Mouse();
SDL_Event Input::events;
int Input::event_filter(void* unused, SDL_Event* events)
	{
	switch (events->type)
	{
	case SDL_APP_WILLENTERBACKGROUND:
		Log::PrintLine("Entered background");
		break;
	case SDL_APP_TERMINATING:
		Log::PrintLine("Entered terminating phase");
		break;
	case SDL_QUIT:
		Log::PrintLine("Entered quitting phase");
		Game::GameInstance->isRunning = false;
		break;
	}


		return 1;
	}
int Input::INITIALIZEKEYS()
{
	SDL_SetEventFilter(&event_filter, NULL);

	m_KeyDictionnary["A"] = new Key("A", SDL_SCANCODE_A);
	m_KeyDictionnary["B"] = new Key("B", SDL_SCANCODE_B);
	m_KeyDictionnary["C"] = new Key("C", SDL_SCANCODE_C);
	m_KeyDictionnary["D"] = new Key("D", SDL_SCANCODE_D);
	m_KeyDictionnary["E"] = new Key("E", SDL_SCANCODE_E);
	m_KeyDictionnary["F"] = new Key("F", SDL_SCANCODE_F);
	m_KeyDictionnary["G"] = new Key("G", SDL_SCANCODE_G);
	m_KeyDictionnary["H"] = new Key("H", SDL_SCANCODE_H);
	m_KeyDictionnary["I"] = new Key("I", SDL_SCANCODE_I);
	m_KeyDictionnary["J"] = new Key("J", SDL_SCANCODE_J);
	m_KeyDictionnary["K"] = new Key("K", SDL_SCANCODE_K);
	m_KeyDictionnary["L"] = new Key("L", SDL_SCANCODE_L);
	m_KeyDictionnary["M"] = new Key("M", SDL_SCANCODE_M);
	m_KeyDictionnary["N"] = new Key("N", SDL_SCANCODE_N);
	m_KeyDictionnary["O"] = new Key("O", SDL_SCANCODE_O);
	m_KeyDictionnary["P"] = new Key("P", SDL_SCANCODE_P);
	m_KeyDictionnary["Q"] = new Key("Q", SDL_SCANCODE_Q);
	m_KeyDictionnary["R"] = new Key("R", SDL_SCANCODE_R);
	m_KeyDictionnary["S"] = new Key("S", SDL_SCANCODE_S);
	m_KeyDictionnary["T"] = new Key("T", SDL_SCANCODE_T);
	m_KeyDictionnary["U"] = new Key("U", SDL_SCANCODE_U);
	m_KeyDictionnary["V"] = new Key("V", SDL_SCANCODE_V);
	m_KeyDictionnary["W"] = new Key("W", SDL_SCANCODE_W);
	m_KeyDictionnary["X"] = new Key("X", SDL_SCANCODE_X);
	m_KeyDictionnary["Y"] = new Key("Y", SDL_SCANCODE_Y);
	m_KeyDictionnary["Z"] = new Key("Z", SDL_SCANCODE_Z);
	m_KeyDictionnary["Up"] = new Key("Up", SDL_SCANCODE_UP);
	m_KeyDictionnary["Down"] = new Key("Down", SDL_SCANCODE_DOWN);
	m_KeyDictionnary["Left"] = new Key("Left", SDL_SCANCODE_LEFT);
	m_KeyDictionnary["Right"] = new Key("Right", SDL_SCANCODE_RIGHT);
	m_KeyDictionnary["Return"] = new Key("Return", SDL_SCANCODE_RETURN);
	m_KeyDictionnary["Space"] = new Key("Space", SDL_SCANCODE_SPACE);
	m_KeyDictionnary["Left Shift"] = new Key("Left Shift", SDL_SCANCODE_LSHIFT);
	m_KeyDictionnary["Left Ctrl"] = new Key("Left Ctrl", SDL_SCANCODE_LCTRL);
	m_KeyDictionnary["Left Alt"] = new Key("Left Alt", SDL_SCANCODE_LALT);
	m_KeyDictionnary["Tab"] = new Key("Tab", SDL_SCANCODE_TAB);
	m_KeyDictionnary["Right Shift"] = new Key("Right Shift", SDL_SCANCODE_RSHIFT);
	m_KeyDictionnary["Right Ctrl"] = new Key("Right Ctrl", SDL_SCANCODE_RCTRL);
	m_KeyDictionnary["Right Alt"] = new Key("Right Alt", SDL_SCANCODE_RALT);
	m_KeyDictionnary["Escape"] = new Key("Escape", SDL_SCANCODE_ESCAPE);
	m_KeyDictionnary["F1"] = new Key("F1", SDL_SCANCODE_F1);
	m_KeyDictionnary["F2"] = new Key("F2", SDL_SCANCODE_F2);
	m_KeyDictionnary["F3"] = new Key("F3", SDL_SCANCODE_F3);
	m_KeyDictionnary["F4"] = new Key("F4", SDL_SCANCODE_F4);
	m_KeyDictionnary["F5"] = new Key("F5", SDL_SCANCODE_F5);
	m_KeyDictionnary["F6"] = new Key("F6", SDL_SCANCODE_F6);
	m_KeyDictionnary["F7"] = new Key("F7", SDL_SCANCODE_F7);
	m_KeyDictionnary["F8"] = new Key("F8", SDL_SCANCODE_F8);
	m_KeyDictionnary["F9"] = new Key("F9", SDL_SCANCODE_F9);
	m_KeyDictionnary["F10"] = new Key("F10", SDL_SCANCODE_F10);
	m_KeyDictionnary["F11"] = new Key("F11", SDL_SCANCODE_F11);
	m_KeyDictionnary["F12"] = new Key("F12", SDL_SCANCODE_F12);
	UPDATEJOYSTICKS();
	m_firstRun = false;
	return 0;
}
int countline;

void Input::UPDATEJOYSTICKS()
{
	//Get the number of connected joysticks in order to add them to the update list
	int num = SDL_NumJoysticks();
	if (num != m_NumJoysticks)
	{

		m_NumJoysticks = SDL_NumJoysticks();
		if (!m_firstRun)
		{
			for (auto joystick : m_Joysticks)
			{
				delete joystick;

			}
			m_Joysticks.clear();
		}
		for (int i = 0; i < num; i++)
		{
			Debug::Log::PrintLine("Detected joystick");
			m_Joysticks.push_back(new Joystick());
			Joystick *joy = m_Joysticks[i];
			joy->joystick = SDL_JoystickOpen(i);
			joy->name = SDL_JoystickName(joy->joystick);
			Debug::Log::PrintLine("Joystick " + to_string(i) + " name = " + joy->name);
			joy->ID = i;
			int numAxis = SDL_JoystickNumAxes(joy->joystick);
			for (int j = 0; j < numAxis; j++)
			{

				joy->axis.push_back(new Axis());
				Axis *joyaxis = joy->axis[j];
				joyaxis->ID = j;
				SDL_JoystickGetAxisInitialState(joy->joystick, j, &joyaxis->DefaultPosition);
				Debug::Log::PrintLine("Joystick " + joy->name + " axis " + to_string(j) + " found");
			}
			int numButtons = SDL_JoystickNumButtons(joy->joystick);
			for (int k = 0; k < numButtons; k++)
			{
				joy->buttons.push_back(new Button());

				Button *button = joy->buttons[k];
				button->ID = k;
				button->keystate = Released;
			}
			int numHats = SDL_JoystickNumHats(joy->joystick);
			for (int l = 0; l < numHats; l++)
			{
				joy->hats.push_back(new Hat());
				Hat *hat = joy->hats[l];
				hat->ID = l;
				hat->keystate = Released;
				Debug::Log::PrintLine("hat found");
			}

			joy->haptic = SDL_HapticOpenFromJoystick(joy->joystick);
			if (!joy->haptic || SDL_HapticRumbleInit(joy->haptic) != 0)
			{
				Debug::Log::PrintLine("Impossible to initialise Haptic control on this controller, rumble disabled");
			}
			else {
				if (SDL_HapticRumblePlay(joy->haptic, 0.5, 2000) != 0)
				{
				}

			}
			Debug::Log::PrintLine("The controller " + joy->name + " has " + to_string(numButtons) + " buttons " + to_string(numAxis) + " Axes and " + to_string(numHats) + " hats");
		}
	}
	if (num != 0)
	{
		for (auto joystick : m_Joysticks)
		{
			for (auto button : joystick->buttons)
			{

				Uint8 value = SDL_JoystickGetButton(joystick->joystick, button->ID);
				if (value)
				{
					UpdateState(button->keystate, true);
				}
				else
				{
					UpdateState(button->keystate, false);
				}
			}
			for (auto ax : joystick->axis)
			{
				Sint16 value = SDL_JoystickGetAxis(joystick->joystick, ax->ID);
				if (value != 0)
				{
					ax->value = value * 100 / 32768;
					if (ax->value < 15 && ax->value > -15)
					{
						ax->value = 0;
					}
				}
				else {
					ax->value = 0;
				}


			}
			for (auto hat : joystick->hats)
			{
				Uint8 state = SDL_JoystickGetHat(joystick->joystick, hat->ID);
				if (state)
				{
					UpdateState(hat->keystate, true);
				}
				else {
					UpdateState(hat->keystate, false);
				}
			}

		}
	}
}
void Input::UPDATEKEYS()
{
	SDL_Event events;

	while (SDL_PollEvent(&events))
	{
		UPDATEJOYSTICKS();
	}
	UPDATEKEYBOARD();

}

void Input::UPDATEKEYBOARD()
{
	Input::keyboard_state_array = SDL_GetKeyboardState(NULL);
	for (auto key : m_KeyDictionnary)
	{
		SDL_Scancode code = key.second->code;

			if (keyboard_state_array[code])
			{
				UpdateState(key.second->keystate, true);
			}
			else {
				UpdateState(key.second->keystate, false);
			}

	}
	int posx, posy;
	Uint32 state = SDL_GetMouseState(&posx, &posy);
	m_Mouse.position.x = posx;
	m_Mouse.position.y = posy;
	if (state == SDL_BUTTON_LEFT)
	{
		UpdateState(m_Mouse.LeftClick, true);
	}
	else {
		UpdateState(m_Mouse.LeftClick, false);
	}

}
void Input::UpdateState(KeyStates &state, bool pressed)
{
	if (pressed)
	{
		if (state == KeyStates::Down) {
			state = KeyStates::Held;
			//Debug::Log::PrintLine("held");
		}
		else if (state == KeyStates::Released || state == KeyStates::Up)
		{
			state = KeyStates::Down;
			//Debug::Log::PrintLine("justpressed");
		}
	}
	else {
		if (state == 0) {
			state = KeyStates::Released;
		}
		else if (state == KeyStates::Held || state == KeyStates::Down)
		{
			state = KeyStates::Up;
			//	Debug::Log::PrintLine("stopped");
		}
	}

}
float Input::GetAxis(AxisID id)
{
	if (m_NumJoysticks &&  m_Joysticks[0]->axis[id]->value != 0)
	{

			return m_Joysticks[0]->axis[id]->value;

	}
	else {
		return 0;
	}
}
bool Input::GetHat(Hat::direction dir)
{
	return false;
	switch (dir)
	{
	case Hat::direction::Up:
		break;
	case Hat::direction::Right:
		break;
	case Hat::direction::Left:
		break;
	case Hat::direction::Down:
		break;
	}
}
bool Input::GetMouseLeftButton()
{
	return m_Mouse.LeftClick == KeyStates::Down;
}
Position Input::GetCursorPosition()
{
	Position pos;
	pos = m_Mouse.position;
	return pos;
}
bool Input::GetKeyDown(const string &key)
{
	if (m_KeyDictionnary.count(key))
	{
		Key *thekey = m_KeyDictionnary[key];
		if (thekey->keystate == 1)
		{
			//Debug::Log::PrintLine("Le keystate est à 1 pour " + key);
			return true;

		}
	}
	return false;

}
bool Input::GetKeyUp(const string &key)
{
	if (m_KeyDictionnary.count(key))
	{
		Key *thekey = m_KeyDictionnary[key];
		if (thekey->keystate == 0)
		{
			return true;

		}

	}
	return false;
}
bool Input::GetKey(const std::string &key)
{
	if (m_KeyDictionnary.count(key))
	{
		Key *thekey = m_KeyDictionnary[key];

		if (thekey->keystate == 2 || thekey->keystate == 1)
		{
			return true;

		}
	}
	return false;
}
