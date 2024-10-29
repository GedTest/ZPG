#pragma once
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"


namespace ZPG {
	class Model
	{
	private:
		VertexBufferObject* vbo;
		VertexArrayObject* vao;

	public:
		Model(const float points[], size_t count);
		~Model();

		void draw(int start, int count) const;
	};
}
