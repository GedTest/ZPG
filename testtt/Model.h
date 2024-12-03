#pragma once
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "AbstractModel.h"


namespace ZPG {
	class Model : public AbstractModel
	{
	protected:
		VertexBufferObject* vbo;
		VertexArrayObject* vao;
		Material* material;

	public:
		Model(const float points[], int count, Material* material);
		virtual ~Model() override;

		Material* getMaterial() const override;
		virtual Texture* getTexture() const override;

		void draw() const override;
	};
}
