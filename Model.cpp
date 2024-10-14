#include "Model.h"


namespace ZPG {
	Model::Model(const float points[], size_t count)
	{
		vbo = new VertexBufferObject(points, count);
		vao = new VertexArrayObject();
		vao->enableAttribute();
	}

	Model::~Model()
	{
		delete vbo;
		delete vao;
	}

	void Model::draw(int start, int count) const
	{	
		vao->bindBuffer();
		glDrawArrays(GL_TRIANGLES, start, count);
		return;
	}
}
