#version 450
layout(location=0) in vec3 localPosition;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 TexCoords;

void main () {
	 gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(localPosition, 1.0);
	 TexCoords = localPosition;
}
