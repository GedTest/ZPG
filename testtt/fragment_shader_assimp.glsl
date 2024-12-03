#version 450

in vec2 uv;

uniform sampler2D textureUnitID;
uniform vec3 objectColor;
uniform bool useTexture = false;

out vec4 frag_color;

void main () {
    if (useTexture) {
        frag_color = texture(textureUnitID, uv);
    }
    else {
        frag_color = vec4(objectColor, 1.0);
    }
}

