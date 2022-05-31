#pragma once
#include "Screen.h"
#include "UIElements.h"
#include <vector>
#include <algorithm>

using namespace std;
//sorting function to sort by visibility of an element
namespace UI {
	struct byVisibility {
		bool operator()(UI::UIElement* a, UI::UIElement* b) {
			return a->getVisibility() < b->getVisibility();
		}
	};
	class UIEngine {
	public:
		UIEngine(UI::Screen*);
		tuple<int, int> getScreenSize();
		//Add new frame element
		UI::UIFrame* Frame(int, int, int, int);
		UI::UILabel* Label(int, int, std::wstring);
		UI::UITextBox* TextBox(int, int);
		std::string getInput();
		void removeElement(UI::UIElement*);
		void removeAll();
		//draw all elements
		void drawElements();
	private:
		//Element pointer array
		std::vector <UI::UIElement*> UIElements;
		//Screen handler pointer
		UI::Screen* screen;

	};
}
