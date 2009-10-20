#include <stack>
#include "../prim/vec3f.h"

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_projection.hpp"
#include "../glm/gtx/type_ptr.hpp"
#include "../glm/GLM_GTX_transform.h"

#ifndef CAMERA
#define CAMERA
class Camera {
	private:
		bool mChange;
		int mX, mY;
		int cX, cY;
	public:
		glm::mat4 Proj;
		glm::mat4 View;
		std::stack<glm::mat4> viewStack;
		vec3f::vec3f pos;
		vec3f::vec3f rot;
		Camera(float angle, float near, float far, int width, int height);
		void placeCam();
		void setMiddle(int x, int y);
		void setCurrent(int x, int y);
		void unsetMiddle();
		bool getMiddleState();
		int getMiddleX();
		int getMiddleY();
		int getCurrentX();
		int getCurrentY();
};
#endif
