#pragma once
#include "AbstractTexture.h"


class CubemapTexture : public AbstractTexture {
private:
	GLuint textureID;
	const GLuint SKYBOX_TEXTURE_UNIT = 0;

public:
	CubemapTexture(const vector<string>& faces);
	~CubemapTexture() override;

	void bind(GLenum textureUnit=-1) const override;
	void unbind() const override;

	GLuint getAssignedUnit() const override { return SKYBOX_TEXTURE_UNIT; }
};
