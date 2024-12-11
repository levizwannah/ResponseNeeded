#pragma once
#include "model.h"
#include "cube.h"
#include "allglm.h"
#include <vector>
#include <cmath>
#include "player.h"

class CubeMover : public Model
{
	std::vector<Cube> cubes;
	std::vector<float> vertices;
	glm::mat4 dTranslationMat; //default translation matrix
	bool moving;
	float speed;
	float mainX;
	float mainY;
	float length;
	float mainZ;
	float interCubeDistance;
	float endX;
	float endY;
	float endZ;

public:
	CubeMover(float mainX, float mainY, float mainZ, float length, float speed);
	int addCube(Cube& cube);
	bool start();
	bool stop();
	bool remove(int index);
	bool remove(Cube& cube);
	int getIndex(Cube& cube);
	void setSpeed(float speed);
	float getSpeed();
	bool isMoving();
	std::vector<Cube>& getMovingCubes();
	void setMainX(float mainX);
	float getMainX();
	void setMainY(float mainY);
	float getMainY();
	void setMainZ(float mainZ);
	float getMainZ();
	void setLength(float length);
	float getLength();

	//moves the cube every tick by changing their model based on its translation matrix;
	//tick is the number of milliseconds since last render
	void moveAndCheck(int tick, Player& currentPlayer);
	void setEndCoord(float x, float y, float z);
	glm::vec3 getEndCoord();
};

