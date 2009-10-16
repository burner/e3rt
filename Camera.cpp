#include "Camera.h"

Camera::Camera(float angle, float near, float far, int width, int height) {
	Proj = glm::perspective(angle, (GLfloat)width/(GLfloat)height, near, far);
}

void Camera::placeCam() {
	glm::mat4 VTrans = glm::translate(pos.x, pos.y, pos.z);
	glm::mat4 ViewRotX = glm::rotate(rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 ViewRotY = glm::rotate(rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 ViewRotZ = glm::rotate(rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
	View = VTrans * ViewRotX * ViewRotY * ViewRotZ;
}

void Camera::setMiddle(int x, int y) {
	mChange = true;
	mX = x; mY = y;
	cX = 0; cY = 0;
}

void Camera::setCurrent(int x, int y) {
	cX = x; cY = y;
}

void Camera::unsetMiddle() {
	mChange = false;
	cX = 0; cY = 0;
	mX = 0; mY = 0;
}

bool Camera::getMiddleState() {
	return mChange;
}

int Camera::getMiddleX() {
	return mX;
}

int Camera::getMiddleY() {
	return mY;
}

int Camera::getCurrentX() {
	return cX;
}

int Camera::getCurrentY() {
	return cY;
}
