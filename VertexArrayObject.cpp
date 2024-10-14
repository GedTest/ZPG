#include "VertexArrayObject.h"


VertexArrayObject::VertexArrayObject()
{
	this->id = 0;
	glGenVertexArrays(1, &this->id); //generate the VAO
	glBindVertexArray(this->id);
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &this->id);
}

void VertexArrayObject::enableAttribute()
{
	glEnableVertexAttribArray(0);	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);

	glEnableVertexAttribArray(1);	// normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	return;
}

void VertexArrayObject::bindBuffer() const
{
	glBindVertexArray(this->id);
	return;
}
