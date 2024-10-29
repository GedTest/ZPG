#version 400
layout(location=0) in vec3 localPosition;
layout(location=1) in vec3 normal;

out vec4 worldPos;
out vec3 worldNorm;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
    worldPos = modelMatrix * vec4(localPosition, 1.0);
    
    //(M^{-1})^{T}
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    worldNorm = normalMatrix * normal;
    
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(localPosition, 1.0);
}