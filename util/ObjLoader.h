#include "../prim/vec3f.h"
#include "../prim/vec2f.h"
#include "../prim/tri.h"
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#ifndef OBJLOADER
#define OBJLOADER
class ObjLoader {
	private:
		std::vector<vec3f*> vectors;
		std::vector<tri*> triangle;
		std::vector<vec3f*> normals;
		std::vector<vec2f*> texture;
		
		void parseStr(std::string line);
		void readVertexLine(std::string line);
		void readVertexNormalLine(std::string line);
		void readVertexTexCoordLine(std::string line);
		void readFaceLine(std::string line);

		void makeVertexArray();
		void makeNormalArray();
		void makeTextureArray();
		void makeColorArray();

	public:
		GLfloat *vec;
		GLfloat *nor;
		GLfloat *tex;
		GLfloat *col;
		int vSize, nSize, tSize;
		int floatCount;

		ObjLoader(std::string filename);
		std::vector<vec3f*> getVertices();
		std::vector<tri*> getTriangle();
		std::vector<vec3f*> getNormals();

		void printVertexArray();
		void printNormalArray();
		void printTextureArray();
		void printColorArray();
};
#endif
