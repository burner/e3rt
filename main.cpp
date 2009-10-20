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

	//SDL_GL_SetSwapInterval(1);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	Timer::createTimer("fpsTicks");

	//curses
	initscr();
	curs_set(0);
}

void setupSzene() {
	foo = new Obj("t270.eob");
}

void drawscene(SDL_WindowID window) {
	i = (i+0.05f);
	glm::mat4 Projection = glm::perspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);
	glm::mat4 ViewTranslate = glm::translate(0.0f,0.0f,-4.0f);
	glm::mat4 ViewRotateX = glm::rotate(i, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 ViewRotateY = glm::rotate(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 ViewRotateZ = glm::rotate(45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 View = ViewTranslate * ViewRotateX * ViewRotateY * ViewRotateZ;

	glUniformMatrix4fv(glGetUniformLocation(foo->getShaderHandle(), "mvpmatrix"), 1, GL_FALSE, glm::value_ptr(Projection*View));

	glClearColor(0.0, 0.0, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	foo->draw(NULL);
	SDL_GL_SwapWindow(window);
}

void destroywindow(SDL_WindowID window, SDL_GLContext context) {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	endwin();
}

int main(int argc, char *argv[]) {
	foo = NULL;
	SDL_WindowID mainwindow;
	SDL_GLContext maincontext;
	
	setupwindow(&mainwindow, &maincontext, height, width);
	setupSzene();
	while(handle()) {
		drawscene(mainwindow);
		if(Timer::read("fpsTicks") >= 1000) {
			Timer::reset("fpsTicks");
			fps = frames;
			frames = 0;
		} else {
			frames++;
		}
		mvprintw(1,1, "FPS: %d", fps);
		mvprintw(2,1, "Mousemiddle  X = %d : Y = %d", tCam.getMiddleX(), tCam.getMiddleY());
		mvprintw(3,1, "Mousecurrent X = %d : Y = %d", tCam.getCurrentX(), tCam.getCurrentY());
		refresh();
	}
	destroywindow(mainwindow, maincontext);
	return 0;
}

bool handle() {
	bool result = true;
	SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
				std::cout<<"FOO QUIT"<<std::endl;
                result = false;
                break;
            case SDL_KEYDOWN:
                std::cout<<SDL_GetKeyName(event.key.keysym.sym)<<" KEYDOWN"<<std::endl;
                break;
            case SDL_KEYUP:
                if(event.key.keysym.sym == SDLK_ESCAPE) {
                    result = false;
                }
                break;
			//MOUSEBUTTONDOWN is MOUSEMOTION
			case SDL_MOUSEBUTTONDOWN:
				int x, y;
				SDL_GetMouseState(0,&x, &y);
				tCam.setCurrent(x,y);
				if(event.button.button == SDL_BUTTON_MIDDLE) {
					if(!tCam.getMiddleState()) {
						tCam.setMiddle(x,y);
					}
				}
				break;
			//MOUSEBUTTONUP is MOUSEBUTTONDOWN
			case SDL_MOUSEBUTTONUP:
				std::cout<<"MouseDOWN"<<std::endl;
				if(event.button.button == SDL_BUTTON_MIDDLE) {
					tCam.unsetMiddle();
				}
				break;
			case SDL_MOUSEMOTION:
				std::cout<<"MouseUP"<<std::endl;
				break;
        }
    }
	return result;
}
