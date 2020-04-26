
#ifndef TEXTCOMPONENT_HPP
#define TEXTCOMPONENT_HPP
#include "GlobalHeader.hpp"
#include "GameSystem/Scene.hpp"
#include "Components/UIComponent.hpp"
#include "Misc/Color.hpp"
namespace DreamEngine {
	namespace Components {
		class TextComponent : public UIComponent
		{
		public:
			TextComponent();
			~TextComponent();
			int LoadFontFromDirectory(const std::string &path);
			const std::string &GetFont() const;
			void SetSize(int size);
			int GetSize() const;
			void SetText(const std::string &text);
			const std::string &GetText() const;
			void UpdateText();
			void Launch();
		protected:
			double minutes = 0, seconds = 0, milliseconds = 0;
			void Update();
			void Render();
			int m_Size;
			SDL_Color m_Color;
			int sizeW, sizeH;
			int framecount;
			char *buffer = nullptr;
			std::string PreviousText;
			std::string m_Text;
			std::string m_FontPath;
			TTF_Font *m_Font = nullptr;
			SDL_Surface *m_Texture = nullptr;
		};
	};
};
#endif
