# Build static libraries
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Add GLAD
add_subdirectory(glad)

# Add GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
set(GLFW_BUILD_X11 ON)
set(GLFW_BUILD_WAYLAND OFF)

add_subdirectory(glfw)

# Add GLM
add_subdirectory(glm)

# Add spdlog
add_subdirectory(spdlog)

# Add imgui
add_subdirectory(imgui)
