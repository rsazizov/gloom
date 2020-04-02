#include "Level.hh"
#include "Wad.hh"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <iostream>

#include "RenderSystem.hh"
#include "VertexBuffer.hh"
#include "IndexBuffer.hh"
#include "RenderProgram.hh"
#include "InputSystem.hh"
#include "Camera.hh"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "Usage: gloom <file.wad>\n";
    return 1;
  }

  const char* file = argv[1];

  Level level;
  Wad wad;

  wad.open(file);

  if (!wad.readLevel("E1M2", level)) {
    wad.close();
    return false;
  }

  wad.close();

  RenderSystem renderSystem;
  InputSystem inputSystem;
  Camera camera;

  renderSystem.create(640, 480);
  inputSystem.create(renderSystem);

  VertexBuffer vbo;
  IndexBuffer ibo;

  std::vector<Vertex> verts;
  for (DVertex dv : level.vertexes) {
    verts.push_back({
      {dv.x / 100.f, 0, dv.y / 100.f},
      {1, 0, 0},
      {0, 0}
    });
  }

  std::vector<std::uint16_t> inds;
  for (auto line : level.linedefs) {
    inds.push_back(line.start);
    inds.push_back(line.end);
  }

  vbo.create(verts.size(), verts.data());
  ibo.create(inds.size(), inds.data());

  RenderProgram program;
  program.loadFromFile("assets/vert.glsl", "assets/frag.glsl");

  float dt = 0;
  float frameStart = glfwGetTime();

  while (renderSystem.isOpen()) {
    renderSystem.handleEvents();
    camera.handleInput(inputSystem, dt);

    renderSystem.beginFrame();
    renderSystem.setRenderProgram(program);

    program.setUniform("u_model", glm::mat4(1));
    program.setUniform("u_viewProjection", camera.getViewProjection());

    renderSystem.draw(vbo, ibo, RenderSystem::Lines);

    renderSystem.endFrame();

    dt = glfwGetTime() - frameStart;
    frameStart = glfwGetTime();
  }

  ibo.destroy();
  vbo.destroy();

  renderSystem.destroy();

  return 0;
}
