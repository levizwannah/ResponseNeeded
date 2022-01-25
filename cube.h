#pragma once
#include "allglm.h"

#include "model.h"
class Cube: public Model
{
	glm::vec4 color;


	Cube();
	bool intersects(Model model);
	void setColor(glm::vec4 color);
};

