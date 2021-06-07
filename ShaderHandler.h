#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <vector>
#include <fstream>
#include <sstream>

#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

#endif
