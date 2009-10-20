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
	
	//create verticies	
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

	//create vbo data
	frData = new GLfloat[(k-1)*(k-1)*2*9]; frColor = new GLfloat[(k-1)*(k-1)*2*9];
	baData = new GLfloat[(k-1)*(k-1)*2*9]; baColor = new GLfloat[(k-1)*(k-1)*2*9];
	leData = new GLfloat[(k-1)*(k-1)*2*9]; leColor = new GLfloat[(k-1)*(k-1)*2*9];
	riData = new GLfloat[(k-1)*(k-1)*2*9]; riColor = new GLfloat[(k-1)*(k-1)*2*9];
	toData = new GLfloat[(k-1)*(k-1)*2*9]; toColor = new GLfloat[(k-1)*(k-1)*2*9];
	boData = new GLfloat[(k-1)*(k-1)*2*9]; boColor = new GLfloat[(k-1)*(k-1)*2*9];
	unsigned h = 0;
	for(unsigned i = 0; i < (k-1); i++) {
		for(unsigned j = 0; j < (k-1); j++) {
			//first TRI first VEC Pos
			frData[h] = Fr[i][j]->x; baData[h] = Ba[i][j]->x; leData[h] = Le[i][j]->x;
			riData[h] = Ri[i][j]->x; toData[h] = To[i][j]->x; boData[h] = Bo[i][j]->x;
			frColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); baColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			leColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); riColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			toColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); boColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			h++;
			frData[h] = Fr[i][j]->y; baData[h] = Ba[i][j]->y; leData[h] = Le[i][j]->y;
			riData[h] = Ri[i][j]->y; toData[h] = To[i][j]->y; boData[h] = Bo[i][j]->y;
			frColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); baColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			leColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); riColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			toColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); boColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			h++;
			frData[h] = Fr[i][j]->z; baData[h] = Ba[i][j]->z; leData[h] = Le[i][j]->z;
			riData[h] = Ri[i][j]->z; toData[h] = To[i][j]->z; boData[h] = Bo[i][j]->z;
			frColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); baColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			leColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); riColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			toColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); boColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			h++;
			//first TRI second VEC Pos
			frData[h] = Fr[i+1][j]->x; baData[h] = Ba[i+1][j]->x; leData[h] = Le[i+1][j]->x;
			riData[h] = Ri[i+1][j]->x; toData[h] = To[i+1][j]->x; boData[h] = Bo[i+1][j]->x;
			frColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); baColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			leColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); riColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			toColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); boColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			h++;
			frData[h] = Fr[i+1][j]->y; baData[h] = Ba[i+1][j]->y; leData[h] = Le[i+1][j]->y;
			riData[h] = Ri[i+1][j]->y; toData[h] = To[i+1][j]->y; boData[h] = Bo[i+1][j]->y;
			frColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); baColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			leColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); riColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			toColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); boColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			h++;
			frData[h] = Fr[i+1][j]->z; baData[h] = Ba[i+1][j]->z; leData[h] = Le[i+1][j]->z;
			riData[h] = Ri[i+1][j]->z; toData[h] = To[i+1][j]->z; boData[h] = Bo[i+1][j]->z;
			frColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); baColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			leColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); riColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			toColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); boColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			h++;
			//first TRI third VEC Pos
			frData[h] = Fr[i][j+1]->x; baData[h] = Ba[i][j+1]->x; leData[h] = Le[i][j+1]->x;
			riData[h] = Ri[i][j+1]->x; toData[h] = To[i][j+1]->x; boData[h] = Bo[i][j+1]->x;
			frColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); baColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			leColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); riColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			toColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); boColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			h++;
			frData[h] = Fr[i][j+1]->y; baData[h] = Ba[i][j+1]->y; leData[h] = Le[i][j+1]->y;
			riData[h] = Ri[i][j+1]->y; toData[h] = To[i][j+1]->y; boData[h] = Bo[i][j+1]->y;
			frColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); baColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			leColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); riColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			toColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); boColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			h++;
			frData[h] = Fr[i][j+1]->z; baData[h] = Ba[i][j+1]->z; leData[h] = Le[i][j+1]->z;
			riData[h] = Ri[i][j+1]->z; toData[h] = To[i][j+1]->z; boData[h] = Bo[i][j+1]->z;
			frColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); baColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			leColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); riColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			toColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); boColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			h++;
			//second TRI first VEC Pos
			frData[h] = Fr[i+1][j]->x; baData[h] = Ba[i+1][j]->x; leData[h] = Le[i+1][j]->x;
			riData[h] = Ri[i+1][j]->x; toData[h] = To[i+1][j]->x; boData[h] = Bo[i+1][j]->x;
			frColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); baColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			leColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); riColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			toColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); boColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			h++;
			frData[h] = Fr[i+1][j]->y; baData[h] = Ba[i+1][j]->y; leData[h] = Le[i+1][j]->y;
			riData[h] = Ri[i+1][j]->y; toData[h] = To[i+1][j]->y; boData[h] = Bo[i+1][j]->y;
			frColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); baColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			leColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); riColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			toColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); boColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			h++;
			frData[h] = Fr[i+1][j]->z; baData[h] = Ba[i+1][j]->z; leData[h] = Le[i+1][j]->z;
			riData[h] = Ri[i+1][j]->z; toData[h] = To[i+1][j]->z; boData[h] = Bo[i+1][j]->z;
			frColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); baColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			leColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); riColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			toColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); boColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			h++;
			//second TRI second VEC Pos
			frData[h] = Fr[i+1][j+1]->x; baData[h] = Ba[i+1][j+1]->x; leData[h] = Le[i+1][j+1]->x;
			riData[h] = Ri[i+1][j+1]->x; toData[h] = To[i+1][j+1]->x; boData[h] = Bo[i+1][j+1]->x;
			frColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); baColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			leColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); riColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			toColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); boColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			h++;
			frData[h] = Fr[i+1][j+1]->y; baData[h] = Ba[i+1][j+1]->y; leData[h] = Le[i+1][j+1]->y;
			riData[h] = Ri[i+1][j+1]->y; toData[h] = To[i+1][j+1]->y; boData[h] = Bo[i+1][j+1]->y;
			frColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); baColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			leColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); riColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			toColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); boColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			h++;
			frData[h] = Fr[i+1][j+1]->z; baData[h] = Ba[i+1][j+1]->z; leData[h] = Le[i+1][j+1]->z;
			riData[h] = Ri[i+1][j+1]->z; toData[h] = To[i+1][j+1]->z; boData[h] = Bo[i+1][j+1]->z;
			frColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); baColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			leColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); riColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			toColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); boColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			h++;
			//second TRI third VEC Pos
			frData[h] = Fr[i][j+1]->x; baData[h] = Ba[i][j+1]->x; leData[h] = Le[i][j+1]->x;
			riData[h] = Ri[i][j+1]->x; toData[h] = To[i][j+1]->x; boData[h] = Bo[i][j+1]->x;
			frColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); baColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			leColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); riColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			toColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); boColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			h++;
			frData[h] = Fr[i][j+1]->y; baData[h] = Ba[i][j+1]->y; leData[h] = Le[i][j+1]->y;
			riData[h] = Ri[i][j+1]->y; toData[h] = To[i][j+1]->y; boData[h] = Bo[i][j+1]->y;
			frColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); baColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			leColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); riColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			toColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); boColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			h++;
			frData[h] = Fr[i][j+1]->z; baData[h] = Ba[i][j+1]->z; leData[h] = Le[i][j+1]->z;
			riData[h] = Ri[i][j+1]->z; toData[h] = To[i][j+1]->z; boData[h] = Bo[i][j+1]->z;
			frColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); baColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			leColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); riColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			toColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1)); boColor[h] = (GLfloat)((rand()/float(RAND_MAX)+1));
			h++;
		}
	}	
}
