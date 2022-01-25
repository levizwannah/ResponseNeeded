#include "model.h"

Model::Model()
{
}

void Model::setVertices(std::vector<double> vertices)
{
	this->vertices = vertices;
}

bool Model::intersects(Model model)
{
	return false;
}

std::string Model::toString() {
	std::string output = "";
	for (int i = 0; i < vertices.size(); i++ ) {
		output += vertices[i];
		output += ", ";
	}
	return output;
}
