#ifndef GLOOM_RENDER_SYSTEM_HH
#define GLOOM_RENDER_SYSTEM_HH

#include <any>
#include <glm/glm.hpp>

#include "NonCopyable.hh"

class RenderProgram;
class VertexBuffer;
class IndexBuffer;
class InputSystem;

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

  void setRenderProgram(const RenderProgram& renderProgram);

  void draw(const VertexBuffer& buffer,
      Primitive primitive=Triangles);

  void draw(const VertexBuffer& vbo,
      const IndexBuffer& ibo,
      Primitive primitive=Triangles);
private:
  friend class InputSystem;

  glm::vec3 m_clearColor = glm::vec3(0, 0, 0);
  std::any m_window;
};

#endif
