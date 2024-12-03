#version 400
#define MAX_LIGHTS 100


in vec4 worldPos;
in vec3 worldNorm;
in vec2 uvc;

out vec4 fragColor;

uniform vec3 objectColor;
uniform vec3 viewPosition;
uniform sampler2D textureUnitID;

struct Material {
    vec3 reflectance;
    float shininess;
};

struct Light {
    int type;
    vec3 position;
    vec3 direction;
    vec3 color;
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
    float cutOff;
    float outerCutOff;
};

uniform Material material;
uniform int numLights;
uniform Light lights[MAX_LIGHTS];


float calculateAttenuation(Light light, float distance) {
    return 1.0 / (light.constantAttenuation + 
                  light.linearAttenuation * distance +
                  light.quadraticAttenuation * distance * distance);
}


void main() {
    vec3 norm = normalize(worldNorm);
    vec3 viewDir = normalize(viewPosition - vec3(worldPos));
    
    vec4 result = vec4(objectColor * material.reflectance.x, 1.0); // ambient
    
    for(int i = 0; i < numLights; i++) {
        vec3 lightDir;
        float attenuation = 1.0;
        float spot = 1.0f;
        
        // Point light
        if(lights[i].type == 0) {
            lightDir = normalize(lights[i].position - vec3(worldPos));
            float distance = length(lights[i].position - vec3(worldPos));
            attenuation = calculateAttenuation(lights[i], distance);
        }
        // Directional light
        else if(lights[i].type == 1) {
            lightDir = normalize(-lights[i].direction);
        }
        // Spot light
        else if(lights[i].type == 2) {
            lightDir = normalize(lights[i].position - vec3(worldPos));
            float distance = length(lights[i].position - vec3(worldPos));
            attenuation = calculateAttenuation(lights[i], distance);
            
            spot = dot(normalize(lightDir), -lights[i].direction);
            float alpha = cos(lights[i].outerCutOff);
            float beta = cos(lights[i].cutOff);
            if (spot < alpha) {
                spot = (spot - alpha)/(beta - alpha);
                spot = clamp(spot, 0.0f, 1.0f);
            }
        }

        float diff = max(dot(lightDir, norm), 0.0);
        vec4 diffuse = diff * vec4(objectColor * material.reflectance.y, 1.0) * vec4(lights[i].color, 1.0);

        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);

        // don't draw light from behind object
        // when light is infront of
        if (dot(worldNorm, lightDir) < 0.0) {
            spec = 0.0;
        }

        vec4 specular = spec * vec4(lights[i].color * material.reflectance.z, 1.0);
        
        result += attenuation * spot * (diffuse + specular);
    }

    fragColor = texture(textureUnitID, uvc) * result;
}
