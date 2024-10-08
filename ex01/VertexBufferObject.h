
#pragma once
#include <GL/glew.h>
class VertexBufferObject
{
public:
	VertexBufferObject(const float points[], size_t size);
	~VertexBufferObject();
private:
	GLuint id;
};