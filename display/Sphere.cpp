#include "Sphere.h"

void Sphere::makeSphere(float radius) {

}

Sphere::Sphere() {
	k = 6;
	double step = 2.0/(k-1);
	double n = -1.0;
	double m = -1.0;
	double o = 1.0;
	
	Fr = new vec3f** [k];
	Ba = new vec3f** [k];
	Ri = new vec3f** [k];
	Le = new vec3f** [k];
	To = new vec3f** [k];
	Bo = new vec3f** [k];
		
	for(unsigned i = 0; i < k; i++) {
		Fr[i] = new vec3f* [k];
		Ba[i] = new vec3f* [k];
		Ri[i] = new vec3f* [k];
		Le[i] = new vec3f* [k];
		To[i] = new vec3f* [k];
		Bo[i] = new vec3f* [k];

		for(unsigned j = 0; j < k; j++) {
			Fr[i][j] = new vec3f(n,m,o);
			Ba[i][j] = new vec3f(n,m,-o);
			Ri[i][j] = new vec3f(o,m,n);
			Le[i][j] = new vec3f(-o,m,n);
			To[i][j] = new vec3f(n,o,m);
			Bo[i][j] = new vec3f(n,-o,m);
			n+=step;
		}
		m+=step;
	}
}
