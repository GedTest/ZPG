#include "AbstractTexture.h"


// Start from 1 since 0 is reserved for skybox
vector<GLuint> AbstractTexture::textureUnits(AbstractTexture::MAX_TEXTURE_UNITS, 0);
