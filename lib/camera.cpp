#include "camera.h"

Camera::Camera() {}

Camera::Camera(GLFWwindow *window, glm::vec3 pos, float speed, float sensitivity, float fov)
{
  this->pos = pos;
  this->up = glm::vec3(0.0f, 1.0f, 0.0f);
  this->front = glm::vec3(0.0f, 0.0f, -1.0f);
  this->delta_time = 0.0f;
  this->last_frame = 0.0f;
  this->speed = speed;
  this->sensitivity = sensitivity;
  this->yaw = -90.0f;
  this->pitch = 0.0f;
  this->fov = fov;
}

void Camera::mouseCallback(double xpos, double ypos)
{
  std::cout << "mouse event" << std::endl;
  float x = static_cast<float>(xpos);
  float y = static_cast<float>(ypos);

  if (this->first_mouse)
  {
    std::cout << "First mouse" << std::endl;
    lastX = x;
    lastY = y;
    first_mouse = false;
  }

  float xoffset = x - lastX;
  float yoffset = lastY - y;
  lastX = x;
  lastY = y;

  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw += xoffset;
  pitch += yoffset;

  if (pitch > 89.0f)
    pitch = 89.0f;
  if (pitch < -89.0f)
    pitch = -89.0f;

  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  front = glm::normalize(direction);
  // std::cout << front.x << "," << front.y << "," << front.z << std::endl;
}

void Camera::scrollCallback(double xoffset, double yoffset)
{
  std::cout << "scorll event" << std::endl;
  fov -= (float)yoffset;
  if (fov < 1.0f)
    fov = 1.0f;
  if (fov > 45.0f)
    fov = 45.0f;
}

void Camera::setSensitivity(float sens)
{
  this->sensitivity = sens;
}

void Camera::setSpeed(float speed)
{
  this->speed = speed;
}

glm::mat4 Camera::getViewMatrix()
{
  return glm::lookAt(pos, pos + front, up);
}

Camera::~Camera()
{
}
