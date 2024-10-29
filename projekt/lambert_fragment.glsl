#version 400
in vec4 worldPos;
in vec3 worldNorm;

out vec4 fragColor;

uniform vec3 objectColor;
uniform vec3 lightPosition;
uniform vec3 lightColor;

void main() {
    vec3 lightDir = normalize(lightPosition - vec3(worldPos));
    float diff = max(dot(lightDir, normalize(worldNorm)), 0.0);
    
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    vec4 diffuse = diff * vec4(objectColor, 1.0) * vec4(lightColor, 1.0);
    
    fragColor = ambient + diffuse;
}