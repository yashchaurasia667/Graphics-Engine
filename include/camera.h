#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class Camera
{
private:
  glm::vec3 pos;
  glm::vec3 up;
  glm::vec3 front;
  float delta_time, last_frame, speed, sensitivity;
  float yaw, pitch, fov;
  float lastX, lastY;
  bool first_mouse;

public:
  Camera();
  Camera(GLFWwindow *window, glm::vec3 pos, float speed, float sensitivity, float fov);
  void mouseCallback(double xpos, double ypos);
  void scrollCallback(double xoffset, double yoffset);
  void setSensitivity(float sens);
  void setSpeed(float speed);
  glm::mat4 getViewMatrix();
  ~Camera();
};