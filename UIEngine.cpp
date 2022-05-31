#include "UIEngine.h"

namespace UI {
	UIEngine::UIEngine(UI::Screen* screen) {
		//Constructing a new screen
		this->screen = screen;
	}

	UI::UIFrame* UIEngine::Frame(int x1, int y1, int x2, int y2) {
		//Appending new frame element
		UI::UIFrame* Frame = new UI::UIFrame(x1, y1, x2, y2);
		UIElements.push_back(Frame);
		return Frame;

	}
	UI::UILabel* UIEngine::Label(int x, int y, std::wstring text) {
		//Appending new Label element
		UI::UILabel* Label = new UI::UILabel(x, y, text);
		UIElements.push_back(Label);
		return Label;

	}

	UI::UITextBox* UIEngine::TextBox(int x, int y)
	{
		//Appending new TextBox element
		UI::UITextBox* TextBox = new UI::UITextBox(x, y);
		UIElements.push_back(TextBox);
		return TextBox;
	}

	std::string UIEngine::getInput()
	{
		return screen->getInput();
	}

	void UIEngine::removeElement(UI::UIElement* element)
	{
		UIElements.erase(std::remove(UIElements.begin(), UIElements.end(), element), UIElements.end());
	}

	void UIEngine::removeAll()
	{
		UIElements.clear();
	}


	tuple<int, int> UIEngine::getScreenSize()
	{
		return screen->getScreenSize();
	}

	void UIEngine::drawElements() {
		//Sort elements by visibility
		std::sort(UIElements.begin(), UIElements.end(), byVisibility());
		for (int i = 0; i < UIElements.size(); i++)
		{
			//If visibility is 0, dont draw
			if (UIElements[i]->getVisibility())
				UIElements[i]->Draw(screen);
		}
		//Calling the screen to update
		screen->Update();
	}
}



