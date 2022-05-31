#include "UIElements.h"
namespace UI {
	UITextBox::UITextBox(int x, int y) {
		this->x = x;
		this->y = y;
	}

	void UITextBox::setPosition(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void UITextBox::Draw(UI::Screen* screen) {
		screen->setInput(x, y);
	}
}