
#pragma once
#include <GL/glew.h>
#include "VertexBufferObject.h"
class VertexArrayObject {
public:
	VertexArrayObject();
	void enableAttribute();
	void bindBuffer() const;
	~VertexArrayObject();
private:
	GLuint id;
};