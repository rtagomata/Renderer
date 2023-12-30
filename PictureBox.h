#pragma once
#include "GUIElement.h"

namespace GUIElements {
	class PictureBox : GUIElement {
	public:
		std::string picLocation;
	
		PictureBox(std::string picLoc, VECTOR2D pos, GLfloat len, GLfloat wid) :
			picLocation(picLoc), GUIElement(pos, len, wid){}
		void render() {
			glBegin(GL_QUADS);
			glVertex3f(position.x, position.y, 0.0);
			glVertex3f(position.x + width, position.y, 0.0);
			glVertex3f(position.x+width, position.y+length, 0.0);
			glVertex3f(position.x, position.y+length, 0.0);
			glEnd();
		}
	};
}