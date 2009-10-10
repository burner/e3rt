#include <stdlib.h> 
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>

/* Ensure we are using opengl's core profile only */
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#include <SDL-1.3/SDL.h>
#include <math.h>
#include "utils.h"
#include "Obj.h"
#include "ShaderHandle.h"

#define PROGRAM_NAME "e3rt"

int i = 0;
GLuint shader;

Obj *foo;

void setupwindow(SDL_WindowID *window, SDL_GLContext *context, int height, int width);
void drawscene(SDL_WindowID window); 
void setupSzene(SDL_WindowID window);
void destroywindow(SDL_WindowID window, SDL_GLContext context);
bool handleEvents();
int main(int argc, char *argv[]);
