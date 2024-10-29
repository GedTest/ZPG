#version 400
in vec4 worldPos;
in vec3 worldNorm;

out vec4 fragColor;

uniform vec3 objectColor;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 viewPosition;

void main() {
    vec3 lightDir = normalize(lightPosition - vec3(worldPos));
    vec3 viewDir = normalize(viewPosition - vec3(worldPos));
    vec3 norm = normalize(worldNorm);
    vec3 reflectDir = reflect(-lightDir, norm);

    float diff = max(dot(lightDir, normalize(worldNorm)), 0.0);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    vec4 diffuse = diff * vec4(objectColor, 1.0) * vec4(lightColor, 1.0);
    vec4 specular = spec * vec4(lightColor, 1.0);
    
    fragColor = ambient + diffuse + specular;
}