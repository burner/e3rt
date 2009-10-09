#include "main.h"

void setupwindow(SDL_WindowID *window, SDL_GLContext *context, int height, int width) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { 
		std::cout<<"failed to create SDL Window"<<std::endl;
	}

	/* Request an opengl 3.2 context. 
	 * SDL doesn't have the ability to choose which profile at this time of writing,
	 * but it should default to the core profile */
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	/* Enable double buffering with a 24bit Z buffer.
	 * You may need to change this to 16 or 32 for your system */
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	/* Enable multisampling for a nice antialiased effect */
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	/* Create our window centered at 512x512 resolution */
	*window = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!*window) {
		std::cout<<"failed to create SDL Window"<<std::endl;
	}	
	/* Create our opengl context and attach it to our window */
	*context = SDL_GL_CreateContext(*window);

	/* This makes our buffer swap syncronized with the monitor's vertical refresh */
	SDL_GL_SetSwapInterval(1);

	/* Enable Z depth testing so objects closest to the viewpoint are in front of objects further away */
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void setupSzene(SDL_WindowID window) {
//	int i; /* Simple iterator */
//	GLuint vao, vbo[2]; /* Create handles for our Vertex Array Object and two Vertex Buffer Objects */
	//GLfloat projectionmatrix[16]; /* Our projection matrix starts with all 0s */
	//GLfloat modelmatrix[16]; /* Our model matrix  */
	/* An identity matrix we use to perform the equivalant of glLoadIdentity */
	//const GLfloat identitymatrix[16] = IDENTITY_MATRIX4; 

	/* Verticies to make 4 triangles in the shape of a tetrahedron */
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
	{  1.0, -1.0, -1.0  } };

	const GLfloat colors[12][3] = {
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
	{  1.0,  1.0,  1.0  } };

	GLchar *vertexsource, *fragmentsource;

	GLuint vertexshader, fragmentshader;

	GLuint shaderprogram;

	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glGenBuffers(2, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(GLfloat), tetrahedron, GL_STATIC_DRAW);
	
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(GLfloat), colors, GL_STATIC_DRAW);

	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);

	vertexsource = readShader("shader.vert");
	fragmentsource = readShader("shader.frag");

	vertexshader = glCreateShader(GL_VERTEX_SHADER);
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);
	glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);

	glCompileShader(vertexshader);
	glCompileShader(fragmentshader);

	shaderprogram = glCreateProgram();
	shader = shaderprogram;
	
	glAttachShader(shaderprogram, vertexshader);
	glAttachShader(shaderprogram, fragmentshader);
	
	glBindAttribLocation(shaderprogram, 0, "in_Position");
	glBindAttribLocation(shaderprogram, 1, "in_Color");

	glLinkProgram(shaderprogram);
	glUseProgram(shaderprogram);*/
}

void drawscene(SDL_WindowID window) {
	GLfloat projectionmatrix[16]; /* Our projection matrix starts with all 0s */
	GLfloat modelmatrix[16]; /* Our model matrix  */
	/* An identity matrix we use to perform the equivalant of glLoadIdentity */
	const GLfloat identitymatrix[16] = IDENTITY_MATRIX4; 

	perspective(projectionmatrix, 45.0, 1.0, 0.1, 100.0);
	foo->draw(NULL);
	
	i = (i+1)%360;
	/* Load the identity matrix into modelmatrix. rotate the model, and move it back 5 */
	memcpy(modelmatrix, identitymatrix, sizeof(GLfloat) * 16);
	rotate(modelmatrix, (GLfloat)i * foo->rot->x, X_AXIS);
	rotate(modelmatrix, (GLfloat)i * foo->rot->y, Y_AXIS);
	rotate(modelmatrix, (GLfloat)i * foo->rot->z, Z_AXIS);
	translate(modelmatrix, 0, 1, -7.0);

	multiply4x4(modelmatrix, projectionmatrix);

	/* Bind our modelmatrix variable to be a uniform called mvpmatrix in our shaderprogram */
	glUniformMatrix4fv(glGetUniformLocation(foo->getShaderHandle(), "mvpmatrix"), 1, GL_FALSE, modelmatrix);

	/* Make our background black */
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Invoke glDrawArrays telling that our data consists of individual triangles */
	glDrawArrays(GL_TRIANGLES, 0, 12);

	/* Swap our buffers to make our changes visible */
	SDL_GL_SwapWindow(window);

	/* Sleep for roughly 33 milliseconds between frames */
	//SDL_Delay(33);
}

void destroywindow(SDL_WindowID window, SDL_GLContext context) {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool handleEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_KEYDOWN:
				std::cout<<SDL_GetKeyName(event.key.keysym.sym)<<" KEYDOWN"<<std::endl;
				break;
			case SDL_KEYUP:
				std::cout<<SDL_GetKeyName(event.key.keysym.sym)<<" KEYUP"<<std::endl;
				break;
			case SDL_QUIT:
				return false;
		}
	}
	return true;
}

/* Our program's entry point */
int main(int argc, char *argv[]) {
	SDL_WindowID mainwindow; /* Our window handle */
	SDL_GLContext maincontext; /* Our opengl context handle */

	/* Create our window, opengl context, etc... */
	setupwindow(&mainwindow, &maincontext, 800, 1280);

	/* Call our function that performs opengl operations */
	//std::cout<<SDL_QUIT<<std::endl;
	foo = new Obj("t270.eob");
	setupSzene(mainwindow);
	bool handled = true;
	while(handled) {
		handled = handleEvents();
		//std::cout<<handled<<std::endl;
		drawscene(mainwindow);
	}


	/* Delete our opengl context, destroy our window, and shutdown SDL */
//	destroywindow(mainwindow, maincontext);

	return 0;
}
