#include <stdlib.h> 
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include <curses.h>
#include <pthread.h>
#include "/usr/local/sdl-1.3/include/SDL/SDL.h"
#include "/usr/local/sdl-1.3/include/SDL/SDL_mutex.h"
#include "/usr/local/sdl-1.3/include/SDL/SDL_thread.h"

#include <SDL/SDL_ttf.h>

/* Ensure we are using opengl's core profile only */
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#include "display/Camera.h"
#include "display/FontWriter.h"
#include "util/Timer.h"
#include "display/Obj.h"
#include "display/Sphere.h"
#include "util/ShaderHandle.h"
#define TIXML_USE_STL
#include "tinyxml/tinyxml.h"

//#include "defines.h"

//matrix
#include "glm/glm.hpp"
#include "glm/gtc/matrix_projection.hpp"
#include "glm/gtx/type_ptr.hpp"
#include "glm/GLM_GTX_transform.h"

#define PROGRAM_NAME "e3rt"

GLfloat i = 0;
GLuint shader;

Obj *foo;
Sphere *sphere;

int width = 1200;
int height = 800;
float angle = 45.0f;
int fps;
int frames;
bool result;
Camera tCam(angle, 0.1f, 100.0f, width, height);

void setupwindow(SDL_WindowID *window, SDL_GLContext *context, int height, int width);
void drawscene(SDL_WindowID window); 
void setupSzene();
void destroywindow(SDL_WindowID window, SDL_GLContext context);
bool handle();
int main(int argc, char *argv[]);
