#include "InputSystem.hh"
#include "RenderSystem.hh"

#include <GLFW/glfw3.h>
#include <limits>
#include <functional>

#include <iostream>

using namespace std::placeholders;

InputSystem::InputSystem() {
}

InputSystem::~InputSystem() {
}

void InputSystem::create(const RenderSystem& renderSystem) {
  m_window = std::any_cast<GLFWwindow*>(renderSystem.m_window);

  glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
  glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  m_mousePosition = getMousePosition();
}

bool InputSystem::isKeyDown(int scancode) const {
  return glfwGetKey(m_window, scancode);
}

glm::vec2 InputSystem::getMousePosition() const {
  double x, y;
  glfwGetCursorPos(m_window, &x, &y);

  return {(float) x, (float) y};
}

glm::vec2 InputSystem::getMouseChange() {
  glm::vec2 change = m_mousePosition - getMousePosition();
  m_mousePosition = getMousePosition();

  return change;
}

