#include "vec3d.h"

vec3d::vec3d(GLdouble x_n, GLdouble y_n, GLdouble z_n) {
	x = x_n;
	y = y_n;
	z = z_n;
}

vec3d::vec3d() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

vec3d* vec3d::operator+ (const vec3d &second) {
	return new vec3d(x+second.x, y+second.y, z+second.z);
}

void vec3d::operator+= (const vec3d &second) {
	x += second.x;
	y += second.y;
	z += second.z;
}

vec3d* vec3d::operator- (const vec3d &second) {
	return new vec3d(x-second.x, y-second.y, z-second.z);
}

void vec3d::operator-= (const vec3d &second) {
	x -= second.x;
	y -= second.y;
	z -= second.z;
}

vec3d* vec3d::operator* (const vec3d &second) {
	return new vec3d( (y * second.z)-(z * second.y),
					(z * second.x)-(x * second.z),
					(x * second.y)-(y * second.x));
}

	
void vec3d::operator*= (const vec3d &second) {
	GLdouble tx = (y * second.z)-(z * second.y);
	GLdouble ty = (z * second.x)-(x * second.z);
	GLdouble tz = (x * second.y)-(y * second.x);
	x = tx; y = ty; z = tz;
}

vec3d* vec3d::operator* (const GLdouble &scalar) {
	return new vec3d(x*scalar, y*scalar, z*scalar);
}
	
void vec3d::operator*= (const GLdouble &scalar) {
	x*=scalar;
	y*=scalar;
	z*=scalar;
}

GLdouble vec3d::length() {
	return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
}

std::string* vec3d::toXML() {
	std::string* tmp = new std::string("x=\"");
	tmp->push_back(x);
	tmp->append("\" y=\"");
	tmp->push_back(y);
	tmp->append("\" z=\"");
	tmp->push_back(z);
	tmp->append("\"");
	return tmp;
}
