#ifndef CAMERA
#define CAMERA
#include <stack>
#include "../prim/vec3f.h"

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_projection.hpp"
#include "../glm/gtx/type_ptr.hpp"
#include "../glm/GLM_GTX_transform.h"

#define STATE_STOP 0
#define STATE_MOVING_FORWARD 1 
#define STATE_MOVING_BACKWARD 2 
#define STATE_MOVING_LEFT 3 
#define STATE_MOVING_RIGHT 4 

#define MOUSE_STATE_UP 0 
#define MOUSE_STATE_DOWN 1

#define KEY_STATE_UP 0
#define KEY_STATE_FORWARD 119
#define KEY_STATE_BACKWARD 115
#define KEY_STATE_LEFT 97
#define KEY_STATE_RIGHT 100

#define MOVE_STEP 0.0005
#define MAX_VELOCITY 1.0000
#define PI 3.14159

class Camera {
	private:
		vec3f::vec3f pos;
		float angleXZ;
		float angleYZ;
		int keyState;
		int mouseState;
		float velocity;

	public:
		Camera(vec3f::vec3f p, float angleXY, float angleyYZ);
		glm::mat4 applyCamMatrix();
		void setKeyState(int key);
		void setMouseState(int s);
		void moveLeft(void);
		void moveRight(void);
		void moveForward(void);
		void moveBackward(void);
		void moveUp(void);
		void moveDown(void);
		void decreasevelocity(void);
		void turnCamera(float thetaX, float thetaY);
};
#endif
