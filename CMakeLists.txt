cmake_minimum_required(VERSION 3.15)
project(Batle-City)
set(PROJECT_NAME battle-city)
add_executable(${PROJECT_NAME} src/main.cpp)

#glfw
add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

#glad
add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)