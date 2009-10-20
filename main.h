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

#include "util/Timer.h"
#include <SDL-1.3/SDL.h>
#include <SDL-1.3/SDL_mutex.h>
#include <SDL-1.3/SDL_thread.h>
#include "display/Obj.h"
#include "util/ShaderHandle.h"
#define TIXML_USE_STL
#include "tinyxml/tinyxml.h"

#include "display/Camera.h"

//matrix
#include "glm/glm.hpp"
#include "glm/gtc/matrix_projection.hpp"
#include "glm/gtx/type_ptr.hpp"
#include "glm/GLM_GTX_transform.h"

#define PROGRAM_NAME "e3rt"

GLfloat i = 0;
GLuint shader;

Obj *foo;

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
