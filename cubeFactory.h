#pragma once
#include "allglm.h"
#include "cube.h"
#include "constants.h"
#include <vector>

/*
* Makes the cube and give it its color and initial position. It returns a reference
* to every new cube it makes.
*/
class CubeFactory
{
	bool makeCube;
	int targetNum, numCreated;
	glm::mat4 defaultModelMatrix;
	std::vector<float> defaultVertices;
	
public:

	CubeFactory(glm::mat4& defaultModelMatrix, std::vector<float>& defaultVertices);
	/*
	* Ensure you have set the Target Cube Color
	*/
	void setTargetNum(int targetNum);
	int  getTargetNum();
	void startProduction();
	void stopProduction();
	bool isProducing();
	glm::mat4 getDefaultModelMat();
	std::vector<float> getDefaultVertices();

	//returns a cube in the animation loop
	void produce(std::vector<Cube>& cubeInventory);
};

