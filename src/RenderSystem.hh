#ifndef GLOOM_RENDER_SYSTEM_HH
#define GLOOM_RENDER_SYSTEM_HH

#include <any>
#include <glm/glm.hpp>

#include "NonCopyable.hh"

class RenderProgram;
class VertexBuffer;

class RenderSystem : private NonCopyable {
public:
  enum Primitive {
    Points,
    Lines,
    Triangles
  };

  RenderSystem();
  ~RenderSystem();

  bool create(int width, int height, const char* title="Gloom");
  void destroy();

  bool isOpen() const;
  void handleEvents();

  int getWidth() const;
  int getHeight() const;
  glm::vec2 getSize() const;

  void setClearColor(const glm::vec3& color);
  const glm::vec3& getClearColor() const;

  void beginFrame() const;
  void endFrame() const;

  void draw(const VertexBuffer& buffer,
      const RenderProgram& program,
      Primitive primitive=Triangles);
private:
  glm::vec3 m_clearColor = glm::vec3(0, 0, 0);
  std::any m_window;
};

#endif
