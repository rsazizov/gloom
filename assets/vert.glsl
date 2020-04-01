#version 330 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec2 inUv;

out vec3 vertColor;
out vec2 vertUv;

uniform mat4 u_model;
uniform mat4 u_viewProjection;

void main() {
  vertColor = inColor;
  vertUv = inUv;

  mat4 mvp = u_viewProjection * u_model;

  gl_Position = mvp * vec4(inPosition, 1);
}
