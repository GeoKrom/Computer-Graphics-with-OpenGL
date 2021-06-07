#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>



#ifndef OBJLOADER_H
#define OBJLOADER_H

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 texcoord;
	glm::vec3 normal;
};

class objLoader {
public:
	objLoader();
	bool objLoad(const char* path);
};

#endif