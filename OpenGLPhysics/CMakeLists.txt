# CMakeList.txt : CMake project for OpenGLPhysics, include source and define
# project specific logic here.
#

# Add source to this project's executable.
set(SOURCE_FILES ${CMAKE_SOURCE_DIR}/*.cpp)
set(HEADER_FILES ${CMAKE_SOURCE_DIR}/*.h)


add_executable(OpenGLPhysics ${HEADER_FILES} ${SOURCE_FILES})
#add_executable(OpenGLPhysics "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OpenGLPhysics PROPERTY CXX_STANDARD 20)
endif()
#find_package(OpenGL)


add_compile_definitions(PROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)



# TODO: Add tests and install targets if needed.
