#include "Components/TextComponent.hpp"
#include "GameSystem/FileSystem.hpp"
#include "GameSystem/Time.hpp"
#include "Misc/Debug.hpp"
#include <cmath>
#include <iomanip>
#include <sstream>
using namespace std;
using namespace DreamEngine::Components;
using namespace DreamEngine::GameSystem;

TextComponent::TextComponent() : UIComponent(typeid(this).name()), sizeW(0), sizeH(0), framecount(0), PreviousText("")
{
}

TextComponent::~TextComponent()
{
	if (m_Font)
	{
		TTF_CloseFont(m_Font);
	}
	if (m_Texture)
	{
		SDL_FreeSurface(m_Texture);
		m_Texture = nullptr;
	}
	if (buffer)
	{
		delete buffer;
	}
}
void TextComponent::Launch()
{
}
const string &TextComponent::GetFont() const
{
	return m_FontPath;
}
const string &TextComponent::GetText() const
{
	return m_Text;
}
void TextComponent::SetSize(int size)
{
	m_Size = size;
}
int TextComponent::GetSize() const
{
	return m_Size;
}
void TextComponent::Render()
{
	if (isActive() && m_Texture)
	{
		//  cout << GetGameEntity()->GetName().c_str() << " rendered " << endl;
  SDL_BlitSurface(m_Texture,nullptr,Game::GetGlobalSurface(),&m_TextRect);
	}
}

void TextComponent::Update()
{
	/*milliseconds += Time::GetDeltaTime();
	if (milliseconds >= 10)
	{
		seconds += 1;
		milliseconds = 0;
		if (seconds >= 60)
		{
			minutes += 1;
			seconds = 0;
		}
	}
	ostringstream oss;

	oss << setfill('0') << setw(2) << minutes << ":" << setfill('0') << setw(2) << seconds << ":" << setfill('0') << setw(2) << (int)milliseconds << flush;
	SetText(oss.str());
	UpdateText();
	// SetText("test");*/
}
void TextComponent::UpdateText()
{
	if (m_Text != "")
	{
		m_TextRect.x = GetGameEntity()->transform.position.x;
		m_TextRect.y = GetGameEntity()->transform.position.y;
		if (PreviousText != m_Text)
		{
			LoadFontFromDirectory(m_FontPath);
			if (m_Texture)
			{
				SDL_FreeSurface(m_Texture);
				m_Texture = nullptr;
			}
			m_Text.c_str();
			if (m_Font)
			{

				m_TextRect.w *= GetGameEntity()->transform.scale.w;
				m_TextRect.h *= GetGameEntity()->transform.scale.h;
			m_Texture = TTF_RenderUTF8_Solid(m_Font, m_Text.c_str(), m_Color);


				TTF_CloseFont(m_Font);
				m_Font = nullptr;
			}
			if (buffer)
			{
				delete[] buffer;
				buffer = nullptr;
			}
			PreviousText = m_Text;
		}
	}
}
void TextComponent::SetText(const std::string &text)
{
	PreviousText = m_Text;
	m_Text = text;
}

int TextComponent::LoadFontFromDirectory(const std::string &path)
{
	if (m_Size > 3)
	{
		if (m_Font)
		{
			TTF_CloseFont(m_Font);
			delete buffer;
			buffer = nullptr;
			m_Font = nullptr;
		}
		Sint64 size;
		if (FileSystem::GetBytesFromFile(path, buffer, size) == EXIT_SUCCESS)
		{
			//Get the font from the file in memory
			SDL_RWops *rw = SDL_RWFromConstMem(buffer, size);

			m_Font = TTF_OpenFontRW(rw, 0, m_Size);
			m_FontPath = string(path);
		}
		else
		{
			Debug::Log::PrintLine(string("An error occured while loading the font ") + path);
		}

	}
	return EXIT_FAILURE;
}
