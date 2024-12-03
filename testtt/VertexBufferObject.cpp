#include "VertexBufferObject.h"


VertexBufferObject::VertexBufferObject(const float points[], size_t size)
{
	this->id = 0;
	glGenBuffers(1, &this->id); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->id);
	glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);
}

VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &id);
}
