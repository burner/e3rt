#include "vec2f.h"

vec2f::vec2f(GLfloat x_n, GLfloat y_n) {
	x = x_n;
	y = y_n;
}

vec2f* vec2f::operator+ (const vec2f &second) {
	return new vec2f(x+second.x, y+second.y);
}

void vec2f::operator+= (const vec2f &second) {
	x += second.x;
	y += second.y;
}

vec2f* vec2f::operator- (const vec2f &second) {
	return new vec2f(x-second.x, y-second.y);
}

void vec2f::operator-= (const vec2f &second) {
	x -= second.x;
	y -= second.y;
}

vec2f* vec2f::operator* (const vec2f &second) {
	return new vec2f(0.0,0.0);
}

	
void vec2f::operator*= (const vec2f &second) {
}

vec2f* vec2f::operator* (const GLfloat &scalar) {
	return new vec2f(x*scalar, y*scalar);
}
	
void vec2f::operator*= (const GLfloat &scalar) {
	x*=scalar;
	y*=scalar;
}

GLfloat vec2f::length() {
	return sqrt(pow(x,2) + pow(y,2));
}

std::string* vec2f::toXML() {
	std::string* tmp = new std::string("x=\"");
	tmp->push_back(x);
	tmp->append("\" y=\"");
	tmp->push_back(y);
	tmp->append("\"");
	return tmp;
}
