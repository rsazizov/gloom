#ifndef GLOOM_RENDER_PROGRAM_HH
#define GLOOM_RENDER_PROGRAM_HH

#include "NonCopyable.hh"
#include <cstdint>
#include <map>

#include <glm/glm.hpp>

class RenderSystem;

class RenderProgram : private NonCopyable {
public:
  RenderProgram();
  ~RenderProgram();

  bool loadFromFile(const char* vert, const char* frag);
  bool loadFromSource(const char* vert, const char* frag);

  bool setUniform(const char* name, const glm::mat4& v);

  void destroy();

  bool setUniform(const char* name, float v);
  bool setUniform(const char* name, int v);

  bool setUniform(const char* name, const glm::vec2& v);
  bool setUniform(const char* name, const glm::vec3& v);
  bool setUniform(const char* name, const glm::vec4& v);

private:
  friend class RenderSystem;

  std::uint32_t getUniformLocation(const char* name);

  std::uint32_t m_vertId = 0;
  std::uint32_t m_fragId = 0;
  std::uint32_t m_id = 0;
};

#endif
