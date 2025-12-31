#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
  GLuint ID;
  void checkCompileErrors(GLuint id, std::string type);

public:
  Shader(const char *vertex_path, const char *fragment_path);
  void use();
  GLuint getId();
  void setInt(const std::string uniform_name, int data);
  void setFloat(const std::string uniform_name, float data);
  void setBool(const std::string uniform_name, bool data);
  void setVec3(const std::string uniform_name, glm::vec3 data);
  void setMat4(const std::string uniform_name, glm::mat4 data);
  ~Shader();
};
