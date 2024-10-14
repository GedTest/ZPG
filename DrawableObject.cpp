#include "DrawableObject.h"
#include "Transform.h"
#include "ComposedTransform.h"
#include <glm/vec3.hpp>


float DrawableObject::random(float limit) {
	return (rand() / (RAND_MAX * 1.0f)) * limit;
}

DrawableObject::DrawableObject(ShaderProgram* shaderProgram, ZPG::Model* model, int startVertex, int vertexCount)
{
	this->model = model;
	this->shaderProgram = shaderProgram;
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

	GLint idModelTransform = this->shaderProgram->getUniformLocation("modelMatrix");
	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &this->transform->getTransformMatrix()[0][0]);
					// location,     count, transpose, *value

	this->model->draw(this->startVertex, this->vertexCount);
	return;
}

void DrawableObject::move(const glm::vec3& offset)
{
	Transform* newTransform = new Transform();
	newTransform->translate(offset);
	this->transform->addTransform(newTransform);
}

void DrawableObject::rotate(float angle, const glm::vec3& axis)
{
	Transform* newTransform = new Transform();
	newTransform->rotate(angle, axis);
	this->transform->addTransform(newTransform);
}

void DrawableObject::scale(const glm::vec3& factor)
{
	Transform* newTransform = new Transform();
	newTransform->scale(factor);
	this->transform->addTransform(newTransform);
}

void DrawableObject::randomTransform() {
	float angle = random(360);
	this->rotate(glm::radians(angle), glm::vec3(0, 1, 0));

	float scaleFactor = random(0.5);
	this->scale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));

	int sign = random(1) > 0.5 ? -1 : 1;
	float x = sign * random(2);
	float y = sign * random(2);
	this->move(glm::vec3(x, y, 0));
}
