#pragma once
#include "GUIElement.h"

namespace GUIElements {
	class Button : GUIElement{
	public:
		std::string text;
		void render();
	};
}