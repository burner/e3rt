#include "FontWriter.h"

std::map<std::string, FontWriter::Text> FontWriter::text;
std::map<std::string, FontWriter::Text> FontWriter::tmpText;
Obj* FontWriter::chars[95];

FontWriter::Text::Text(std::string textIn, short rgbIn[3], vec3f posIn, vec3f rotIn, float sizeIn) {
	text = textIn;
	rgb = { rgbIn[0], rgbIn[1], rgbIn[2] };
	pos = posIn;
	rot = rotIn;
	size = sizeIn;
}

void FontWriter::initFontWriter() {
	FontWriter::chars[0] = new Obj("font/a.eob");
}

void FontWriter::setText(std::string key, std::string text, short rgb[3], vec3f pos, vec3f rot, float size) {
	FontWriter::text.insert(std::make_pair(key, FontWriter::Text(text, rgb, pos, rot, size)));
}

void FontWriter::writeOnce(std::string key, std::string text, short rgb[3], vec3f pos, vec3f rot, float size) {
	FontWriter::tmpText.insert(std::make_pair(key, FontWriter::Text(text, rgb, pos, rot, size)));
}


void FontWriter::remove(std::string key) {
	FontWriter::text.erase(key);
}

void FontWriter::render() {
	float angle = 65.0f;
	GLfloat scale = 2.5f;
	glm::mat4 Projection = glm::perspective(45.0f, (GLfloat)1200/(GLfloat)800, 0.1f, 20000.0f);
	glm::mat4 ViewTranslate = glm::translate(0.0f,0.0f,-1.0f);
	glm::mat4 ViewRotateX = glm::rotate(0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 ViewRotateY = glm::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 ViewRotateZ = glm::rotate(0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 Scale = glm::scale(glm::vec3(scale));
	glm::mat4 View =ViewTranslate * ViewRotateX * ViewRotateY * ViewRotateZ * Scale;
	FontWriter::chars[0]->draw((GLfloat*)glm::value_ptr(Projection*View));

	float x = sin(angle)*0.072*scale;
	float y = cos(angle)*0.072*scale;

	//std::cout<<"x "<<x<<" y "<<y<<std::endl;
	
	ViewTranslate = glm::translate(-y,0.0f,-(1.0f+x));
	View =ViewTranslate * ViewRotateX * ViewRotateY * ViewRotateZ*Scale;

	FontWriter::chars[0]->draw((GLfloat*)glm::value_ptr(Projection*View));
}
