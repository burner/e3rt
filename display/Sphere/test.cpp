#include "Noise.h"
#include <iostream>
#include <SDL/SDL.h>

void putPixelB(SDL_Surface* sur, int x, int y, double al) {
	unsigned *pixel = (unsigned*)sur->pixels;
	unsigned a = (unsigned)(1024.0*al*128);
	//std::cout<<a<<std::endl;
	pixel[(y*sur->h)+x] = a;
}

int main() {
	std::cout<<"foo\n";
	SDL_Surface* hello = NULL;
	SDL_Init(SDL_INIT_EVERYTHING);
	int x = 512;
	int y = 512;
	hello = SDL_SetVideoMode(x,y,32,SDL_SWSURFACE);
	double steps = 1.0 / x;
	initPerlin();
	//std::ofstream myfile;
	//myfile.open("c++");
	//std::cout.precision(10);
	for(int i = 0; i < x; i++) {
		for(int j = 0; j < y; j++) {
			double w = fbm(i*steps,j*steps, 0.0, 15, 4.3, 0.7);
			//double w = turbulence(i*steps,j*steps, 0.0, 15, 4.2, 0.7);
			//double w = noise(i*steps,j*steps, 0.0);
			//double w = snoise(i*steps, j*steps,0.0);
			//double w = RidgedMF(i*steps, j*steps, 0.0, 5, 2.3, 1.7, 1.6);
			//std::cout<<w<<std::endl;
			//std::cout<<"w "<<w<<" i "<<i*steps<<" j "<<j*steps<<std::endl;
			putPixelB(hello, i, j, w);
		}
	}
	//myfile.close();
	SDL_Flip(hello);
	SDL_Delay(3000);
}	
