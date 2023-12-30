#pragma once
#include <string>

struct VECTOR2D {
	GLfloat x;
	GLfloat y;
};

namespace GUIElements{
	class GUIElement {
	public:
		VECTOR2D position;
		GLfloat length;
		GLfloat width;
		virtual void render() = 0;
	
		GUIElement(VECTOR2D pos, GLfloat len, GLfloat wid) :
			position(pos), length(len), width(wid) {}
	};
}