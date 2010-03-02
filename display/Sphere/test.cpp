#include "Noise.h"
#include <iostream>
#include <SDL/SDL.h>

void putPixelB(SDL_Surface* sur, int x, int y, double al) {
	unsigned *pixel = (unsigned*)sur->pixels;
	//std::cout<<"x "<<x<<" y "<<y<<" "<<al*255<<std::endl;
	//std::cout<<"sur->h "<<sur->h<<" sur->w "<<sur->w<<std::endl;
	unsigned a = 0;
	//unsigned a = 255<<24;
	//a += 255<<16;
	//a+=255<<8;
	if(al > 0.0) {
		a+=(unsigned)(pow(2,12) * al);
	} else {
		a+=(unsigned)(pow(2,12)* (-al));
	}
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
	for(int i = 0; i < x; i++) {
		for(int j = 0; j < y; j++) {
			//double w = fbm(i*steps,j*steps, 0.0, 15);
			//double w = turbulence(i*steps,j*steps, 0.0, 5);
			double w = noise(i*steps,j*steps, 0.0);
			//double w = snoise(0.0000001+(1.0/(i+1)), 0.0+(1.0/(j+1)),0.0);
			//std::cout<<"w "<<w<<" i "<<i*steps<<" j "<<j*steps<<std::endl;
			putPixelB(hello, i, j, w);
		}
	}
	SDL_Flip(hello);
	SDL_Delay(5000);
}	
