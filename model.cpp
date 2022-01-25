#include "model.h"

Model::Model()
{
}

void Model::setVertices(std::vector<float> &vertices)
{
	this->vertices = vertices;
}

bool Model::intersects(Model model)
{
	return false;
}

void Model::setModelMatrix(glm::mat4 modelMatrix) {
	this->modelMatrix = modelMatrix;
}

glm::mat4 Model::getModelMatrix() {
	return this->modelMatrix;
}

std::string Model::toString() {
	std::string output = "";
	for (int i = 0; i < vertices.size(); i++ ) {
		output += vertices[i];
		output += ", ";
	}
	return output;
}
