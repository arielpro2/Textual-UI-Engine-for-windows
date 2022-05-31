#include "UIElements.h"
namespace UI {
	void UIElement::setColor(std::wstring color)
	{
		this->color = color;
	}

	void UIElement::setVisibility(int visibility)
	{
		this->visibility = visibility;
	}

	int UIElement::getVisibility()
	{
		return visibility;
	}
}



