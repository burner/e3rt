#include <iostream>
#include <math.h>
#include <string>
#include <GL3/gl3.h>
#ifndef VEC3D
#define VEC3D
class vec3d {
	private:
	public:
		GLdouble x;
		GLdouble y;
		GLdouble z;

		vec3d(GLdouble x_n, GLdouble y_n, GLdouble z_n);
		vec3d();

		//addition subtraction
		vec3d* operator+ (const vec3d &second);
		void operator+= (const vec3d &second);
		vec3d* operator- (const vec3d &second);
		void operator-= (const vec3d &second);

		//corssprocut
		vec3d* operator* (const vec3d &second);
		void operator*= (const vec3d &second);

		//scalar multiplcation
		vec3d* operator* (const GLdouble &scalar);
		void operator*= (const GLdouble &scalar);
		GLdouble length();

		std::string* toXML();
};
#endif
