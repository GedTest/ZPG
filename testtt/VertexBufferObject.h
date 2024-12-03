#pragma once
#include <GL/glew.h>


class VertexBufferObject
{
private:
	GLuint id;

public:
	VertexBufferObject(const float points[], size_t size);
	~VertexBufferObject();
};
