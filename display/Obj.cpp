#include "Obj.h"

Obj::Obj(std::string file) {
	created = false;
	geo = false;
	TiXmlDocument doc(file);
	doc.LoadFile();
	TiXmlElement *root = doc.RootElement();

	(*this).name = root->Attribute("name");

	//std::cout<<"filename of .obj "<<objFile<<std::endl;
	TiXmlElement *objNode = root->FirstChild("ObjFile")->ToElement();
	objFile = objNode->Attribute("fileName");
	//std::cout<<"filename of .obj "<<objFile<<std::endl;

	TiXmlElement *shaderRef = root->FirstChild("Shader")->ToElement();
	verRef = shaderRef->Attribute("Vertex");
	fragRef = shaderRef->Attribute("Fragment");
	if(NULL != shaderRef->Attribute("Geometry")) {
		geomRef = shaderRef->Attribute("Geometry");
		geo = true;
	}

	float x,y,z;
	TiXmlElement *posNode = root->FirstChild("Position")->ToElement();
	std::stringstream *str;
	
	//Position
	str = new std::stringstream(posNode->Attribute("x"));
	*str >> x;
	delete(str);
	str = new std::stringstream(posNode->Attribute("y"));
	*str >> y;
	delete(str);
	str = new std::stringstream(posNode->Attribute("z"));
	*str >> z;
	delete(str);
	this->pos = new vec3f(x,y,z);
	
	//Rotation
	TiXmlElement *rotNode = root->FirstChild("Rotation")->ToElement();	
	str = new std::stringstream(rotNode->Attribute("x"));
	*str >> x;
	delete(str);
	str = new std::stringstream(rotNode->Attribute("y"));
	*str >> y;
	delete(str);
	str = new std::stringstream(rotNode->Attribute("z"));
	*str >> z;
	delete(str);
	this->rot = new vec3f(x,y,z);
}

Obj::Obj() {
	created = false;
	geo = false;
}

Obj::~Obj() {
	delete(verSource);
	delete(fragSource);
	delete(geomSource);
	delete(pos);
	delete(rot);
}


void Obj::draw(GLfloat *projection) {
	if(!created) {
		//std::cout<<"filename "<<objFile<<" end filename"<<std::endl;
	
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

		//link shader
		glLinkProgram(shaderProgram);
	    
	/*	const GLfloat tetrahedron[12][3] = {
	    {  1.0,  1.0,  1.0  }, 
	    { -1.0, -1.0,  1.0  },
	    { -1.0,  1.0, -1.0  },
	    {  1.0,  1.0,  1.0  },
	    { -1.0, -1.0,  1.0  },
	    {  1.0, -1.0, -1.0  },
	    {  1.0,  1.0,  1.0  },
	    { -1.0,  1.0, -1.0  },
	    {  1.0, -1.0, -1.0  },
	    { -1.0, -1.0,  1.0  },
	    { -1.0,  1.0, -1.0  },
	    {  1.0, -1.0, -1.0  } };*/
	
/*	    const GLfloat colors[12][3] = {
	    {  1.0,  0.0,  0.0  }, 
	    {  1.0,  0.0,  0.0  }, 
	    {  1.0,  0.0,  0.0  }, 
	    {  0.0,  1.0,  0.0  },
	    {  0.0,  1.0,  0.0  },
	    {  0.0,  1.0,  0.0  },
	    {  0.0,  0.0,  1.0  },
	    {  0.0,  0.0,  1.0  },
	    {  0.0,  0.0,  1.0  },
	    {  1.0,  1.0,  1.0  },
	    {  1.0,  1.0,  1.0  },
	    {  1.0,  1.0,  1.0  } };*/

		ObjLoader obj(objFile);
		//obj.printVertexArray();
		vSize = obj.vSize;
		nSize = obj.nSize;
		tSize = obj.tSize;
		cSize = obj.vSize;
		//floatCount = obj.floatCount;
		//create vertex array
		glGenVertexArrays(1, &vao);
		glGenBuffers(2, vbo);
		glBindVertexArray(vao);
		
		//position vertices
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(obj.vec), obj.vec, GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, vSize*sizeof(GLfloat), obj.vec, GL_STATIC_DRAW);
		const GLuint positionIdx = glGetAttribLocation(shaderProgram, "in_Position");
		glVertexAttribPointer(positionIdx, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(positionIdx);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(obj.col), obj.col, GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, vSize*sizeof(GLfloat), obj.col, GL_STATIC_DRAW);
		const GLuint colorIdx = glGetAttribLocation(shaderProgram, "in_Color");
		glVertexAttribPointer(colorIdx, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(colorIdx);
		
		created = true;
	}
	//std::cout<<"Draw"<<std::endl;
	glUseProgram(shaderProgram);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES,0,vSize);
}

GLuint Obj::getShaderHandle() {
	return shaderProgram;
}

GLuint Obj::getVertexCount() {
	return vertexCount;
}
