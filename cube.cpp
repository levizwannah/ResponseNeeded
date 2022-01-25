#include "cube.h"

Cube::Cube(std::vector<float>& vertices) : Model() {
	this->setVertices(vertices);
	this->setColor(Color::BLUE);
	this->ID = Cube::currentReadyId;
}

//@todo
bool Cube::intersects(Model model) {
	return true;
}

//@should update its own color
void Cube::setColor(Color color)
{
	glm::vec4 c;
	switch (color) {
	case Color::RED:
		c = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case Color::BLUE:
		c = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case Color::GREEN:
		c = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case Color::YELLOW:
		c = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
		break;
	default:
		c = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	}

	this->color = c;
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

//operators
bool operator== (Cube& lhs, Cube& rhs) {
	if (lhs.ID == rhs.ID) return true;
	return false;
}