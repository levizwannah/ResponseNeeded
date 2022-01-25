#pragma once
#include <vector>
#include <string>

class Model
{
protected:
	std::vector<float> vertices;

public:
	Model();
	void setVertices(std::vector<float> vertices);
	bool intersects(Model model);
	std::string toString();

};

