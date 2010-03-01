#include "Noise.h"
#include <iostream>
#include <SDL/SDL.h>

void putPixelB(SDL_Surface* sur, int x, int y, double al) {
	unsigned *pixel = (unsigned*)sur->pixels;
	//std::cout<<"x "<<x<<" y "<<y<<" "<<al*255<<std::endl;
	//std::cout<<"sur->h "<<sur->h<<" sur->w "<<sur->w<<std::endl;
	pixel[(y*sur->h)+x] = (unsigned)(al*255);
}

int main() {
	std::cout<<"foo";
	SDL_Surface* hello = NULL;
	SDL_Init(SDL_INIT_EVERYTHING);
	int x = 255;
	int y = 255;
	hello = SDL_SetVideoMode(x,y,32,SDL_SWSURFACE);
	for(int i = 0; i < x; i++) {
		for(int j = 0; j < y; j++) {
			//double w = fbm(1.0-(1.0/i), 1.0-(1.0/j), 0.0, 6);
			double w = snoise(1.0000001-(1.0/i), 1.0-(1.0/j),0.0);
			std::cout<<"w "<<w<<" "<<" i "<<1.000001-(1.0/i+1)<<" j "<<1.0-(1.0/j+1)<<std::endl;
			putPixelB(hello, i, j, w);
		}
	}
	SDL_Flip(hello);
	SDL_Delay(2000);
}	
