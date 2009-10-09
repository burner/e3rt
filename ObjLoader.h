#include "vec3f.h"
#include "vec2f.h"
#include "tri.h"
#include <vector>
#include <string>
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#ifndef OBJLOADER
#define OBJLOADER
class ObjLoader {
	private:
		std::vector<vec3f*> *vectors;
		std::vector<tri*> *triangle;
		std::vector<vec3f*> *normals;
		std::vector<vec2f*> *texture;
		
		void parseStr(std::string line);
		void readVertexLine(std::string line);
		void readVertexNormalLine(std::string line);
		void readVertexTexCoordLine(std::string line);
		void readFaceLine(std::string line);

	public:
		ObjLoader(std::string filename);
		std::vector<vec3f*>* getVertices();
		std::vector<tri*>* getTriangle();
		std::vector<vec3f*>* getNormals();

		GLfloat** getVertexArray();
		int getVertexArraySize();	
		GLfloat** getTextureArray();
		int getTextureArraySize();	
		GLfloat** getNormalArray();
		int getNormalArraySize();	
};
#endif
