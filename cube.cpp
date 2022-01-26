#include "cube.h"

Cube::Cube(std::vector<float>& vertices) : Model() {
	this->setVertices(vertices);
	this->setColor(Color::BLUE);
	this->ID = Cube::currentReadyId;
	this->returning = false;
	this->target = false;
	this->hit = false;
}

//@todo
bool Cube::intersects(Model model) {
	return true;
}

//should update its own color
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

Color Cube::getColor() {
	if (this->color == glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)) return Color::RED;
	if (this->color == glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)) return Color::BLUE;
	if (this->color == glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)) return Color::GREEN;
	if (this->color == glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)) return Color::YELLOW;
}

void Cube::setMainX(float mainX)
{
	this->setMainCoord(mainX, this->mainY, this->mainZ);
}

float Cube::getMainX()
{
	return mainX;
}

void Cube::setMainY(float mainY) {
	this->setMainCoord(this->mainX, mainY, this->mainZ);
}

float Cube::getMainY() {
	return mainY;
}

void Cube::setMainZ(float mainZ) {
	this->setMainCoord(this->mainX, this->mainY, mainZ);
}

float Cube::getMainZ() {
	return this->mainZ;
}

void Cube::setMainCoord(float x, float y, float z) {

	float prevX = this->mainX, prevY = this->mainY, prevZ = this->mainZ;

	this->mainX = x;
	this->mainY = y;
	this->mainZ = z;

	glm::vec3 transVec(x - prevX, y - prevY, z - prevZ);
	//translate model Matrix
	this->modelMatrix = glm::translate(this->modelMatrix, transVec);
}

int Cube::getId() {
	return this->ID;
}

glm::vec3 Cube::getCenterCoord()
{
	return glm::vec3(this->mainX, this->mainY, this->mainZ);
}

void Cube::setReturning(bool returning) {
	this->returning = returning;
}

bool Cube::isReturning() {
	return this->returning;
}

void Cube::hasBeenHit() {
	this->hit = true;
}

bool Cube::wasHit() {
	return this->hit;
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