#ifndef GLOOM_INDEX_BUFFER_HH
#define GLOOM_INDEX_BUFFER_HH

#include "NonCopyable.hh"
#include <cstddef>
#include <cstdint>

class RenderSystem;

class IndexBuffer : private NonCopyable {
public:
  IndexBuffer();
  ~IndexBuffer();

  bool create(size_t nIndices, std::uint16_t* data);
  void destroy();

  std::size_t getIndicesCount() const;
private:
  friend class RenderSystem;

  std::size_t m_nIndices;
  std::uint32_t m_id = 0;
};

#endif
