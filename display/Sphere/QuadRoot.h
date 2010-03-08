#include "Quad.h"

#ifndef QUADROOT
#define QUADROOT
class QuadRoot {
	private:
		unsigned maxDepth;
		unsigned maxHeightMapDepth;
		Quad *root;

	public:
		unsigned getMaxDepth();
		unsigned getHeightMapDepth();
		QuadRoot(unsigned mxDpth_in, unsigned mxHghtMpDpth_in, double scale, unsigned seed);
		void render();
};
#endif
