#include "Obj.h"
#include <cstdlib>
#ifndef SPHERE
#define SPHERE
class Sphere : Obj {
	private:
		unsigned k;
		GLfloat *frData, *frColor;
		GLfloat *baData, *baColor;
		GLfloat *leData, *leColor;
		GLfloat *riData, *riColor;
		GLfloat *toData, *toColor;
		GLfloat *boData, *boColor;
		
		vec3f ***Fr, ***Ba, ***Ri, ***Le, ***To, ***Bo;
		void makeSphere(float radius);
	public:
		Sphere();
		void draw(GLfloat *projection);
		void writeVert();
};
#endif
