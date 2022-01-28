#include "cube.h"

int Cube::currentReadyId;
unsigned int Cube::cubeVAO;

Cube::Cube(std::vector<float>& vertices) : Model() {
	this->setVertices(vertices);
	this->setColor(Color::BLUE);
	this->ID = Cube::currentReadyId;
	this->returning = false;
	this->target = false;
	this->hit = false;
}

//@todo
bool Cube::intersects(Model model) {
	return true;
}

//should update its own color
void Cube::setColor(Color color)
{
	glm::vec4 c;
	switch (color) {
	case Color::RED:
		c = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case Color::BLUE:
		c = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case Color::GREEN:
		c = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case Color::YELLOW:
		c = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
		break;
	default:
		c = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	}

	this->color = c;
}

Color Cube::getColor() {
	if (this->color == glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)) return Color::RED;
	if (this->color == glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)) return Color::BLUE;
	if (this->color == glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)) return Color::GREEN;
	if (this->color == glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)) return Color::YELLOW;
}

void Cube::setMainX(float mainX)
{
	this->setMainCoord(mainX, this->mainY, this->mainZ);
}

float Cube::getMainX()
{
	return mainX;
}

void Cube::setMainY(float mainY) {
	this->setMainCoord(this->mainX, mainY, this->mainZ);
}

float Cube::getMainY() {
	return mainY;
}

void Cube::setMainZ(float mainZ) {
	this->setMainCoord(this->mainX, this->mainY, mainZ);
}

float Cube::getMainZ() {
	return this->mainZ;
}

void Cube::setMainCoord(float x, float y, float z) {

	float prevX = this->mainX, prevY = this->mainY, prevZ = this->mainZ;

	this->mainX = x;
	this->mainY = y;
	this->mainZ = z;
	std::cout << "CUBE::" << this->ID << "::MAINCOORD::\n";
	std::cout << "[\n";
	std::cout << x << ", " << y << ", " << z << "\n";
	std::cout << "]\n";

	glm::vec3 transVec(x - prevX, y - prevY, z - prevZ);
	std::cout << "CUBE::" << this->ID << "::TRANSLATE VEC::\n";
	std::cout << "[\n";
	std::cout << transVec.x << ", " << transVec.y << ", " << transVec.z << "\n";
	std::cout << "]\n";
	//translate model Matrix
	this->modelMatrix = glm::translate(this->modelMatrix, transVec);
	std::cout << "CUBE::ID::" << this->ID << "::MODEL MATRIX::SETMAINCOORD::FUNCTION\n";
	std::cout << "[\n";
	std::cout << "\t" << this->modelMatrix[0].x << " " << this->modelMatrix[0].y << " " << this->modelMatrix[0].z << " " << this->modelMatrix[0].w << "\n";
	std::cout << "\t" << this->modelMatrix[1].x << " " << this->modelMatrix[1].y << " " << this->modelMatrix[1].z << " " << this->modelMatrix[1].w << "\n";
	std::cout << "\t" << this->modelMatrix[2].x << " " << this->modelMatrix[2].y << " " << this->modelMatrix[2].z << " " << this->modelMatrix[2].w << "\n";
	std::cout << "\t" << this->modelMatrix[3].x << " " << this->modelMatrix[3].y << " " << this->modelMatrix[3].z << " " << this->modelMatrix[3].w << "\n";
	std::cout << "]\n";
}

int Cube::getId() {
	return this->ID;
}

glm::vec3 Cube::getCenterCoord()
{
	return glm::vec3(this->mainX, this->mainY, this->mainZ);
}

void Cube::setReturning(bool returning) {
	this->returning = returning;
}

bool Cube::isReturning() {
	return this->returning;
}

bool Cube::isTarget() {
	return this->target;
}

void Cube::hasBeenHit() {
	this->hit = true;
}

bool Cube::wasHit() {
	return this->hit;
}

//@todo
bool Cube::explode() {
	return true;
}

//operators
bool operator== (Cube& lhs, Cube& rhs) {
	if (lhs.ID == rhs.ID) return true;
	return false;
}

void Cube::render(int tick, Shader& ourShader) {
	//if we are exploding, then leaving particles and fade
	std::cout << "RENDERING::CUBE::ID " << this->ID << "\n";
	//draw on screen
	ourShader.setVec3("colorOut", this->color);

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	ourShader.setMat4("projection", projection);
	ourShader.setMat4("view", view);

	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(((this->ID % 2 == 0) ? 1 : -1) * (float)tick + 300.0f), glm::vec3(0.5f, 1.0f, 0.1f));
	ourShader.setMat4("model", this->modelMatrix);

	/*std::cout << "CUBE::ID::" << this->ID << "::MODEL MATRIX::\n";
	std::cout << "[\n";
	std::cout << "\t" << this->modelMatrix[0].x << " " << this->modelMatrix[0].y << " " << this->modelMatrix[0].z << " " << this->modelMatrix[0].w << "\n";
	std::cout << "\t" << this->modelMatrix[1].x << " " << this->modelMatrix[1].y << " " << this->modelMatrix[1].z << " " << this->modelMatrix[1].w << "\n";
	std::cout << "\t" << this->modelMatrix[2].x << " " << this->modelMatrix[2].y << " " << this->modelMatrix[2].z << " " << this->modelMatrix[2].w << "\n";
	std::cout << "\t" << this->modelMatrix[3].x << " " << this->modelMatrix[3].y << " " << this->modelMatrix[3].z << " " << this->modelMatrix[3].w << "\n";
	std::cout << "]\n";*/
	// render the cube
	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}