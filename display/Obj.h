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
#include <SDL-1.3/SDL.h>

#ifndef OBJ
#define OBJ
class Obj {
	private:
		bool created;
		bool geo;
		int vSize, nSize, tSize, cSize;
		GLuint vertexCount;
		GLuint floatCount;
		GLuint shaderProgram;
		GLuint vao, vbo[2];
		std::string objFile;
		std::string verRef, fragRef, geomRef;
		GLchar *verSource, *fragSource, *geomSource;
		GLuint verShader, fragShader, geomShader;
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
