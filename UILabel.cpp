#include "UIElements.h"

namespace UI {
	UILabel::UILabel(int x, int y, std::wstring text)
	{
		setVisibility(1);
		this->x = x;
		this->y = y;
		this->text = text;
	}

	void UILabel::setPosition(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void UILabel::setText(std::wstring text)
	{
		this->text = text;
	}

	void UILabel::Draw(UI::Screen* screen)
	{
		//printing the string by individual character
		int linecount = 0;
		int spacecount = 0;
		for (int i = 0; i < text.size(); i++)
		{
			if (text[i] == L'\n')
			{
				linecount++;
				spacecount = 0;
				continue;
			}
			screen->drawChar(x + spacecount, y + linecount, color + text[i] + Reset);
			spacecount += 1;
		}

	}
}
