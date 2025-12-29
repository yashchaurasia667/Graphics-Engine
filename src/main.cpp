#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <shader.h>

// global vars/constants
const unsigned int SCR_WIDTH = 800, SCR_HEIGHT = 600;
glm::vec3 background_color = glm::vec3(0.2f);
glm::vec3 origin = glm::vec3(0.0f);

// camera vars
glm::vec3 pos = glm::vec3(0.0f);
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);

float deltaTime = 0.0f, lastFrame = 0.0f, speed = 2.5f, sensitivity = 0.1f;
float yaw = 0.0f, pitch = 0.0f;
float lastX, lastY;
bool firstMouse = true;

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void mouseCallback(GLFWwindow *window, double xpos, double ypos);
void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

// camera functions

int main()
{
  // initialize GLFW window system
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Game engine", NULL, NULL);
  if (window == NULL)
  {
    glfwTerminate();
    std::cout << "Failed to create a GLFW window" << std::endl;
    return -1;
  }

  // set current window as the focus
  glfwMakeContextCurrent(window);

  // initialize glad
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to load OpenGL function pointers" << std::endl;
    glfwTerminate();
    return -1;
  }
  // set resize callback, mouse control etc.
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window, mouseCallback);

  float vertices[] = {
      -0.5f, -0.5f, 0.0f, // left
      0.5f, -0.5f, 0.0f,  // right
      0.0f, 0.5f, 0.0f    // top
  };

  Shader triangle("../src/shaders/default.vs", "../src/shaders/default.fs");

  GLuint VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // set background color
  glClearColor(background_color.r, background_color.g, background_color.b, 1.0f);

  // main event loop
  while (!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT);
    processInput(window);

    triangle.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
  glfwTerminate();
  return 0;
}

// handle resizing
void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

// process keyboard inputs
void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void mouseCallback(GLFWwindow *window, double xpos, double ypos)
{
  float x = static_cast<float>(xpos);
  float y = static_cast<float>(ypos);

  if (firstMouse)
  {
    std::cout << "First mouse" << std::endl;
    lastX = x;
    lastY = y;
    firstMouse = false;
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
  direction.y = cos(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  front = direction;
}