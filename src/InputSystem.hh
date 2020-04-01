#ifndef GLOOM_INPUT_SYSTEM_HH
#define GLOOM_INPUT_SYSTEM_HH

#include "NonCopyable.hh"
#include <vector>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class RenderSystem;

class InputSystem : private NonCopyable {
public:
  InputSystem();
  ~InputSystem();

  void create(const RenderSystem& renderSystem);

  bool isKeyDown(int scancode) const;
  glm::vec2 getMousePosition() const;
  glm::vec2 getMouseChange();
private:
  friend class RenderSystem;

  glm::vec2 m_mousePosition = glm::vec2(0.f, 0.f);

  GLFWwindow* m_window;
};


#endif
