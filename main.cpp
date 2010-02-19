#include "main.h"
using namespace std;

void setupwindow(SDL_WindowID *window, SDL_GLContext *context, int height, int width) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { 
		std::cout<<"failed to create SDL Window"<<std::endl;
	}

	if(TTF_Init()) {
		std::cout<<"failed to init SDL_ttf"<<std::endl;
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
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);
	Timer::createTimer("fpsTicks");
	//curses
	//initscr();
	curs_set(0);
}

void setupSzene() {
	Projection = glm::perspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 20000.0f);
	View = glm::translate(0.f,0.f,0.f);
	//cout<<"setupScene\n";
	//FontWriter::initFontWriter();
	vec3f::vec3f camPos(-2.0f, 1.0f, 90.0f);
	//tCam=new Camera(camPos, 23.f, -45.f);
	foo = new Obj("t270.eob");
	litMonkey = new Obj("litMonkey.eob");
	litMonkey2 = new Obj("litMonkey2.eob");
	ground = new Obj("ground.eob");
	//sphere = new Sphere();
}

void drawscene(SDL_WindowID window) {
	i = (i+0.05f);
	if(i>=100.f){i=0.f;}
	glClearColor(0.0, 0.0, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	View = tCam.applyCamMatrix();


	pushViewMatrix();
	View *=  glm::translate(-2.0f,0.f,0.0f);
	View *= glm::scale(0.5f, 0.5f, 0.5f);
	View *= glm::rotate(i, glm::vec3(1.0f, 0.0f, 0.0f));
	View *= glm::rotate(i, glm::vec3(0.0f, 1.0f, 0.0f));
	View *= glm::rotate(i, glm::vec3(0.0f, 0.0f, 1.0f));
	glUseProgram(foo->getShaderHandle());
	glUniformMatrix4fv(glGetUniformLocation(foo->getShaderHandle(), "mvpmatrix"), 1, GL_FALSE, glm::value_ptr(Projection*View));
	foo->draw((GLfloat*)glm::value_ptr(Projection*View));
	
	pushViewMatrix();
	View *= glm::rotate(23.0f*i, glm::vec3(0.0f, 0.0f, 1.0f));
	View *=  glm::translate(-1.f,-0.7f,0.3f);
	View *= glm::scale(0.2f, 0.2f, 0.2f);
	glUseProgram(foo->getShaderHandle());
	glUniformMatrix4fv(glGetUniformLocation(foo->getShaderHandle(), "mvpmatrix"), 1, GL_FALSE, glm::value_ptr(Projection*View));
	foo->draw((GLfloat*)glm::value_ptr(Projection*View));
	popViewMatrix();
	
	
	View *= glm::rotate(46.0f*i, glm::vec3(1.0f, 0.0f, 0.0f));
	View *=  glm::translate(-2.f,-0.0f,0.0f);
	View *= glm::scale(0.6f, 0.1f, 0.8f);
	glUseProgram(foo->getShaderHandle());
	glUniformMatrix4fv(glGetUniformLocation(foo->getShaderHandle(), "mvpmatrix"), 1, GL_FALSE, glm::value_ptr(Projection*View));
	foo->draw((GLfloat*)glm::value_ptr(Projection*View));
	
	popViewMatrix();
	
	pushViewMatrix();
	View *= glm::translate(0.0f,0.0f,(i/10.f<10.f?-(i/10.f):-10.f));
	View *= glm::rotate((2.2f*i), glm::vec3(0.0f, 1.0f, 0.4f));
	
//Lightsource position
	GLfloat tmp[3];
	tmp[0]=2.0f;
	tmp[1]=5.0f;
	tmp[2]=3.5f;
	
	
	//Get the NormalMatrix
	glm::mat3 NormalMatrix(View); 
	NormalMatrix=glm::inverse(NormalMatrix);
	NormalMatrix=glm::transpose(NormalMatrix);
	glUseProgram(litMonkey->getShaderHandle());
	//std::cout<<"\nx:"<<litMonkey->getShaderHandle()<<"\n";
//	std::cout<<"\nx:"<<glGetUniformLocation(litMonkey->getShaderHandle(), "lightsource")<<"\n";
	glUniformMatrix4fv(glGetUniformLocation(litMonkey->getShaderHandle(), "MVPMatrix"), 1, GL_FALSE, glm::value_ptr(Projection*View));
	glUniform3f(glGetUniformLocation(litMonkey->getShaderHandle(), "lightsource"), tmp[0],tmp[1],tmp[2]);
	glUniformMatrix3fv(glGetUniformLocation(litMonkey->getShaderHandle(), "NormalMatrix"), 1, GL_FALSE, glm::value_ptr(NormalMatrix));
	litMonkey->draw((GLfloat*)glm::value_ptr(Projection*View));
	popViewMatrix();


	pushViewMatrix();
	View *= glm::translate(3.0f, 0.2f, 0.0f) * glm::rotate(2.0f*i, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat3 NormalMatrix2(View); 
	NormalMatrix2=glm::inverse(NormalMatrix2);
	NormalMatrix2=glm::transpose(NormalMatrix2);
	glUseProgram(litMonkey2->getShaderHandle());
	glUniformMatrix4fv(glGetUniformLocation(litMonkey2->getShaderHandle(), "MVPMatrix"), 1, GL_FALSE, glm::value_ptr(Projection*View));
	glUniformMatrix3fv(glGetUniformLocation(litMonkey2->getShaderHandle(), "NormalMatrix"), 1, GL_FALSE, glm::value_ptr(NormalMatrix2));
	litMonkey2->draw((GLfloat*)glm::value_ptr(Projection*View));
	popViewMatrix();



	
	
	View *= glm::translate(0.0f,-1.0f,0.0f) *glm::scale(20.0f, 20.0f, 20.0f) ;
	//View *= glm::rotate(0.f, glm::vec3(1.0f, 0.0f, 0.0f));
	//View *=glm::rotate(0.f, glm::vec3(0.0f, 1.0f, 0.0f));
	//View *=glm::rotate(0.f, glm::vec3(0.0f, 0.0f, 1.0f));
	//glUniform3f(glGetUniformLocation(ground->getShaderHandle(), "lightsource"), 0.0f,0.0f,0.0f);
	glUseProgram(ground->getShaderHandle());	
	glUniformMatrix4fv(glGetUniformLocation(ground->getShaderHandle(), "mvpmatrix"), 1, GL_FALSE, glm::value_ptr(Projection*View));
	ground->draw((GLfloat*)glm::value_ptr(Projection*View));
	
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

	//cout<<"main\n";
	
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
		//mvprintw(2,1, "Mousemiddle  X = %d : Y = %d", tCam.getMiddleX(), tCam.getMiddleY());
		//mvprintw(3,1, "Mousecurrent X = %d : Y = %d", tCam.getCurrentX(), tCam.getCurrentY());
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
				std::cout<<"SDL_QUIT"<<std::endl;
				result = false;
				break;
            case SDL_KEYDOWN:
               // std::cout<<SDL_GetKeyName(event.key.keysym.sym)<<" KEYDOWN"<<std::endl;
					switch(event.key.keysym.sym){
					case 119:
					case 115:
					case 97:
					case 100:
						tCam.setKeyState(event.key.keysym.sym);
					break;
					default:
					break;
				}
                break;
            case SDL_KEYUP:
            	tCam.setKeyState(0);
                if(event.key.keysym.sym == SDLK_ESCAPE) {
                    result = false;
                }
                break;
			case SDL_MOUSEBUTTONDOWN:
				//std::cout<<"MOUSEDOWN"<<std::endl;
				int x, y;
				SDL_GetMouseState(&x, &y);
				if(event.button.button == SDL_BUTTON_LEFT) {
					tCam.setMouseState(1);
				//	
				}
				//std::cout<<x<<" "<<y<<std::endl;
				break;
			case SDL_MOUSEBUTTONUP:
				//std::cout<<"MouseUP"<<std::endl;
				//SDL_GetMouseState(&x, &y);
				//tCam.turnCamera(event.motion.xrel, event.motion.yrel);
				tCam.setMouseState(0);
				break;
			case SDL_MOUSEMOTION:
				//std::cout<<"MouseMotion"<<std::endl;
				tCam.turnCamera(event.motion.xrel, event.motion.yrel);
				break;
        }
    }
	return result;
}

void pushViewMatrix(){
	viewStack.push(View);
}

void popViewMatrix(){
	View=viewStack.top();
	viewStack.pop();
}
