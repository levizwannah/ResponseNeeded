#pragma once
#include "allglm.h"
#include "constants.h"
#include "model.h"
class Cube: public Model
{
	glm::vec4 color;
	double mainX, mainY, mainZ;
	int ID;

public:
	static int currentReadyId;

	Cube(std::vector<float>& vertices);
	bool intersects(Model model);
	void setColor(Color color);
	void setMainX(double mainX);
	double getMainX();
	void setMainY(double mainY);
	double getMainY();
	void setMainZ(double mainZ);
	double getMainZ();
	void setMainCoord(double x, double y, double z);
	int getId();
	bool explode();

	//operators definition
	friend bool operator== (Cube& lhs, Cube& rhs);
};

