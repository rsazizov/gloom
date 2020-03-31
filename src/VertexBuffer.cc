#include "VertexBuffer.hh"

#include <GL/glew.h>
#include <cstddef>
#include <cstring>

VertexBuffer::VertexBuffer() {
}

VertexBuffer::~VertexBuffer() {
}

bool VertexBuffer::create(std::size_t nVertices, const Vertex* data) {
  m_nVertices = nVertices;

  std::size_t size = nVertices * sizeof(Vertex);

  glGenBuffers(1, &m_id);
  glBindBuffer(GL_ARRAY_BUFFER, m_id);
  glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);

  void* buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
  std::memcpy(buffer, data, size);

  glUnmapBuffer(GL_ARRAY_BUFFER);
  buffer = nullptr;

  return true;
}

void VertexBuffer::destroy() {
  glDeleteBuffers(1, &m_id);
  m_id = 0;
}

std::size_t VertexBuffer::getVerticesCount() const {
  return m_nVertices;
}
