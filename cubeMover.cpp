#include "cubeMover.h"


CubeMover::CubeMover(float mainX, float mainY, float mainZ, float radius, float speed) {
	this->mainX = mainX;
	this->mainY = mainY;
	this->mainZ = mainZ;
	this->radius = radius;
	this->speed = speed;
	this->generateVertices();
	this->dTranslationMat = glm::mat4(1.0f);
	this->interCubeDistance = C_SIDE + 1;
}

//O(N) complexity actually 2 * N;
//might have a performance overhead

int CubeMover::addCube(Cube& cube) {
	for (int i = 0; i < this->cubes.size(); i++) {
		if (cube == this->cubes[i]) {
			return i;
		}
	}

	this->cubes.push_back(cube);

	//update the mainCoordinates of the cube;
	float d = this->interCubeDistance;
	for (Cube cube : this->cubes) {
		float theta2 = 2 * sin(d / 2 * this->radius);
		float theta1 = std::max(acos((cube.getMainX() - this->mainX) / this->radius), asin((cube.getMainY() - this->mainY) / this->radius));
		float finalTheta = theta1 + theta2;
		float newMainX = this->radius * cos(finalTheta) + this->mainX;
		float newMainY = this->radius * sin(finalTheta) + this->mainY;
		cube.setMainCoord(newMainX, newMainY, this->mainZ);
	}
	
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
		float x = (this->radius * cos(i * 180 / PI)) + this->mainX;
		float y = (this->radius * sin(i * 180 / PI)) + this->mainY;
		float z = 0.0f;
		this->vertices.push_back(x);
		this->vertices.push_back(y);
		this->vertices.push_back(z);
	}
}

std::vector<float> CubeMover::getVertices() {
	return this->vertices;
}

void CubeMover::moveAndCheck(int tick, Player& currentPlayer)
{
	if (!this->isMoving()) return;

	float circumference = this->getCircumference();
	float seconds = tick / 1000.0f;
	float mvDistance = this->speed * R_SPEED * circumference * seconds;
	float arcAngle = mvDistance / this->radius;

	int loopUntil = this->cubes.size();

	for (int i = 0; i < loopUntil;) {

		Cube* cube = &this->cubes[i];

		//remove cubes that have reached the end of revolution
		if (cube->getCenterCoord() == this->getRevEndCoord() && cube->isReturning()) {

			//cube checks if it was one of the target cubes
			if (cube->isTarget() && !cube->wasHit()) {
				currentPlayer.score--;
				Player::consecutiveMiss += 1;
				if (Player::consecutiveMiss % Player::maxConsecutiveMiss == 0) {
					Player::consecutiveMiss = 0;
					currentPlayer.life--;
				}
			}

			this->remove(i);
			loopUntil = this->cubes.size();
			continue;
		}

		float diffAngle = std::max(
			asin((cube->getMainY() - this->mainY) / this->radius ),
			acos ((cube->getMainX() - this->mainX) / this->radius )
		);

		float finalAngle = diffAngle + arcAngle;
		float newMainX = this->radius * cos(finalAngle) + this->mainX;
		float newMainY = this->radius * sin(finalAngle) + this->mainY;

		cube->setMainCoord(newMainX, newMainY, this->mainZ);
		cube->setReturning(true);

		i++;
	}
	
	
}

float CubeMover::getCircumference()
{
	return 2 * PI * this->radius;
}

void CubeMover::setRevEndCoord(float x, float y, float z)
{
	this->endX = x;
	this->endY = y;
	this->endZ = z;
}

glm::vec3 CubeMover::getRevEndCoord()
{
	return glm::vec3(this->endX, this->endY, this->endZ);
}
