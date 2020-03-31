#ifndef GLOOM_RENDER_SYSTEM_HH
#define GLOOM_RENDER_SYSTEM_HH

#include <any>
#include <glm/glm.hpp>

class RenderSystem {
public:
  RenderSystem();
  ~RenderSystem();

  bool create(int width, int height, const char* title="Gloom");
  void destroy();

  bool isOpen() const;
  void handleEvents();

  int getWidth() const;
  int getHeight() const;
  glm::vec2 getSize() const;

private:
  std::any m_window;
};

#endif
