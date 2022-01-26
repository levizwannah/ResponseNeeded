#include "model.h"

Model::Model()
{
	this->modelMatrix = glm::mat4(1.0f);
}

void Model::setVertices(std::vector<float> &vertices)
{
	this->vertices = vertices;
}

bool Model::intersects(Model& model)
{
	glm::mat3x2 bBox = model.getBoundingBox();

	if (
		(bBox[0].x <= this->boundingBox[0].y && bBox[0].y >= this->boundingBox[0].x) &&
		(bBox[1].x <= this->boundingBox[1].y && bBox[1].y >= this->boundingBox[1].x) &&
		(bBox[2].x <= this->boundingBox[2].y && bBox[2].y >= this->boundingBox[2].x)
		) {
		return true;
	}
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

void Model::calculateBoundingBox() {
	if (this->vertices.size() < 3) return;

	float minX = this->vertices[0], maxX = minX, minY = this->vertices[1], maxY = minY, minZ = this->vertices[2], maxZ = minZ;
	for (int i = 0; i < this->vertices.size(); i += 3) {
		glm::vec4 vec(this->vertices[i], this->vertices[i + 1], this->vertices[i + 3], 1.0f);
		vec = this->modelMatrix * vec;

		if (minX > vec.x) minX = vec.x;
		if (maxX < vec.x) maxX = vec.x;
		if (minY > vec.y) minY = vec.y;
		if (maxY < vec.y) maxY = vec.y;
		if (minZ > vec.z) minZ = vec.z;
		if (maxZ < vec.z) maxZ = vec.z;
	}

	this->boundingBox = glm::mat3x2(minX, maxX, minY, maxY, minZ, maxZ);
}

glm::mat3x2 Model::getBoundingBox() {
	return this->boundingBox;
}
