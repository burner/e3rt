#include <vector>
#include "../../prim/vec3d.h"
#include "QuadRoot.h"

#ifndef QUAD
#define QUAD
class Quad {
	private:
		Quad *parent;
		QuadRoot *quadRoot;
		unsigned depth;
		std::vector<Quad*> *childs;
		vec3d *tr, *tl, *br, *bl;

	public:
		unsigned id;
		Quad(Quad *parent_in, QuadRoot *qr_in, unsigned id_in, unsigned depth_in, vec3d *tr_in, vec3d *tl_in, vec3d *br_in, vec3d *bl_in);
		void subdived();
		void render();
		bool childsCreated;
};
#endif
