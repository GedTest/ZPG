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

void VertexArrayObject::enableAttribute(int count)
{
	int skipValues = 3;
	if (count == 2) { skipValues = 6; }
	if (count == 3) { skipValues = 8; }
	if (count == 4) { skipValues = 11; }

	glEnableVertexAttribArray(0);	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, skipValues * sizeof(float), (GLvoid*)0);

	if (count >= 2) {
		glEnableVertexAttribArray(1);	// normal
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, skipValues * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	}

	if (count >= 3) {
		glEnableVertexAttribArray(2);	// uv
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, skipValues * sizeof(float), (GLvoid*)(6 * sizeof(float)));
	}

	if (count >= 4) {
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, skipValues * sizeof(float), (GLvoid*)(8 * sizeof(float)));
	}

	return;
}

void VertexArrayObject::bindBuffer() const
{
	glBindVertexArray(this->id);
	return;
}

void VertexArrayObject::unbindBuffer() const {
	glBindVertexArray(0);
	return;
}
