#include <stack>
#include "vec3f.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_projection.hpp"
#include "glm/gtx/type_ptr.hpp"
#include "glm/GLM_GTX_transform.h"

#ifndef CAMERA
#define CAMERA
class Camera {
	public:
		glm::mat4 Proj;
		glm::mat4 View;
		std::stack<glm::mat4> viewStack;
		vec3f::vec3f pos;
		vec3f::vec3f rot;
		Camera(float angle, float near, float far, int width, int height);
		void placeCam();
};
#endif
