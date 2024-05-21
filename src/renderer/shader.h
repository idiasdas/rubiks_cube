#pragma  once
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>

#ifndef EXECUTABLE_UTILS_PATH
#define EXECUTABLE_UTILS_PATH ""
#endif

GLuint LoadShaders(std::string vertex_file_path, std::string fragment_file_path);
