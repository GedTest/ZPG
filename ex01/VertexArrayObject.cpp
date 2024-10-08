#include "VertexArrayObject.h"
#include <stdlib.h>
VertexArrayObject::VertexArrayObject()
{
	this->id = 0;
	glGenVertexArrays(1, &this->id); //generate the VAO
	glBindVertexArray(this->id);
}
void VertexArrayObject::enableAttribute()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}
void VertexArrayObject::bindBuffer() const
{
	glBindVertexArray(this->id);
}
VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &this->id);
}