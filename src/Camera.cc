#include "Camera.hh"
#include "InputSystem.hh"

#include <GLFW/glfw3.h>
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

glm::vec3 Camera::transform(const glm::vec3& vec) const {
  glm::mat4 trans(1.0f);

  trans = glm::rotate(trans, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
  trans = glm::rotate(trans, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));

  return trans * glm::vec4(vec, 1.0f);
}

glm::vec3 Camera::getForward() const {
  return transform({0.0f, 0.0f, -1.0f});
}

glm::vec3 Camera::getRight() const {
  return transform({1.0f, 0.0f, 0.0f});
}

glm::mat4 Camera::getViewProjection() {
  m_rotation.x = glm::clamp(m_rotation.x, -89.9f, 89.9f);

  glm::vec3 forward = getForward();

  glm::mat4 view = glm::lookAt(m_position, m_position + forward, glm::vec3(0, 1, 0));
  glm::mat4 proj = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);

  return proj * view;
}

void Camera::handleInput(InputSystem& input, float dt) {
  glm::vec3 movement = glm::vec3(0.0f);

  if (input.isKeyDown(GLFW_KEY_W)) {
    movement += getForward() * m_speed;
  }

  if (input.isKeyDown(GLFW_KEY_S)) {
    movement += -getForward() * m_speed;
  }

  if (input.isKeyDown(GLFW_KEY_D)) {
    movement += getRight() * m_speed;
  }

  if (input.isKeyDown(GLFW_KEY_A)) {
    movement += -getRight() * m_speed;
  }

  if (input.isKeyDown(GLFW_KEY_R)) {
    m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    m_position = glm::vec3(0.0f, 0.0f, 0.0f);
  }

  if (input.isKeyDown(GLFW_KEY_LEFT_SHIFT)) {
    movement *= 2;
  }

  translate(movement * dt);

  glm::vec2 mouseChange = input.getMouseChange() * m_sensitivity;

  rotate({mouseChange.y, mouseChange.x, 0});
}
