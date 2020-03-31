#version 330 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec2 inUv;

out vec3 vertColor;
out vec2 vertUv;

void main() {
  vertColor = inColor;
  vertUv = inUv;

  gl_Position = vec4(inPosition, 1);
}
