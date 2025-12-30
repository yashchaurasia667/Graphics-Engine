#include "shader.h"

Shader::Shader(const char *vertex_path, const char *fragment_path)
{
  std::string vertex_code, fragment_code;
  std::ifstream vertex_file, fragment_file;

  vertex_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fragment_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  // read the shader source from the files
  try
  {
    vertex_file.open(vertex_path);
    fragment_file.open(fragment_path);

    std::stringstream vertex_stream, fragment_stream;
    vertex_stream << vertex_file.rdbuf();
    fragment_stream << fragment_file.rdbuf();

    vertex_file.close();
    fragment_file.close();

    vertex_code = vertex_stream.str();
    fragment_code = fragment_stream.str();
  }
  catch (std::ifstream::failure e)
  {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
  }

  const char *vertex_shader_code = vertex_code.c_str();
  const char *fragment_shader_code = fragment_code.c_str();

  // compile shaders
  GLuint vertex, fragment;
  int success;
  char infoLog[512];

  // vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertex_shader_code, NULL);
  glCompileShader(vertex);
  checkCompileErrors(vertex, "VERTEX");

  // fragment shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fragment_shader_code, NULL);
  glCompileShader(fragment);
  checkCompileErrors(fragment, "FRAGMENT");

  // shader program
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);
  checkCompileErrors(ID, "PROGRAM");

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::use()
{
  glUseProgram(ID);
}

void Shader::checkCompileErrors(GLuint id, std::string type)
{
  int success;
  char info[512];
  if (type != "PROGRAM")
  {
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(id, 512, NULL, info);
      std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                << info << "\n -- --------------------------------------------------- -- " << std::endl;
    }
  }
  else
  {
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(id, 512, NULL, info);
      std::cout << "ERROR::PROGRAM_COMPILATION_ERROR of type: " << type << "\n"
                << info << "\n -- --------------------------------------------------- -- " << std::endl;
    }
  }
}

GLuint Shader::getId()
{
  return this->ID;
}

void Shader::setInt(const std::string uniform_name, int data)
{
  glUniform1i(glGetUniformLocation(this->ID, uniform_name.c_str()), data);
}

void Shader::setFloat(const std::string uniform_name, float data)
{
  glUniform1f(glGetUniformLocation(this->ID, uniform_name.c_str()), data);
}

void Shader::setBool(const std::string uniform_name, bool data)
{
  glUniform1i(glGetUniformLocation(this->ID, uniform_name.c_str()), data);
}

void Shader::setVec3(const std::string uniform_name, glm::vec3 data)
{
  glUniform3fv(glGetUniformLocation(this->ID, uniform_name.c_str()), 1, glm::value_ptr(data));
}

void Shader::setMat4(const std::string uniform_name, glm::mat4 data)
{
  glUniformMatrix4fv(glGetUniformLocation(this->ID, uniform_name.c_str()), 1, GL_FALSE, glm::value_ptr(data));
}

Shader::~Shader()
{
  glDeleteProgram(ID);
}