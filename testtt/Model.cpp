#include "Model.h"


namespace ZPG {
	Model::Model(const float points[], int count, Material* material)
	{
		this->vbo = new VertexBufferObject(points, count);
		this->vao = new VertexArrayObject();
		this->vao->enableAttribute(2);
		this->material = material;

		this->vertexCount = count / sizeof(float) / 6;
	}

	Model::~Model()
	{
		delete this->vbo;
		delete this->vao;
	}

	Material* Model::getMaterial() const {
		return this->material;
	}

	Texture* Model::getTexture() const {
		return nullptr;
	}

	void Model::draw() const
	{	
		this->vao->bindBuffer();
		glDrawArrays(GL_TRIANGLES, 0, this->vertexCount);
		return;
	}
}
