#ifndef GLOOM_CAMERA_HH
#define GLOOM_CAMERA_HH

#include <glm/glm.hpp>

class InputSystem;

class Camera {
public:
  Camera();
  ~Camera();

  void setFov(float fov);
  float getFov() const;

  void setPosition(const glm::vec3& position);
  const glm::vec3& getPosition() const;

  void translate(const glm::vec3& translation);
  void rotate(const glm::vec3& rotation);

  void setAspect(float aspect);
  float getAspect() const;

  void setNearClip(float near);
  float getNearClip() const;

  void setFarClip(float far);
  float getFarClip() const;

  void setSensitivity(float sensitivity);
  float getSensitivity() const;

  void setSpeed(float speed);
  float getSpeed() const;

  glm::mat4 getViewProjection();

  glm::vec3 transform(const glm::vec3& vec) const;

  glm::vec3 getRight() const;
  glm::vec3 getForward() const;

  void handleInput(InputSystem& input, float dt);

private:
  glm::vec3 m_position = glm::vec3(0, 0, 0);
  glm::vec3 m_rotation = glm::vec3(0, 0, 0);

  float m_near = 0.1f;
  float m_far = 100;
  float m_fov = 70.f;
  float m_sensitivity = 0.1f;
  float m_speed = 4;

  float m_aspect = 640.0f / 480.0f;
};

#endif
