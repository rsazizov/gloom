#ifndef GLOOM_RENDER_PROGRAM_HH
#define GLOOM_RENDER_PROGRAM_HH

#include "NonCopyable.hh"
#include <cstdint>

class RenderSystem;

class RenderProgram : private NonCopyable {
public:
  RenderProgram();
  ~RenderProgram();

  bool loadFromFile(const char* vert, const char* frag);
  bool loadFromSource(const char* vert, const char* frag);

  void destroy();

private:
  friend class RenderSystem;

  std::uint32_t m_vertId = 0;
  std::uint32_t m_fragId = 0;
  std::uint32_t m_id = 0;
};

#endif
