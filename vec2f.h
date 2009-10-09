#include <iostream>
#include <math.h>
#include <string>
#include <GL3/gl3.h>
#ifndef VEC2F
#define VEC2F
class vec2f {
	private:
	public:
		GLfloat x;
		GLfloat y;

		vec2f(GLfloat x_n, GLfloat y_n);

		//addition subtraction
		vec2f* operator+ (const vec2f &second);
		void operator+= (const vec2f &second);
		vec2f* operator- (const vec2f &second);
		void operator-= (const vec2f &second);

		//corssprocut
		vec2f* operator* (const vec2f &second);
		void operator*= (const vec2f &second);

		//scalar multiplcation
		vec2f* operator* (const float &scalar);
		void operator*= (const float &scalar);
		float length();

		std::string* toXML();
};
#endif
