#include "Quad.h"

Quad::Quad(Quad *parent_in, QuadRoot *qr_in, unsigned id_in, unsigned depth_in, vec3d *tr_in, vec3d *tl_in, vec3d *br_in, vec3d *bl_in) {
	parent = parent_in;
	quadRoot = qr_in;
	depth = depth_in;
	id = id_in;
	childsCreated = false;
	tr = tr_in;
	tl = tl_in;
	br = br_in;
	bl = bl_in;
}

void Quad::subdived() {

	//last thing is to make node that the Quad
	//is subdivided
	childsCreated = true;
}

void Quad::render() {
	if(childsCreated) {
		std::vector<Quad*>::iterator it;
		for(it = childs->begin(); it != childs->end(); it++) {
			(*it)->render();
		}
	} else {
	}	
}
