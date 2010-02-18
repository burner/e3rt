#include "Camera.h"

Camera::Camera(vec3f::vec3f p, float angleXZ, float angleyYZ){
	pos=p;
	angleXZ=angleXZ;
	angleYZ=angleYZ;
	mouseState=false;
	keyState=0;
	velocity=0.0f;
}

glm::mat4 Camera::applyCamMatrix() {
	
	switch(keyState){
		case KEY_STATE_FORWARD:
			if(velocity<=MAX_VELOCITY)velocity+=MOVE_STEP;
			
			moveForward();
		break;
		case KEY_STATE_BACKWARD:
			if(velocity>=-MAX_VELOCITY)velocity-=MOVE_STEP;
			moveForward();
		break;
		case KEY_STATE_LEFT:
			moveLeft();
		break;
		case KEY_STATE_RIGHT:
			moveRight();
		break;

		default:
			//std::cout<<velocity<<std::endl;
			if(velocity<-MOVE_STEP || velocity>MOVE_STEP){
			velocity*=0.96f;
			moveForward();
			}
		break;
	}

	glm::mat4 retMat = glm::rotate(angleXZ, glm::vec3(0.0f, 1.0f, 0.0f));
	retMat *= glm::rotate(angleYZ, glm::vec3(1.0f, 0.0f, 0.0f));
	retMat *= glm::translate(-pos.x, -pos.y, -pos.z);
	
	return retMat;

}

void Camera::setKeyState(int key){
	keyState=key;		
}

void Camera::setMouseState(int s){
	mouseState=s;
}


void Camera::moveLeft(void){
		vec3f::vec3f direction(
		-sin((90.0f + angleXZ) * PI / 180),
		0.0, 
		cos((90.0f + angleXZ) * PI / 180));
	direction*= MOVE_STEP*100.f;
	pos+=direction;
}



void Camera::moveRight(void){
		vec3f::vec3f direction(
		sin((90.0f + angleXZ) * PI / 180),
		0.0, 
		-cos((90.0f + angleXZ) * PI / 180));
	direction*= MOVE_STEP*100.f;
	pos+=direction;
}




void Camera::moveForward(void){
	vec3f::vec3f direction(
		sin(angleXZ*PI/180),
		0.0,
		-cos(angleXZ*PI/180));
	direction*= velocity;
	pos+=direction;
}



void Camera::moveBackward(void){

}

void Camera::moveUp(void){};
void Camera::moveDown(void){};
void Camera::turnCamera(float thetaX, float thetaY){
	if(mouseState==1){
		angleXZ = (angleXZ + 0.3 * thetaX);
		angleYZ = (angleYZ + 0.05 * thetaY);
	}
};
