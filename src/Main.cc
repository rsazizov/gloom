#include "RenderSystem.hh"
#include "VertexBuffer.hh"
#include <GL/glew.h>
#include "RenderProgram.hh"
#include "IndexBuffer.hh"
#include "InputSystem.hh"
#include "Camera.hh"

#include <GLFW/glfw3.h>
#include <cstdint>
#include <iostream>

int main() {
  RenderSystem renderSystem;

  renderSystem.create(640, 480);

  InputSystem input;
  input.create(renderSystem);

  RenderProgram prog;
  prog.loadFromFile("assets/vert.glsl", "assets/frag.glsl");

  Vertex verts[] = {
    {glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec2(0, 0)},
    {glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec2(0, 0)},
    {glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec2(0, 0)},
    {glm::vec3(1, 1, 0), glm::vec3(0, 0, 1), glm::vec2(0, 0)},
  };

  std::uint16_t indices[] = {
    0, 2, 1, 1, 3, 2
  };

  IndexBuffer ibuff;
  ibuff.create(6, indices);

  VertexBuffer buff;
  buff.create(4, verts);

  glm::mat4 model(1);

  renderSystem.setRenderProgram(prog);

  Camera cam;

  prog.setUniform("u_model", model);

  cam.setPosition(glm::vec3(0, 0, 1));

  float frameStart = (float) glfwGetTime();
  float dt = 0;
  while (renderSystem.isOpen()) {
    prog.setUniform("u_viewProjection", cam.getViewProjection());

    renderSystem.handleEvents();
    cam.handleInput(input, dt);

    renderSystem.beginFrame();

    renderSystem.draw(buff, ibuff);

    renderSystem.endFrame();

    dt = glfwGetTime() - frameStart;
    frameStart = glfwGetTime();
  }

  buff.destroy();
  renderSystem.destroy();

  return 0;
}
