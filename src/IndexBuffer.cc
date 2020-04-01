#include "IndexBuffer.hh"
#include <GL/glew.h>
#include <cstring>

IndexBuffer::IndexBuffer() {
}

IndexBuffer::~IndexBuffer() {
}

bool IndexBuffer::create(size_t nIndices, std::uint16_t* data) {
  m_nIndices = nIndices;
  auto size = nIndices * sizeof(data[0]);

  glGenBuffers(1, &m_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);

  void* buffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
  std::memcpy(buffer, data, size);

  glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
  buffer = nullptr;

  return true;
}

void IndexBuffer::destroy() {
  glDeleteBuffers(1, &m_id);
}

std::size_t IndexBuffer::getIndicesCount() const {
  return m_nIndices;
}
