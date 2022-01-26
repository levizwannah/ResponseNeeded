#include "cubeMover.h"

CubeMover::CubeMover(float mainX, float mainY, float mainZ, float radius, float speed) {
	this->mainX = mainX;
	this->mainY = mainY;
	this->mainZ = mainZ;
	this->radius = radius;
	this->speed = speed;
	this->generateVertices();
}

int CubeMover::addCube(Cube& cube) {
	for (int i = 0; i < this->cubes.size(); i++) {
		if (cube == this->cubes[i]) {

			return i;
		}
	}

	this->cubes.push_back(cube);
	return this->cubes.size() - 1;
}

//@todo
bool CubeMover::start() {
	this->moving = true;
	return true;
}

//@todo
bool CubeMover::stop() {
	this->moving = false;
	return true;
}

/*
* This method will translate the cube to an off viewport position
* 
*/
bool CubeMover::remove(int index) {
	if (this->cubes.empty() || index < 0 || index > this->cubes.size() - 1) return false;
	this->cubes.erase(this->cubes.begin() + index);
	return true;
}

//time complexed than the remove with the index parameter
bool CubeMover::remove(Cube& cube) {
	for (int i = 0; i < this->cubes.size(); i++) {
		if (this->cubes[i] == cube) {
			this->cubes.erase(this->cubes.begin() + i);
			return true;
		}
	}
	return false;
}

//O(N) complexity
int CubeMover::getIndex(Cube& cube) {
	for (int i = 0; i < this->cubes.size(); i++) {
		if (this->cubes[i] == cube) {
			return i;
		}
	}
	return -1;
}

//this speed will be multiplied by the revolution per second R_SPEED
void CubeMover::setSpeed(float speed) {
	this->speed = R_SPEED * speed;
}

float CubeMover::getSpeed() {
	return this->speed;
}

bool CubeMover::isMoving() {
	return this->moving;
}

std::vector<Cube>& CubeMover::getMovingCubes() {
	return this->cubes;
}

void CubeMover::setMainX(float mainX) {
	this->mainX = mainX;
}

float CubeMover::getMainX() {
	return this->mainX;
}

void CubeMover::setMainY(float mainY) {
	this->mainY = mainY;
}

float CubeMover::getMainY() {
	return this->mainY;
}

void CubeMover::setMainZ(float mainZ)
{
	this->mainZ = mainZ;
}

float CubeMover::getMainZ()
{
	return this->mainZ;
}

void CubeMover::setRadius(float radius)
{
	this->radius = radius;
}

float CubeMover::getRadius()
{
	return this->radius;
}

void CubeMover::generateVertices() {
	for (int i = 0; i < 360; i++) {
		float x = (this->radius * cos(i)) + this->mainX;
		float y = (this->radius * sin(y)) + this->mainY;
		float z = 0.0f;
		this->vertices.push_back(x);
		this->vertices.push_back(y);
		this->vertices.push_back(z);
	}
}

std::vector<float> CubeMover::getVertices() {
	return this->vertices;
}
