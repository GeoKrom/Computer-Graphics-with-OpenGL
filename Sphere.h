#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "ShaderHandler.h"
#include <vector>

#ifndef SPHERE_H
#define SPHERE_H

class Sphere {
public:
	Sphere();
	void makeSphere(float aktina, float pk, float ad, float me);
};


#endif

