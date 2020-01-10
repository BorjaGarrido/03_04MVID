#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;

out vec3 myColor;

out vec3 myPos;

uniform vec3 changePos;

void main() {
    myColor = aColor;
    myPos = aPos;
    gl_Position = vec4(aPos, 1.0);
}