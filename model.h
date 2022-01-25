#pragma once
#include <vector>
#include <string>

class Model
{
protected:
	std::vector<double> vertices;

public:
	Model();
	void setVertices(std::vector<double> vertices);
	bool intersects(Model model);
	std::string toString();

};

