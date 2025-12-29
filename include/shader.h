#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
  void checkCompileErrors(GLuint id, std::string type);

public:
  GLuint ID;
  Shader(const char *vertex_path, const char *fragment_path);
  void use();
  ~Shader();
};
