#version 400
layout(location=0) in vec3 localPosition;
layout(location=1) in vec3 normal;
layout(location = 2) in vec2 uv;

out vec2 uvc;
out vec3 worldNorm;
out vec4 worldPos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec2 tilingFactor;

void main() {
    worldPos = modelMatrix * vec4(localPosition, 1.0);
    
    //(M^{-1})^{T}
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    worldNorm = normalize(normalMatrix * normal);
    
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(localPosition, 1.0);

    uvc = uv * tilingFactor;
}