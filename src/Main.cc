#include "Level.hh"
#include "Wad.hh"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <stack>
#include <iostream>

#include "RenderSystem.hh"
#include "VertexBuffer.hh"
#include "IndexBuffer.hh"
#include "RenderProgram.hh"
#include "InputSystem.hh"
#include "Camera.hh"

const float DOOM_SCALE = 1 / 100.f;

void genLevelVBO(const Level& level, VertexBuffer& vbo) {
  std::vector<Vertex> verts;

  for (const auto& vertex : level.vertexes) {
    verts.push_back({
        {vertex.x * DOOM_SCALE, 0, vertex.y * DOOM_SCALE},
        {0, 0.25f, 0.75f},
        {0, 0}
    });
  }

  vbo.create(verts.size(), verts.data());
}

bool genSubSector(const Level& level, const Ssector& ssector, IndexBuffer& ibo) {
  std::vector<std::uint16_t> inds;

  if (ssector.nSegs < 3) return false;

  for (int i = 0; i < ssector.nSegs; ++i) {
    int segId = ssector.firstSeg + i;
    const Seg& seg = level.segs[segId];

    inds.push_back(seg.start);
  }

  inds.push_back(inds.front());

  ibo.create(inds.size(), inds.data());

  return true;
}

bool isSsector(short id) {
  /* return id & (1<<16); */
  return false;
}

void traverse(const Level& level, const Node& root, std::vector<Vertex>& verts) {
  verts.push_back({
      {root.x * DOOM_SCALE, 0, root.y * DOOM_SCALE},
      {0, 1, 0},
      {0, 0}
  });

  verts.push_back({
      {(root.x + root.dx) * DOOM_SCALE, 0, (root.y + root.dy) * DOOM_SCALE},
      {0, 1, 0},
      {0, 0}
  });

  if (!isSsector(root.leftChild)) {
    traverse(level, level.nodes[root.leftChild], verts);
  }

  if (!isSsector(root.rightChild)) {
    traverse(level, level.nodes[root.leftChild], verts);
  }
}

void genBisectionLines(const Level& level, VertexBuffer& vbo) {
  // Last node is the root.
  std::vector<Vertex> verts;

  for (const auto& node : level.nodes) {
    verts.push_back({
        {node.x * DOOM_SCALE, 0, node.y * DOOM_SCALE},
        {0, 1, 0},
        {0, 0}
    });

    verts.push_back({
        {(node.x + node.dx) * DOOM_SCALE, 0, (node.y + node.dy) * DOOM_SCALE},
        {0, 1, 0},
        {0, 0}
    });

  }

  vbo.create(verts.size(), verts.data());
}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "Usage: gloom <file.wad>\n";
    return 666;
  }

  const char* file = argv[1];

  Level level;
  Wad wad;

  wad.open(file);

  if (!wad.readLevel("E1M1", level)) {
    wad.close();
    return 666;
  }

  wad.close();

  RenderSystem renderSystem;
  InputSystem inputSystem;
  Camera camera;

  renderSystem.create(640, 480);
  inputSystem.create(renderSystem);

  VertexBuffer vbo;
  genLevelVBO(level, vbo);

  VertexBuffer bisectionVBO;
  genBisectionLines(level, bisectionVBO);

  std::vector<IndexBuffer*> ibos;

  for (const auto& ssector : level.ssectors) {
    IndexBuffer* ibo = new IndexBuffer();
    if (genSubSector(level, ssector, *ibo)) {
      ibos.push_back(ibo);
    }
  }

  RenderProgram program;
  program.loadFromFile("assets/vert.glsl", "assets/frag.glsl");

  float dt = 0;
  float frameStart = glfwGetTime();

  glPointSize(5);

  while (renderSystem.isOpen()) {
    renderSystem.handleEvents();
    camera.handleInput(inputSystem, dt);

    renderSystem.beginFrame();
    renderSystem.setRenderProgram(program);

    program.setUniform("u_model", glm::mat4(1));
    program.setUniform("u_viewProjection", camera.getViewProjection());

    for (auto ibo : ibos) {
      program.setUniform("u_color", glm::vec3(0, 0, 1));
      renderSystem.draw(vbo, *ibo, RenderSystem::TriangleFan);
      program.setUniform("u_color", glm::vec3(1, 0, 0));
      renderSystem.draw(vbo, *ibo, RenderSystem::Points);
    }

    program.setUniform("u_color", glm::vec3(0, 1, 0));
    renderSystem.draw(bisectionVBO, RenderSystem::Lines);

    renderSystem.endFrame();

    dt = glfwGetTime() - frameStart;
    frameStart = glfwGetTime();
  }

  renderSystem.destroy();

  return 0;
}
