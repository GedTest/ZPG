#include "DrawableObject.h"
#include "RandomTranslation.h"
#include "RandomRotation.h"
#include "RandomScale.h"
#include "Translation.h"
#include "Rotation.h"
#include "Scale.h"
#include "ComposedTransform.h"
#include <glm/vec3.hpp>


DrawableObject::DrawableObject(ShaderProgram* shaderProgram, AbstractModel* model, glm::vec3 color)
{
	this->model = model;
	this->color = color;
	this->shaderProgram = shaderProgram;


	this->texture = this->model->getTexture();
	if (!this->texture) {
		this->shaderProgram->setUseTextureFlag(false);
		this->shaderProgram->setObjectColor(this->color);
	}
	this->transform = new ComposedTransform();
}

DrawableObject::~DrawableObject()
{
	delete this->transform;
}

void DrawableObject::draw()
{
	this->shaderProgram->setModelMatrix(this->transform->getTransformMatrix());
	this->shaderProgram->setProjectionMatrix();
	
	if (this->texture) {
		this->shaderProgram->setUseTextureFlag(true);
		this->shaderProgram->setTexture(this->texture);
	}

	this->shaderProgram->setObjectColor(this->color);
		
	if (!this->model) { return; }
	this->shaderProgram->setMaterialProperties(this->model->getMaterial());

	this->shaderProgram->setProgram();
	this->model->draw();
	this->shaderProgram->resetProgram();
	return;
}

void DrawableObject::move(const glm::vec3& offset)
{
	Translation* translation = new Translation(offset);
	this->transform->addTransform(translation);
	return;
}

void DrawableObject::move(Translation* translation)
{
	this->transform->addTransform(translation);
	return;
}

void DrawableObject::rotate(float angle, const glm::vec3& axis)
{
	Rotation* rotation = new Rotation(angle, axis);
	this->transform->addTransform(rotation);
	return;
}

void DrawableObject::rotate(Rotation* rotation)
{
	this->transform->addTransform(rotation);
	return;
}

void DrawableObject::rotateAroundPoint(Rotation* rotation, const glm::vec3& point) {
	// Translate to rotaion point
	Translation* translateToOrigin = new Translation(-point);
	this->move(translateToOrigin);

	// Rotate along the axis
	this->rotate(rotation);

	// Translate back to original place
	Translation* translateBack = new Translation(point);
	this->move(translateBack);

	return;
}

void DrawableObject::scale(const glm::vec3& factor)
{
	Scale* scale = new Scale(factor);
	this->transform->addTransform(scale);
	return;
}

void DrawableObject::scale(Scale* scale)
{
	this->transform->addTransform(scale);
	return;
}

void DrawableObject::randomTransform() {
	RandomRotation* randomRotation = new RandomRotation(360, false, true, false);
	this->rotate(randomRotation);

	RandomScale* randomScale = new RandomScale(1.2f);
	this->scale(randomScale);

	RandomTranslation* randomTranslation = new RandomTranslation(true, false);
	this->move(randomTranslation);
	return;
}

void DrawableObject::setShaderType(ShaderProgram::ShaderType type) {
	this->shaderProgram->setType(type);
	return;
}
