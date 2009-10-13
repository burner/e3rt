#include <stdlib.h> 
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include <curses.h>
#include <pthread.h>

/* Ensure we are using opengl's core profile only */
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#include "Timer.h"
#include <SDL-1.3/SDL.h>
#include <SDL-1.3/SDL_mutex.h>
#include <SDL-1.3/SDL_thread.h>
#include "utils.h"
#include "Obj.h"
#include "ShaderHandle.h"
#define TIXML_USE_STL
#include "tinyxml.h"

#define PROGRAM_NAME "e3rt"

GLfloat i = 0;
GLuint shader;


Obj *foo;

int fps;
int frames;
bool result;

void setupwindow(SDL_WindowID *window, SDL_GLContext *context, int height, int width);
void drawscene(SDL_WindowID window); 
void setupSzene();
void destroywindow(SDL_WindowID window, SDL_GLContext context);
bool handle();
int main(int argc, char *argv[]);
