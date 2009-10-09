#include "vec3f.h"
#include <string>
#ifndef TRI
#define TRI
class tri {
	public:
		tri(int x1o, int x2o, int x3o,
			int y1o, int y2o, int y3o,
			int z1o, int z2o, int z3o);
		int x1, x2, x3;
		int y1, y2, y3;
		int z1, z2, z3;
};
#endif
