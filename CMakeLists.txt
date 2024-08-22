cmake_minimum_required(VERSION 3.17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(project_target rubiks_cube)

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

add_executable(rubiks_cube ${executable_sources})

target_compile_options(rubiks_cube PRIVATE -Wall -Wextra -Wpedantic)

file(RELATIVE_PATH relative ${CMAKE_BINARY_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/utils/")

message(" [INFO] The relative path between build and utils is:\n\t - ${relative}")

# Create compile definition EXECUTABLE_UTILS_PATH with the relative path the build path and the utils directory
target_compile_definitions(rubiks_cube PRIVATE EXECUTABLE_UTILS_PATH="${relative}/")

target_include_directories(rubiks_cube PUBLIC ${include_directories})

target_link_libraries(rubiks_cube PRIVATE ${libraries})

# Adding tests

enable_testing()
list(REMOVE_ITEM executable_sources "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

add_executable(test_external tests/test_external.cpp)
target_include_directories(test_external PUBLIC ${include_directories})
target_link_libraries(test_external PRIVATE ${libraries})
add_test(NAME test_external COMMAND test_external)

add_executable(test_ray_plane_intersection tests/test_ray_plane_intersection.cpp ${executable_sources})
target_include_directories(test_ray_plane_intersection PUBLIC ${include_directories})
target_link_libraries(test_ray_plane_intersection PRIVATE ${libraries})
add_test(NAME test_ray_plane_intersection COMMAND test_ray_plane_intersection)

add_executable(test_ray_cube_intersection tests/test_ray_cube_intersection.cpp ${executable_sources})
target_include_directories(test_ray_cube_intersection PUBLIC ${include_directories})
target_link_libraries(test_ray_cube_intersection PRIVATE ${libraries})
add_test(NAME test_ray_cube_intersection COMMAND test_ray_cube_intersection)
