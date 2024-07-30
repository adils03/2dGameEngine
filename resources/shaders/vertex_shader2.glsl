#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTex;

out vec4 color;
out vec2 texCoord;
out vec2 fragPos;

uniform mat4 transform;
uniform mat4 viewProjection;

void main() {
    vec4 worldPos = transform * vec4(aPos, 0.0, 1.0);
    gl_Position = viewProjection * worldPos;

    color = aColor;
    texCoord = aTex;
    fragPos = worldPos.xy;
}
