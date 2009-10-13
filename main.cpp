#include "main.h"

void setupwindow(SDL_WindowID *window, SDL_GLContext *context, int height, int width) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { 
		std::cout<<"failed to create SDL Window"<<std::endl;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	*window = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!*window) {
		std::cout<<"failed to create SDL Window"<<std::endl;
	}	
	*context = SDL_GL_CreateContext(*window);

	SDL_GL_SetSwapInterval(1);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void setupSzene() {
	foo = new Obj("t270.eob");
}

void drawscene(SDL_WindowID window) {
	GLfloat projectionmatrix[16];
	GLfloat modelmatrix[16];
	const GLfloat identitymatrix[16] = IDENTITY_MATRIX4; 

	perspective(projectionmatrix, 45.0, 1.0, 0.1, 100.0);
	
	i = (i+1)%360;
	memcpy(modelmatrix, identitymatrix, sizeof(GLfloat) * 16);
	//rotate(modelmatrix, (GLfloat)i * -1.0, X_AXIS);
	//rotate(modelmatrix, (GLfloat)i * 1.0, Y_AXIS);
	//rotate(modelmatrix, (GLfloat)i * 0.5, Z_AXIS);
	translate(modelmatrix, 0, 0, -8.0);

	multiply4x4(modelmatrix, projectionmatrix);

	glUniformMatrix4fv(glGetUniformLocation(foo->getShaderHandle(), "mvpmatrix"), 1, GL_FALSE, modelmatrix);

	glClearColor(0.0, 0.0, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	foo->draw(NULL);
	SDL_GL_SwapWindow(window);
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

int main(int argc, char *argv[]) {
	foo = NULL;
	SDL_WindowID mainwindow;
	SDL_GLContext maincontext;

	setupwindow(&mainwindow, &maincontext, 800, 1280);

	setupSzene();
	bool handled = true;
	while(handled) {
		handled = handleEvents();
		//std::cout<<handled<<std::endl;
		drawscene(mainwindow);
	}
	destroywindow(mainwindow, maincontext);
	return 0;
}
