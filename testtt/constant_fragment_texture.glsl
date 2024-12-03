#version 400
out vec4 fragColor;
uniform vec3 objectColor;


uniform sampler2D textureUnitID;
in vec2 uvc;

void main() {
    vec4 texColor = texture(textureUnitID, uvc);
    fragColor = texColor * vec4(objectColor, 1.0);
}
