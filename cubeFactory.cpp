#include "cubeFactory.h"


CubeFactory::CubeFactory(glm::mat4& defaultModelMatrix, std::vector<float>& defaultVertices)
{
    this->defaultModelMatrix = defaultModelMatrix;
    this->defaultVertices = defaultVertices;
    this->targetNum = 0;
    this->numCreated = 0;
    Cube::currentReadyId = 0;
}

void CubeFactory::setTargetNum(int targetNum)
{
    this->targetNum = targetNum;
}

int CubeFactory::getTargetNum()
{
    return this->targetNum;
}

void CubeFactory::startProduction()
{
    this->makeCube = true;
    this->numCreated = 0;
}

void CubeFactory::stopProduction() {
    this->makeCube = false;
    this->targetNum = 0;
}

bool CubeFactory::isProducing() {
    return this->makeCube;
}

glm::mat4 CubeFactory::getDefaultModelMat() {
    return this->defaultModelMatrix;
}

std::vector<float> CubeFactory::getDefaultVertices() {
    return this->defaultVertices;
}

void CubeFactory::produce(std::vector<Cube>& cubeInventory)
{
    if (this->isProducing() && this->numCreated == this->targetNum) {
        this->stopProduction();
        return;
    }

    Cube cube(this->defaultVertices);
    cube.setModelMatrix(this->defaultModelMatrix);
    Cube::currentReadyId++;
    cubeInventory.push_back(cube);
    this->numCreated++;
    return;
}

