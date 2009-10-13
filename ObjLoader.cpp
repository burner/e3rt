#include "ObjLoader.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

ObjLoader::ObjLoader(std::string filename) {
	vec = NULL;
	nor = NULL;
	tex = NULL;
	col = NULL;
	//open file
	std::ifstream ifs(filename.c_str());
	std::string temp;
	//std::cout<<"Objloader filename "<<filename<<std::endl;
	while(getline(ifs, temp)) {
		//debug
		//std::cout<<temp<<std::endl;
		parseStr(temp);
	}
	makeVertexArray();
	makeNormalArray();
	makeTextureArray();
	makeColorArray();
	floatCount = vectors.size()*3;
}

void ObjLoader::parseStr(std::string line) {
	if (line.at(0) == 'v') {
		if (line.at(1) == ' ') {
			//std::cout<<"Vertex Line"<<std::endl;
			readVertexLine(line);
		}
		if (line.at(1) == 'n') {
			//std::cout<<"Normal Line"<<std::endl;
			readVertexNormalLine(line);
		}
		if (line.at(1) == 't') {
			//std::cout<<"Tex Line"<<std::endl;
			readVertexTexCoordLine(line);
		}
	} else if (line.at(0) == 'f') {
		//std::cout<<"Face Line"<<std::endl;
		readFaceLine(line);
	}
}

void ObjLoader::readVertexLine(std::string line) {
	std::stringstream tmp[3];
	GLfloat v[3];
	int j = 0;
	for(unsigned i = 2; i < line.length() && j < 3; i++) {
		if(line.at(i) == ' ') {
			j++;
			continue;
		}
		tmp[j]<<(line.at(i));
	}
	tmp[0]>>v[0];	
	tmp[1]>>v[1];
	tmp[2]>>v[2];
	//std::cout<<"x "<<v[0]<<" y "<<v[1]<<" z "<<v[2]<<std::endl;
	vectors.push_back(new vec3f(v[0], v[1], v[2]));
}

void ObjLoader::readVertexNormalLine(std::string line) {
	std::stringstream tmp[3];
	GLfloat v[3];
	unsigned j = 0;
	for(unsigned i = 3; i < line.length() && j < 3; i++) {
		if(line.at(i) == ' ') {
			j++;
			continue;
		}
		tmp[j]<<(line.at(i));
	}
	tmp[0]>>v[0];	
	tmp[1]>>v[1];
	tmp[2]>>v[2];
	//std::cout<<"x "<<v[0]<<" y "<<v[1]<<" z "<<v[2]<<std::endl;
	normals.push_back(new vec3f(v[0], v[1], v[2]));
}

void ObjLoader::readVertexTexCoordLine(std::string line) {
	std::stringstream tmp[2];
	GLfloat v[2];
	unsigned j = 0;
	for(unsigned i = 3; i < line.length() && j < 2; i++) {
		if(line.at(i) == ' ') {
			j++;
			continue;
		}
		tmp[j]<<(line.at(i));
	}
	tmp[0]>>v[0];	
	tmp[1]>>v[1];
	//std::cout<<"x "<<v[0]<<" y "<<v[1]<<std::endl;
	texture.push_back(new vec2f(v[0], v[1]));
}

void ObjLoader::readFaceLine(std::string line) {
	std::stringstream tmp[9];
	int f[9];
	unsigned j = 0;
	for(unsigned i = 2; i < line.length() && j < 9; i++) {
		//if blank set pointer to next array entry and continue
		if(line.at(i) == ' ' || line.at(i) == '/') {
			j++;
			continue;
		}
		tmp[j]<<(line.at(i));
	}
	tmp[0]>>f[0]; f[0]--;
	tmp[1]>>f[1]; f[1]--;
	tmp[2]>>f[2]; f[2]--;
	tmp[3]>>f[3]; f[3]--;
	tmp[4]>>f[4]; f[4]--;
	tmp[5]>>f[5]; f[5]--;
	tmp[6]>>f[6]; f[6]--;
	tmp[7]>>f[7]; f[7]--;
	tmp[8]>>f[8]; f[8]--;
	//std::cout<<f[0]<<" "<<f[1]<<" "<<f[2]<<" "<<f[3]<<" "<<f[4]<<" "<<f[5]<<" "<<f[6]<<" "<<f[7]<<" "<<f[8]<<std::endl;;	
	triangle.push_back(new tri(f[0],f[1],f[2],f[3],f[4],f[5],f[6],f[7],f[8]));	
}

std::vector<vec3f*> ObjLoader::getVertices() {
	return vectors;
}

std::vector<tri*> ObjLoader::getTriangle() {
	return triangle;
}

std::vector<vec3f*> ObjLoader::getNormals() {
	return normals;
}

void ObjLoader::makeVertexArray() {
	unsigned triSize = triangle.size();
	vSize = triSize * 3 * 3;
	this->vec = new GLfloat[triSize*3*3];
	unsigned j = 0;
	for(unsigned i = 0; i < triSize; i++) {
		this->vec[j] = vectors.at(triangle.at(i)->x1)->x;
		j++;
		this->vec[j] = vectors.at(triangle.at(i)->x1)->y;
		j++;
		this->vec[j] = vectors.at(triangle.at(i)->x1)->z;
		j++;

		this->vec[j] = vectors.at(triangle.at(i)->y1)->x;
		j++;
		this->vec[j] = vectors.at(triangle.at(i)->y1)->y;
		j++;
		this->vec[j] = vectors.at(triangle.at(i)->y1)->z;
		j++;

		this->vec[j] = vectors.at(triangle.at(i)->z1)->x;
		j++;
		this->vec[j] = vectors.at(triangle.at(i)->z1)->y;
		j++;
		this->vec[j] = vectors.at(triangle.at(i)->z1)->z;
		j++;
	} 
}

void ObjLoader::makeNormalArray() {
	unsigned triSize = triangle.size();
	nSize = triSize * 3 * 3;
	this->nor = new GLfloat[triSize*3*3];
	unsigned j = 0;
	for(unsigned i = 0; i < triSize; i++) {
		this->nor[j] = normals.at(triangle.at(i)->x3)->x;
		j++;
		this->nor[j] = normals.at(triangle.at(i)->x3)->y;
		j++;
		this->nor[j] = normals.at(triangle.at(i)->x3)->z;
		j++;

		this->nor[j] = normals.at(triangle.at(i)->y3)->x;
		j++;
		this->nor[j] = normals.at(triangle.at(i)->y3)->y;
		j++;
		this->nor[j] = normals.at(triangle.at(i)->y3)->z;
		j++;

		this->nor[j] = normals.at(triangle.at(i)->z3)->x;
		j++;
		this->nor[j] = normals.at(triangle.at(i)->z3)->y;
		j++;
		this->nor[j] = normals.at(triangle.at(i)->z3)->z;
		j++;
	}
} 

void ObjLoader::makeTextureArray() {
	unsigned triSize = triangle.size();
	tSize = triSize * 3 * 2;
	this->tex = new GLfloat[triSize*3*2];
	unsigned j = 0;
	for(unsigned i = 0; i < triSize; i++) {
		this->tex[j] = texture.at(triangle.at(i)->x2)->x;
		j++;
		this->tex[j] = texture.at(triangle.at(i)->x2)->y;
		j++;

		this->tex[j] = texture.at(triangle.at(i)->y2)->x;
		j++;
		this->tex[j] = texture.at(triangle.at(i)->y2)->y;
		j++;

		this->tex[j] = texture.at(triangle.at(i)->z2)->x;
		j++;
		this->tex[j] = texture.at(triangle.at(i)->z2)->y;
		j++;
	}
}

void ObjLoader::makeColorArray() {
	unsigned triSize = triangle.size()*3*3;
	this->col = new GLfloat[triSize];
	for(unsigned i = 0; i < triSize; i++) {
		this->col[i] =(GLfloat) (rand()/(float(RAND_MAX)+1));
		//std::cout<<this->col[i]<<" ";
	}
}

void ObjLoader::printVertexArray() {
	for(int i = 0; i < vSize; i+=9) {
		std::cout<<vec[i]<<" "<<vec[i+1]<<" "<<vec[i+2]<<"\t\t";
		std::cout<<vec[i+3]<<" "<<vec[i+4]<<" "<<vec[i+5]<<"\t\t";
		std::cout<<vec[i+6]<<" "<<vec[i+7]<<" "<<vec[i+8]<<std::endl;
	}
}	

void ObjLoader::printNormalArray() {
	for(int i = 0; i < vSize; i+=9) {
		std::cout<<nor[i]<<" "<<nor[i+1]<<" "<<nor[i+2]<<"\t\t";
		std::cout<<nor[i+3]<<" "<<nor[i+4]<<" "<<nor[i+5]<<"\t\t";
		std::cout<<nor[i+6]<<" "<<nor[i+7]<<" "<<nor[i+8]<<std::endl;
	}
}

void ObjLoader::printTextureArray() {
	for(int i = 0; i < vSize; i+=6) {
		std::cout<<nor[i]<<" "<<nor[i+1]<<"\t\t";
		std::cout<<nor[i+2]<<" "<<nor[i+3]<<"\t\t";
		std::cout<<nor[i+4]<<" "<<nor[i+5]<<std::endl;
	}
}

void ObjLoader::printColorArray() {
	for(int i = 0; i < vSize; i+=9) {
		std::cout<<col[i]<<" "<<col[i+1]<<" "<<col[i+2]<<"\t\t";
		std::cout<<col[i+3]<<" "<<col[i+4]<<" "<<col[i+5]<<"\t\t";
		std::cout<<col[i+6]<<" "<<col[i+7]<<" "<<col[i+8]<<std::endl;
	}
}
