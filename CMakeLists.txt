cmake_minimum_required(VERSION 3.17)

project(rubiks_cube)

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_NAME rubiks_cube)

add_subdirectory(ext)

file(GLOB EXECUTABLE_SOURCES src/*.cpp)

add_executable(${EXECUTABLE_NAME} ${EXECUTABLE_SOURCES})


file(RELATIVE_PATH relative ${CMAKE_BINARY_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/utils/")

message(" [INFO] The relative path between build and utils is:\n\t - ${relative}")

# Create compile definition EXECUTABLE_UTILS_PATH with the relative path the build path and the utils directory
target_compile_definitions(${EXECUTABLE_NAME} PRIVATE EXECUTABLE_UTILS_PATH="${relative}/")

target_include_directories(${EXECUTABLE_NAME} PUBLIC
    ext/glfw/include
    ext/glad/include
    ext/glm
    src/
)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE
    glad
    glfw
    glm::glm
)

# Adding tests

enable_testing()
find_package(GTest REQUIRED)
add_subdirectory(tests)

target_include_directories(tests PUBLIC
    ext/glfw/include
    ext/glad/include
    ext/glm
    src/
)

target_link_libraries(tests PRIVATE
    glad
    glfw
    glm::glm
)
