#include "Model.h"


namespace ZPG {
	Model::Model(const float points[], size_t count)
	{
		this->vbo = new VertexBufferObject(points, count);
		this->vao = new VertexArrayObject();
		this->vao->enableAttribute();
	}

	Model::~Model()
	{
		delete this->vbo;
		delete this->vao;
	}

	void Model::draw(int start, int count) const
	{	
		this->vao->bindBuffer();
		glDrawArrays(GL_TRIANGLES, start, count);
		return;
	}
}
