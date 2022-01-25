#include "cubeMover.h"

CubeMover::CubeMover(float mainX, float mainY, float speed) {
	this->mainX = mainX;
	this->mainY = mainY;
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

}

bool CubeMover::remove(Cube& cube) {

}

int CubeMover::getIndex(Cube& cube) {

}

void CubeMover::setSpeed(float speed) {

}

float CubeMover::getSpeed() {

}

bool CubeMover::isMoving() {

}

std::vector<Cube> CubeMover::getMovingCubes() {

}

void CubeMover::setMainX(float mainX) {

}

float CubeMover::getMainX() {

}

void CubeMover::setMainY(float mainY) {

}

float CubeMover::getMainY() {

}

void CubeMover::generateVertices() {

}

std::vector<float> CubeMover::getVertices() {

}
