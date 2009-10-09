#include "ObjLoader.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

ObjLoader::ObjLoader(std::string filename) {
	vectors = new std::vector<vec3f*>();
	triangle = new std::vector<tri*>();
	normals = new std::vector<vec3f*>();
	texture = new std::vector<vec2f*>();
	
	//open file
	std::ifstream ifs(filename.c_str());
	std::string temp;
	while(getline(ifs, temp)) {
		//debug
		//cout<<temp<<endl;
		parseStr(temp);
	}
}

void ObjLoader::parseStr(std::string line) {
	if (line.at(0) == 'v') {
		if (line.at(1) == ' ') {
			readVertexLine(line);
		}
		if (line.at(1) == 'n') {
			readVertexNormalLine(line);
		}
		if (line.at(1) == 't') {
			readVertexTexCoordLine(line);
		}
	} else if (line.at(0) == 'f') {
		readFaceLine(line);
	}
}

void ObjLoader::readVertexLine(std::string line) {
	std::string tmp[3];
	int j = 0;
	for(unsigned i = 2; i < line.length() && j < 3; i++) {
		if(line.at(i) == ' ') {
			j++;
			continue;
		}
		tmp[j].push_back(line.at(i));
	}
	vectors->push_back(new vec3f(
		(float)atof(tmp[0].c_str()),
		(float)atof(tmp[1].c_str()),
		(float)atof(tmp[2].c_str())));
}

void ObjLoader::readVertexNormalLine(std::string line) {
	std::string tmp[3];
	unsigned j = 0;
	for(unsigned i = 3; i < line.length() && j < 3; i++) {
		if(line.at(i) == ' ') {
			j++;
			continue;
		}
		tmp[j].push_back(line.at(i));
	}
	normals->push_back(new vec3f(
		(float)atof(tmp[0].c_str()),
		(float)atof(tmp[1].c_str()),
		(float)atof(tmp[2].c_str())));
}

void ObjLoader::readVertexTexCoordLine(std::string line) {
	std::string tmp[2];
	unsigned j = 0;
	for(unsigned i = 3; i < line.length() && j < 2; i++) {
		if(line.at(i) == ' ') {
			j++;
			continue;
		}
		tmp[j].push_back(line.at(i));
	}
	texture->push_back(new vec2f(
		(float)atof(tmp[0].c_str()),
		(float)atof(tmp[1].c_str())));
}

void ObjLoader::readFaceLine(std::string line) {
	std::string tmp[9];
	unsigned j = 0;
	for(unsigned i = 2; i < line.length() && j < 9; i++) {
		//if blank set pointer to next array entry and continue
		if(line.at(i) == ' ') {
			j++;
			continue;
		}
		//if / set pointer to next array entry and continue
		if(line.at(i) == '/') {
			j++;
			continue;
		}
		tmp[j].push_back(line.at(i));
	}
	triangle->push_back(new tri(atoi(tmp[0].c_str())-1,
								atoi(tmp[1].c_str())-1,
								atoi(tmp[2].c_str())-1,
								atoi(tmp[3].c_str())-1,
								atoi(tmp[4].c_str())-1,
								atoi(tmp[5].c_str())-1,
								atoi(tmp[6].c_str())-1,
								atoi(tmp[7].c_str())-1,
								atoi(tmp[8].c_str())-1
								));
}

std::vector<vec3f*>* ObjLoader::getVertices() {
	return vectors;
}

std::vector<tri*>* ObjLoader::getTriangle() {
	return triangle;
}

std::vector<vec3f*>* ObjLoader::getNormals() {
	return normals;
}

GLfloat** ObjLoader::getVertexArray() {
	GLfloat **tmp = new GLfloat*[triangle->size()*3];
	unsigned j = 0;
	for(unsigned i = 0; i < triangle->size(); i++) {
		tmp[j] = new GLfloat[3];
		tmp[j][0] = (*this->vectors)[(*triangle)[i]->x1]->x;
		tmp[j][1] = (*this->vectors)[(*triangle)[i]->x1]->y;
		tmp[j][2] = (*this->vectors)[(*triangle)[i]->x1]->z;
		j++;
		tmp[j] = new GLfloat[3];
		tmp[j][0] = (*this->vectors)[(*triangle)[i]->y1]->x;
		tmp[j][1] = (*this->vectors)[(*triangle)[i]->y1]->y;
		tmp[j][2] = (*this->vectors)[(*triangle)[i]->y1]->z;
		j++;
		tmp[j] = new GLfloat[3];
		tmp[j][0] = (*this->vectors)[(*triangle)[i]->z1]->x;
		tmp[j][1] = (*this->vectors)[(*triangle)[i]->z1]->y;
		tmp[j][2] = (*this->vectors)[(*triangle)[i]->z1]->z;
		j++;
	}
	return tmp;
}

GLfloat** ObjLoader::getNormalArray() {
	GLfloat **tmp = new GLfloat*[triangle->size()*3];
	unsigned j = 0;
	for(unsigned i = 0; i < triangle->size(); i++) {
		tmp[j] = new GLfloat[3];
		tmp[j][0] = (*this->normals)[(*triangle)[i]->x3]->x;
		tmp[j][1] = (*this->normals)[(*triangle)[i]->x3]->y;
		tmp[j][2] = (*this->normals)[(*triangle)[i]->x3]->z;
		j++;
		tmp[j] = new GLfloat[3];
		tmp[j][0] = (*this->normals)[(*triangle)[i]->y3]->x;
		tmp[j][1] = (*this->normals)[(*triangle)[i]->y3]->y;
		tmp[j][2] = (*this->normals)[(*triangle)[i]->y3]->z;
		j++;
		tmp[j] = new GLfloat[3];
		tmp[j][0] = (*this->normals)[(*triangle)[i]->z3]->x;
		tmp[j][1] = (*this->normals)[(*triangle)[i]->z3]->y;
		tmp[j][2] = (*this->normals)[(*triangle)[i]->z3]->z;
		j++;
	}
	return tmp;
}

GLfloat** ObjLoader::getTextureArray() {
	GLfloat **tmp = new GLfloat*[triangle->size()*3];
	unsigned j = 0;
	for(unsigned i = 0; i < triangle->size(); i++) {
		tmp[j] = new GLfloat[3];
		tmp[j][0] = (*this->texture)[(*triangle)[i]->x2]->x;
		tmp[j][1] = (*this->texture)[(*triangle)[i]->x2]->y;
		j++;
		tmp[j] = new GLfloat[3];
		tmp[j][0] = (*this->texture)[(*triangle)[i]->y2]->x;
		tmp[j][1] = (*this->texture)[(*triangle)[i]->y2]->y;
		j++;
		tmp[j] = new GLfloat[3];
		tmp[j][0] = (*this->texture)[(*triangle)[i]->z2]->x;
		tmp[j][1] = (*this->texture)[(*triangle)[i]->z2]->y;
		j++;
	}
	return tmp;
}

int ObjLoader::getVertexArraySize() {
	return triangle->size()*3*sizeof(GLfloat);
}

int ObjLoader::getNormalArraySize() {
	return normals->size()*3*sizeof(GLfloat);
}

int ObjLoader::getTextureArraySize() {
	return texture->size()*2*sizeof(GLfloat);
}
