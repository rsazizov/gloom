#ifndef GLOOM_VERTEX_BUFFER_HH
#define GLOOM_VERTEX_BUFFER_HH

#include <cstddef>
#include <cstdint>
#include <glm/glm.hpp>

#include "NonCopyable.hh"

struct Vertex {
  glm::vec3 position;
  glm::vec3 color;
  glm::vec2 uv;
};

class RenderSystem;

class VertexBuffer : private NonCopyable {
public:
  VertexBuffer();
  ~VertexBuffer();

  bool create(std::size_t nVertices, const Vertex* data);
  void destroy();

  std::size_t getVerticesCount() const;

private:
  friend class RenderSystem;

  std::size_t m_nVertices;
  uint32_t m_id = 0;
};

#endif
