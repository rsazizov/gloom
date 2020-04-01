#include "Camera.hh"
#include "InputSystem.hh"

#include <glm/common.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

Camera::Camera() {
}

Camera::~Camera() {
}

void Camera::setFov(float fov) {
  m_fov = fov;
}

float Camera::getFov() const {
  return m_fov;
}

void Camera::setPosition(const glm::vec3& position) {
  m_position = position;
}

const glm::vec3& Camera::getPosition() const {
  return m_position;
}

void Camera::translate(const glm::vec3& translation) {
  m_position += translation;
}

void Camera::rotate(const glm::vec3& rotation) {
  m_rotation += rotation;
}

void Camera::setAspect(float aspect) {
  m_aspect = aspect;
}

float Camera::getAspect() const {
  return m_aspect;
}

void Camera::setNearClip(float near) {
  m_near = near;
}

float Camera::getNearClip() const {
  return m_near;
}

void Camera::setFarClip(float far) {
  m_far = far;
}

float Camera::getFarClip() const {
  return m_far;
}

void Camera::setSensitivity(float sensitivity) {
  m_sensitivity = sensitivity;
}

float Camera::getSensitivity() const {
  return m_sensitivity;
}

void Camera::setSpeed(float speed) {
  m_speed = speed;
}

float Camera::getSpeed() const {
  return m_speed;
}

glm::vec3 Camera::getForward() const {
  glm::mat4 trans(1.0f);

  trans = glm::rotate(trans, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
  trans = glm::rotate(trans, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));

  glm::vec3 forward = trans * glm::vec4(0, 0, -1, 1);

  return glm::normalize(forward);
}

glm::vec3 Camera::getRight() const {
  glm::mat4 trans(1.0f);

  trans = glm::rotate(trans, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
  trans = glm::rotate(trans, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));

  glm::vec3 forward = trans * glm::vec4(1, 0, 0, 1);

  return glm::normalize(forward);
}

glm::mat4 Camera::getViewProjection() {
  m_rotation.x = glm::clamp(m_rotation.x, -89.9f, 89.9f);

  glm::vec3 forward = getForward();

  glm::mat4 view = glm::lookAt(m_position, m_position + forward, glm::vec3(0, 1, 0));
  glm::mat4 proj = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);

  return proj * view;
}

void Camera::handleInput(InputSystem& input, float dt) {
  if (input.isKeyDown(GLFW_KEY_LEFT_SHIFT)) {
    dt *= 2;
  }

  if (input.isKeyDown(GLFW_KEY_W)) {
    translate(getForward() * m_speed * dt);
  }

  if (input.isKeyDown(GLFW_KEY_S)) {
    translate(-getForward() * m_speed * dt);
  }

  if (input.isKeyDown(GLFW_KEY_D)) {
    translate(getRight() * m_speed * dt);
  }

  if (input.isKeyDown(GLFW_KEY_A)) {
    translate(-getRight() * m_speed * dt);
  }

  glm::vec2 change = input.getMouseChange() * m_sensitivity;

  rotate({change.y, change.x, 0});
}
