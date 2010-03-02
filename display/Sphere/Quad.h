#include <vector>
#include "../../prim/vec3d.h"

#ifndef QUAD
#define QUAD
class Quad {
	private:
		std::vector<Quad> childs;
		vec3d *tr, *tl, *br, *bl;
		bool childs;

	public: 	
		void subdived();
		void render();
};
#endif
