#pragma once
#include "model.h"
#include "cube.h"
#include <vector>

class CubeMover : public Model
{
	std::vector<Cube> cubes;
	std::vector<float> vertices;
	bool moving;
	float speed;
	float mainX;
	float mainY;
	
public:
	CubeMover(float mainX, float mainY, float speed);
	int addCube(Cube& cube);
	bool start();
	bool stop();
	bool remove(int index);
	bool remove(Cube& cube);
	int getIndex(Cube& cube);
	void setSpeed(float speed);
	float getSpeed();
	bool isMoving();
	std::vector<Cube> getMovingCubes();
	void setMainX(float mainX);
	float getMainX();
	void setMainY(float mainY);
	float getMainY();
	void generateVertices();
	std::vector<float> getVertices();

	
};

