#version 450

in vec3 TexCoords;
uniform samplerCube skybox;
out vec4 frag_colour;


void main () {
    frag_colour = texture(skybox, TexCoords);
}
