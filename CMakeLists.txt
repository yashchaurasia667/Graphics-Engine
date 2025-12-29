cmake_minimum_required(VERSION 3.20)
project(game_engine)

set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LIB ${CMAKE_CURRENT_SOURCE_DIR}/lib)

find_package(OpenGL REQUIRED)
add_library(depends INTERFACE)
target_include_directories(depends INTERFACE ${INCLUDE})
target_sources(depends INTERFACE "${LIB}/glad.c" "${LIB}/shader.cpp")

add_executable(${PROJECT_NAME} "${SOURCE}/main.cpp")
target_link_libraries(depends INTERFACE ${LIB}/libglfw3.a OpenGL::GL kernel32 user32 gdi32)
target_link_libraries(${PROJECT_NAME} PRIVATE depends)