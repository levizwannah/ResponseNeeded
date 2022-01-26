#pragma once
#include "allglm.h"
#include "constants.h"
#include "model.h"
class Cube: public Model
{
	glm::vec4 color;
	float mainX, mainY, mainZ;
	int ID;
	bool returning, target, hit;

public:
	static int currentReadyId;

	Cube(std::vector<float>& vertices);
	bool intersects(Model model);
	void setColor(Color color);
	Color getColor();
	void setMainX(float mainX);
	float getMainX();
	void setMainY(float mainY);
	float getMainY();
	void setMainZ(float mainZ);
	float getMainZ();

	//will update the model matrix based on the new center and the previous center
	void setMainCoord(float x, float y, float z);
	glm::vec3 getCenterCoord();
	int getId();
	bool explode();
	void setReturning(bool returning);
	bool isReturning();
	void makeTarget(bool isTarget);
	bool isTarget();
	void hasBeenHit();
	bool wasHit();

	//operators definition
	friend bool operator== (Cube& lhs, Cube& rhs);
};

