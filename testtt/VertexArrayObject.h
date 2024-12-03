#pragma once
#include <GL/glew.h>
#include "VertexBufferObject.h"


class VertexArrayObject {
private:
	GLuint id;

public:
	VertexArrayObject();
	~VertexArrayObject();

	void enableAttribute(int count);
	void bindBuffer() const;
	void unbindBuffer() const;
};
