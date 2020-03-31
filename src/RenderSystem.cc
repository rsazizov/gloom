#include "RenderSystem.hh"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <map>

#define PAIR(x) {x, #x}

RenderSystem::RenderSystem() {
}

RenderSystem::~RenderSystem() {
}

const char* glEnumToString(GLenum e) {
  std::map<GLenum, const char*> map = {
    PAIR(GL_DEBUG_SOURCE_API),
    PAIR(GL_DEBUG_SOURCE_APPLICATION),
    PAIR(GL_DEBUG_SOURCE_OTHER),
    PAIR(GL_DEBUG_SOURCE_THIRD_PARTY),
    PAIR(GL_DEBUG_SOURCE_SHADER_COMPILER),
    PAIR(GL_DEBUG_SOURCE_WINDOW_SYSTEM),

    PAIR(GL_DEBUG_SEVERITY_HIGH),
    PAIR(GL_DEBUG_SEVERITY_MEDIUM),
    PAIR(GL_DEBUG_SEVERITY_LOW),
    PAIR(GL_DEBUG_SEVERITY_NOTIFICATION),

    PAIR(GL_DEBUG_TYPE_ERROR),
    PAIR(GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR),
    PAIR(GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR),
    PAIR(GL_DEBUG_TYPE_PORTABILITY),
    PAIR(GL_DEBUG_TYPE_PERFORMANCE),
    PAIR(GL_DEBUG_TYPE_MARKER),
    PAIR(GL_DEBUG_TYPE_PUSH_GROUP),
    PAIR(GL_DEBUG_TYPE_POP_GROUP),
    PAIR(GL_DEBUG_TYPE_OTHER)
  };

  return map[e];
}

static void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id,
       GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {

  std::cerr << "OpenGL has something to say:\n"
            << "Source: " << glEnumToString(source) << "\n"
            << "Type: " << glEnumToString(type) << "\n"
            << "Id: " << id << "\n"
            << "Severity: " << glEnumToString(severity) << "\n"
            << message << "\n";
}


bool RenderSystem::create(int width, int height, const char* title) {
  glfwInit();

  GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  m_window = window;

  glfwMakeContextCurrent(window);

  glewInit();
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(debugCallback, nullptr);

  // This should trigger debug callback.
  glClear(GL_VERTEX_ARRAY);

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

void RenderSystem::setClearColor(const glm::vec3& color) {
  m_clearColor = color;
}

const glm::vec3& RenderSystem::getClearColor() const {
  return m_clearColor;
}

void RenderSystem::beginFrame() const {
  glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderSystem::endFrame() const {
  glfwSwapBuffers(std::any_cast<GLFWwindow*>(m_window));
}
