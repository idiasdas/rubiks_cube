cmake_minimum_required(VERSION 3.17)

add_compile_options(-Wall -Wextra -Wpedantic)

set(project_target rubiks_cube)
set(executable_name rubiks_cube)
set(include_directories
    ext/glfw/include
    ext/glad/include
    ext/glm
    ext/spdlog/include
    src/
)
set(libraries
    glad
    glfw
    glm::glm
    spdlog::spdlog
)

project(${project_target})

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(ext)

file(GLOB_RECURSE executable_sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${executable_name} ${executable_sources})

file(RELATIVE_PATH relative ${CMAKE_BINARY_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/utils/")

message(" [INFO] The relative path between build and utils is:\n\t - ${relative}")

# Create compile definition EXECUTABLE_UTILS_PATH with the relative path the build path and the utils directory
target_compile_definitions(${executable_name} PRIVATE EXECUTABLE_UTILS_PATH="${relative}/")

target_include_directories(${executable_name} PUBLIC ${include_directories})

target_link_libraries(${executable_name} PRIVATE ${libraries})

# Adding tests

enable_testing()
find_package(GTest REQUIRED)
add_subdirectory(tests)

target_include_directories(tests PUBLIC ${include_directories})

target_link_libraries(tests PRIVATE ${libraries})
