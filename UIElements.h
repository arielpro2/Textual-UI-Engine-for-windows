#pragma once
#include "Screen.h"
#define Hidden 0
#define Visible 1
namespace UI {
	class UIElement {
	public:
		virtual void Draw(UI::Screen*) = 0;
		void setColor(std::wstring);
		void setVisibility(int);
		int getVisibility();
	protected:
		std::wstring color;
	private:
		int visibility;

	};

	class UIFrame : public UIElement {
	public:
		UIFrame(int, int, int, int);
		void setPosition(int, int, int, int);
		void Draw(UI::Screen*);
		int x1, x2, y1, y2;
	};

	class UILabel : public UIElement {
	public:
		UILabel(int, int, std::wstring);
		void setPosition(int, int);
		void setText(std::wstring);
		void Draw(UI::Screen*);
		int x, y;
		std::wstring text;
	};

	class UITextBox : public UIElement {
	public:
		UITextBox(int, int);
		void setPosition(int, int);
		void Draw(UI::Screen*);
		int x, y;
	};
}
