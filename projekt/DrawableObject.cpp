#include "DrawableObject.h"
#include "Translation.h"
#include "Rotation.h"
#include "Scale.h"
#include "ComposedTransform.h"
#include <glm/vec3.hpp>


float DrawableObject::random(float limit) {
	return (rand() / (RAND_MAX * 1.0f)) * limit;
}

DrawableObject::DrawableObject(ShaderProgram* shaderProgram, ZPG::Model* model, int startVertex, int vertexCount, glm::vec3 color)
{
	this->model = model;
	this->color = color;
	this->shaderProgram = shaderProgram;
	this->shaderProgram->setObjectColor(this->color);
	this->transform = new ComposedTransform();
	this->startVertex = startVertex;
	this->vertexCount = vertexCount;
}

DrawableObject::~DrawableObject()
{
	delete this->transform;
}

void DrawableObject::draw()
{
	this->shaderProgram->setProgram();
	
	this->shaderProgram->setModelMatrix(this->transform->getTransformMatrix());
	this->shaderProgram->setProjectionMatrix();
	this->shaderProgram->setObjectColor(this->color);

	this->model->draw(this->startVertex, this->vertexCount);
	return;
}

void DrawableObject::move(const glm::vec3& offset)
{
	Translation* translation = new Translation(offset);
	this->transform->addTransform(translation);
}

void DrawableObject::rotate(float angle, const glm::vec3& axis)
{
	Rotation* rotation = new Rotation(angle, axis);
	this->transform->addTransform(rotation);
}

void DrawableObject::scale(const glm::vec3& factor)
{
	Scale* scale = new Scale(factor);
	this->transform->addTransform(scale);
}

void DrawableObject::randomTransform() {
	float angle = random(360);
	this->rotate(angle, glm::vec3(0, 1, 0));

	float scaleFactor = random(1.2);
	this->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));

	int sign = random(1) > 0.5 ? -1 : 1;
	float x = sign * random(80);
	float z = sign * random(80);
	this->move(glm::vec3(x, 0, z));
}

void DrawableObject::setShaderType(ShaderProgram::ShaderType type) {
	this->shaderProgram->setType(type);
}
