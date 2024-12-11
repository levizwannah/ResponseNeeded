#include "cubeMover.h"


CubeMover::CubeMover(float mainX, float mainY, float mainZ, float length, float speed) {
	this->mainX = mainX;
	this->mainY = mainY;
	this->mainZ = mainZ;
	this->length = length;
	this->setSpeed(speed);
	this->dTranslationMat = glm::mat4(1.0f);
	this->interCubeDistance = C_SIDE;
}

//O(N) complexity actually 2 * N;
//might have a performance overhead

int CubeMover::addCube(Cube& cube) {
	for (Cube& c : this->cubes) {
		c.setMainX(c.getMainX() + this->interCubeDistance);
		std::cout << "CUBEMOVER::ADD::CUBE::ID::" << c.getId() << "\n";
		std::cout << "[ " << c.getMainX() << ", " << c.getMainY() << " ]\n";
	}

	cube.setMainCoord(this->mainX, this->mainY, this->mainZ);
	this->cubes.push_back(cube);
	std::cout << "CUBEMOVER::ADD::CUBE::ID::"<<cube.getId()<<"\n";
	std::cout << "[ " << cube.getMainX() << ", " << cube.getMainY() << " ]\n";
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

//time complexed than the remove with the index parameter O(log(N))
bool CubeMover::remove(Cube& cube) {
	int index = this->getIndex(cube);
	if (index < 0) return false;
	this->cubes.erase(this->cubes.begin() + index);

	return true;
}

//Cubes are always sorted, so binary search will work O(log(N)) complexity
int CubeMover::getIndex(Cube& cube) {
	int low = 0, high = this->cubes.size() - 1;
	while (low <= high) {
		int mid = low + (high - low) / 2;

		
		if (this->cubes[mid] == cube) {
			return mid;
		}

		if (this->cubes[mid].getId() < cube.getId()) {
			low = mid + 1;
		}

		if (this->cubes[mid].getId() > cube.getId()) {
			high = mid - 1;
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

void CubeMover::setLength(float length)
{
	this->length = length;
}

float CubeMover::getLength()
{
	return this->length;
}


void CubeMover::moveAndCheck(int tick, Player& currentPlayer)
{
	if (!this->isMoving()) return;

	float mvDistance = this->speed * this->getLength();
	
	int loopUntil = this->cubes.size();

	std::cout << "CUBE_MOVER::MOVEANDCHECK::CURRENT DATA\n--START--\n";
	std::cout << "\t" << "Tick: " << tick << "\n";
	std::cout << "\t" << "MV-DISTANCE: " << mvDistance << "\n";
	std::cout << "--END--\n";

	for (int i = 0; i < loopUntil;) {

		Cube& cube = this->cubes[i];

		//remove cubes that have reached the end of revolution
		if (cube.getCenterCoord().x >= this->getEndCoord().x && cube.isReturning()) {

			//cube checks if it was one of the target cubes
			if (cube.isTarget() && !cube.wasHit()) {
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

		cube.setMainX(cube.getMainX() + mvDistance);

		std::cout << "CUBE_MOVER::MOVEANDCHECK::NEWCOORD::CUBE::" << cube.getId() << "\n--START--\n";
		std::cout << "\t" << "NEW::X: " << cube.getMainX() << "\n";
		std::cout << "--END--\n";

		cube.setReturning(true);
		i++;
	}
	
}


void CubeMover::setEndCoord(float x, float y, float z)
{
	this->endX = x;
	this->endY = y;
	this->endZ = z;
}

glm::vec3 CubeMover::getEndCoord()
{
	return glm::vec3(this->endX, this->endY, this->endZ);
}
