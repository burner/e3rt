#include "Camera.h"

Camera::Camera(float angle, float near, float far, int width, int height) {
	Proj = glm::perspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);
}

void Camera::placeCam() {
	glm::mat4 VTrans = glm::translate(pos.x, pos.y, pos.z);
	glm::mat4 ViewRotX = glm::rotate(rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 ViewRotY = glm::rotate(rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 ViewRotZ = glm::rotate(rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
	View = VTrans * ViewRotX * ViewRotY * ViewRotZ;
}
