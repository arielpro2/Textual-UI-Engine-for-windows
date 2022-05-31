#include "UIElements.h"

namespace UI {
	UIFrame::UIFrame(int x1, int y1, int x2, int y2)
	{
		//Setting the pos of the frame
		setVisibility(1);
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}

	void UIFrame::setPosition(int x1, int y1, int x2, int xy2)
	{
		this->x1 = x1;
		this->x2 = x2;
		this->y1 = y1;
		this->y2 = y2;
	}


	void UIFrame::Draw(UI::Screen* screen) {
		//Using box ascii char to create the frame
		screen->drawChar(x1, y1, color + L"╭" + Reset);
		screen->drawChar(x2, y1, color + L"╮" + Reset);
		screen->drawChar(x1, y2, color + L"╰" + Reset);
		screen->drawChar(x2, y2, color + L"╯" + Reset);
		for (int i = x1 + 1; i < x2; i++)
		{
			screen->drawChar(i, y1, color + L"―" + Reset);
			screen->drawChar(i, y2, color + L"―" + Reset);
		}
		for (int i = y1 + 1; i < y2; i++)
		{
			screen->drawChar(x1, i, color + L"|" + Reset);
			screen->drawChar(x2, i, color + L"|" + Reset);
		}
	}

}
