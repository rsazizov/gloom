#include "RenderSystem.hh"
#include "VertexBuffer.hh"
#include <GL/glew.h>
#include "RenderProgram.hh"

int main() {
  RenderSystem renderSystem;

  renderSystem.create(640, 480);

  RenderProgram prog;
  prog.loadFromFile("assets/vert.glsl", "assets/frag.glsl");

  Vertex verts[] = {
    {glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec2(0, 0)},
    {glm::vec3(1, 1, 0), glm::vec3(0, 1, 0), glm::vec2(0, 0)},
    {glm::vec3(0, 1, 0), glm::vec3(0, 0, 1), glm::vec2(0, 0)}
  };

  Vertex verts2[] = {
    {glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec2(0, 0)},
    {glm::vec3(-1, -1, 0), glm::vec3(0, 0, 1), glm::vec2(0, 0)},
  };

  VertexBuffer buff;
  buff.create(3, verts);

  VertexBuffer buff2;
  buff2.create(2, verts2);

  while (renderSystem.isOpen()) {
    renderSystem.handleEvents();

    renderSystem.beginFrame();

    renderSystem.draw(buff2, prog, RenderSystem::Lines);
    renderSystem.draw(buff, prog);

    renderSystem.endFrame();
  }

  buff.destroy();
  renderSystem.destroy();

  return 0;
}
