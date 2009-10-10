#include "Obj.h"

Obj::Obj(std::string file) {
	shaderCreated = false;
	geo = false;
	Femto *parse = new Femto(&file);

	Node *root = parse->getRoot();

	name = root->getAttri("name")[0];

	Node *objNode = root->getChilds("ObjFile")[0];
	objFile = objNode->getAttri("fileName");

	Node *shaderRef = root->getChilds("Shader")[0];
	verRef = shaderRef->getAttri("Vertex");
	fragRef = shaderRef->getAttri("Fragment");
	if(shaderRef->hasAttri("Geometry")) {
		geomRef = shaderRef->getAttri("Geometry");
		geo = true;
	}

	float x,y,z;
	Node *posNode = root->getChilds("Position")[0];
	std::stringstream *str;
	
	//Position
	str = new std::stringstream(posNode->getAttri("x"));
	*str >> x;
	delete(str);
	str = new std::stringstream(posNode->getAttri("y"));
	*str >> y;
	delete(str);
	str = new std::stringstream(posNode->getAttri("z"));
	*str >> z;
	delete(str);
	this->pos = new vec3f(x,y,z);
	
	//Rotation
	Node *rotNode = root->getChilds("Rotation")[0];	
	str = new std::stringstream(rotNode->getAttri("x"));
	*str >> x;
	delete(str);
	str = new std::stringstream(rotNode->getAttri("y"));
	*str >> y;
	delete(str);
	str = new std::stringstream(rotNode->getAttri("z"));
	*str >> z;
	delete(str);
	this->rot = new vec3f(x,y,z);

	delete(parse);
}

Obj::~Obj() {
	delete(verSource);
	delete(fragSource);
	delete(geomSource);
	delete(pos);
	delete(rot);
}

void Obj::draw(GLfloat *projection) {
	if(!shaderCreated) {
		ObjLoader *obj = new ObjLoader(objFile);
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(3,vbo);
		
		glBindVertexArray(vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);

		//Vertex
		glBufferData(GL_ARRAY_BUFFER, obj->getVertexArraySize(), obj->getVertexArray(), GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE,0,0);
		glEnableVertexAttribArray(0);
		vertexCount = obj->getVertexArraySize();

		//Normal
		glBufferData(GL_ARRAY_BUFFER, obj->getNormalArraySize(), obj->getNormalArray(), GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE,0,0);
		glEnableVertexAttribArray(1);
		
		//TexCoord
		glBufferData(GL_ARRAY_BUFFER, obj->getTextureArraySize(), obj->getTextureArray(), GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE,0,0);
		glEnableVertexAttribArray(2);

		//read shader source
		verSource = readShader(verRef);
		fragSource = readShader(fragRef);
		if(geo) {
			geomSource = readShader(fragRef);
		}
		
		//create shader pointer
		verShader = glCreateShader(GL_VERTEX_SHADER);
		fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		if(geo) {
			geomShader = glCreateShader(GL_GEOMETRY_SHADER);
		}

		//bind source to pointer
		glShaderSource(verShader, 1, (const GLchar**)&verSource, 0);
		glShaderSource(fragShader, 1, (const GLchar**)&fragSource, 0);
		if(geo) {
			glShaderSource(geomShader, 1, (const GLchar**)&geomSource, 0);
		}

		//compile shader
		glCompileShader(verShader);
		glCompileShader(fragShader);
		if(geo) {
			glCompileShader(geomShader);
		}

		//attach shader
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, verShader);
		glAttachShader(shaderProgram, fragShader);
		if(geo) {
			glAttachShader(shaderProgram, geomShader);
		}

		//bind attrib
		glBindAttribLocation(shaderProgram, 0, "in_Position");
		glBindAttribLocation(shaderProgram, 0, "in_Color");

		//link shader
		glLinkProgram(shaderProgram);

		shaderCreated = true;
		//DO the rest lacy asshole
	}
	glUseProgram(shaderProgram);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glDrawArrays(GL_TRIANGLES,0,vertexCount);
}

GLuint Obj::getShaderHandle() {
	return shaderProgram;
}

GLuint Obj::getVertexCount() {
	return vertexCount;
}
