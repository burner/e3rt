#include <iostream>
#include <math.h>
#include <string>
#include <GL3/gl3.h>
#ifndef VEC3F
#define VEC3F
class vec3f {
	private:
	public:
		GLfloat x;
		GLfloat y;
		GLfloat z;

		vec3f(GLfloat x_n, GLfloat y_n, GLfloat z_n);

		//addition subtraction
		vec3f* operator+ (const vec3f &second);
		void operator+= (const vec3f &second);
		vec3f* operator- (const vec3f &second);
		void operator-= (const vec3f &second);

		//corssprocut
		vec3f* operator* (const vec3f &second);
		void operator*= (const vec3f &second);

		//scalar multiplcation
		vec3f* operator* (const float &scalar);
		void operator*= (const float &scalar);
		float length();

		std::string* toXML();
};
#endif
