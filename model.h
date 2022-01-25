#pragma once
#include <vector>
#include <string>
#include "allglm.h"

class Model
{
protected:
	std::vector<float> vertices;
	glm::mat4 modelMatrix;


public:
	Model();
	void setVertices(std::vector<float> &vertices);
	void setModelMatrix(glm::mat4 modelMatrix);
	glm::mat4 getModelMatrix();

	void render();
	bool intersects(Model model);
	std::string toString();

};

