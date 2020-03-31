#include "RenderSystem.hh"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


RenderSystem::RenderSystem() {
}

RenderSystem::~RenderSystem() {
}

bool RenderSystem::create(int width, int height, const char* title) {
  glfwInit();

  GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  glfwMakeContextCurrent(window);

  m_window = window;

  return true;
}

void RenderSystem::destroy() {
  glfwMakeContextCurrent(nullptr);
  glfwDestroyWindow(std::any_cast<GLFWwindow*>(m_window));
  glfwTerminate();

  m_window.reset();
}

bool RenderSystem::isOpen() const {
  if (!m_window.has_value()) {
    return false;
  }

  return !glfwWindowShouldClose(std::any_cast<GLFWwindow*>(m_window));
}

void RenderSystem::handleEvents() {
  glfwPollEvents();
}

int RenderSystem::getWidth() const {
  return getSize().x;
}

int RenderSystem::getHeight() const {
  return getSize().y;
}

glm::vec2 RenderSystem::getSize() const {
  int width;
  int height;

  glfwGetWindowSize(std::any_cast<GLFWwindow*>(m_window), &width, &height);

  return { width, height };
}
