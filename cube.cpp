#include "cube.h"

Cube::Cube(std::vector<float> vertices) : Model() {
	this->setVertices(vertices);
	this->color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

//@todo
bool Cube::intersects(Model model) {
	return true;
}

//@should update its own color
void Cube::setColor(glm::vec4 color)
{
	this->color = color;
}

void Cube::setMainX(double mainX)
{
	this->mainX = mainX;
}

double Cube::getMainX()
{
	return mainX;
}

void Cube::setMainY(double mainY) {
	this->mainY = mainY;
}

double Cube::getMainY() {
	return mainY;
}

void Cube::setMainZ(double mainZ) {
	this->mainZ = mainZ;
}

double Cube::getMainZ() {
	return this->mainZ;
}

void Cube::setMainCoord(double x, double y, double z) {
	this->mainX = x;
	this->mainY = y;
	this->mainZ = z;
}

int Cube::getId() {
	return this->ID;
}

//@todo
bool Cube::explode() {
	return true;
}