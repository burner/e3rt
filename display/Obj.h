#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include "../tinyxml/tinyxml.h"
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#include "../util/ObjLoader.h"
#include "../prim/vec3f.h"
#include "../util/ShaderHandle.h"
#include "/usr/local/sdl-1.3/include/SDL/SDL.h"
#include "/usr/include/SDL/SDL_image.h"

#include <SDL/SDL_ttf.h>

//#include "../gli/gli/gli.hpp"
//#include "../soil/src/SOIL.h"

#ifndef OBJ
#define OBJ
class Obj {
	protected:
		bool created;
		bool geo;
		int vSize, nSize, tSize, cSize;
		GLuint vertexCount;
		GLuint floatCount;
		GLuint shaderProgram;
		GLuint vao, vbo[3];
		std::string objFile;
		std::string verRef, fragRef, geomRef;
		GLchar *verSource, *fragSource, *geomSource;
		GLuint verShader, fragShader, geomShader;
		GLuint diffuse0, diffuse1, diffuse2, diffuse3;
		std::string diffuse0fn, diffuse1fn, diffuse2fn, *diffuse3fn;
	public:
		std::string name;
		vec3f *pos;
		vec3f *rot;
		Obj(std::string file);
		Obj();
		~Obj();
		virtual void draw(GLfloat *projection);
		GLuint getShaderHandle();
		GLuint getVertexCount();
};
#endif		
