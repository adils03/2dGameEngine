#version 330 core
out vec4 FragColor;

in vec4 color;
in vec2 texCoord;
in vec2 fragPos;

uniform sampler2D tex0;
uniform vec2 lightPos;
uniform vec3 lightColor;
uniform float lightRadius;

void main() {
    float ldistance = length(lightPos - fragPos);
    float attenuation = 1.0 / (1.0 + (ldistance / lightRadius) * (ldistance / lightRadius));
    vec3 lighting = lightColor * attenuation;
    vec4 texColor = texture(tex0, texCoord);
    FragColor = color;
}
