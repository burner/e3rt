#include "Obj.h"

Obj::Obj(std::string file) {
	std::cout<<"Obj constr.\n";
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

	//Textures
	TiXmlElement *diffuse0El = root->FirstChild("Diffuse0")->ToElement();
	diffuse0fn = diffuse0El->Attribute("fileName");

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
	std::cout<<"constr. end\n";
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


void Obj::draw(GLfloat *proj) {
	if(!created) {
		
		std::cout<<"filename "<<objFile<<" end filename"<<std::endl;
	
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
		GLsizei len;
		GLchar logf[10000];
		glGetShaderInfoLog(verShader, ((GLsizei)10000), &len, logf);
		for(GLsizei i = 0; i < len; i++) std::cout<<logf[i];
		glCompileShader(fragShader);
		glGetShaderInfoLog(fragShader, ((GLsizei)10000), &len, logf);
		for(GLsizei i = 0; i < len; i++) std::cout<<logf[i];
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

		GLuint uniformDiffuse = glGetAttribLocation(shaderProgram, "Diffuse");
		glUniform1i(uniformDiffuse,0);
	   
		ObjLoader obj(objFile);
		//obj.printVertexArray();
		vSize = obj.vSize;
		nSize = obj.nSize;
		tSize = obj.tSize;
		cSize = obj.vSize;
		//floatCount = obj.floatCount;
		//create vertex array
		glGenVertexArrays(1, &vao);
		glGenBuffers(3, vbo);
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
		glBufferData(GL_ARRAY_BUFFER, vSize*sizeof(GLfloat), obj.nor, GL_STATIC_DRAW);
		const GLuint norIdx = glGetAttribLocation(shaderProgram, "in_Nor");
		glVertexAttribPointer(norIdx, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(norIdx);
		
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(obj.tex), obj.tex, GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, tSize*sizeof(GLfloat), obj.tex, GL_STATIC_DRAW);
		const GLuint texIdx = glGetAttribLocation(shaderProgram, "in_Tex");
		glVertexAttribPointer(texIdx, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(texIdx);
		
		SDL_Surface *tex = IMG_Load(diffuse0fn.c_str());

		//TTF_Font *font = TTF_OpenFont("FreeSans.ttf", 20);
		//SDL_Color co;
		//co.r = 255;
		//co.g = 155;
		//co.b = 255;
		//SDL_Surface *fontSurface = TTF_RenderText_Blended(font, "H", co);
		//double a = log(fontSurface->w)/log(2);
		//double b = log(fontSurface->h)/log(2);

		//GLint w =(int) ((pow(2,ceil(a)))+0.5);
		//GLint h =(int) ((pow(2,ceil(b)))+0.5);

		//SDL_Surface *fontD = SDL_CreateRGBSurface(0,w, h,32,
		//	0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

		//SDL_BlitSurface(fontSurface, 0, fontD, 0);

		//SDL_SaveBMP(fontSurface, "font.bmp");
		//SDL_SaveBMP(fontD, "font1.bmp");

		glGenTextures( 1, &diffuse0 );
		glActiveTexture(GL_TEXTURE0);
		glBindTexture( GL_TEXTURE_2D, diffuse0 );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		glTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGB, tex->w, tex->h, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->pixels);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGB, fontD->w, fontD->h, 0, GL_RGB, GL_UNSIGNED_BYTE, fontD->pixels);
		
		created = true;
	}
//	std::cout<<"Draw"<<std::endl;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuse0);
	glUseProgram(shaderProgram);
	//glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "mvpmatrix"), 1, GL_FALSE, proj);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES,0,vSize);
}

GLuint Obj::getShaderHandle() {
	
	return shaderProgram;
}

GLuint Obj::getVertexCount() {
	return vertexCount;
}
