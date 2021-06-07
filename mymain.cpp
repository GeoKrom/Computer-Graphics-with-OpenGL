#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ShaderHandler.h"
#include "objLoader.h"
#include "Cube.h"
#include "Sphere.h"


GLFWwindow* window;
using namespace glm;
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

float cam_x = 175; // gia to erwthma 4, kinhsh kameras
float cam_y = 55;
float cam_z = 50;
float mv_updown = 3; //gia to erwthma 3, kinhsh sfairas
float mv_lr = 3;
float mv_io = 4;
float k = rand() % 2; //kokkino
float p = rand() % 2; //prasino
float mp = rand() % 2; //mple
int d = rand() % 10 + 1; //aktina - vasi - pleyra kapoiou tyxaiou stoixeioy

int main(void)
{
	int win_h = 600;
	int win_l = 600;
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(win_h, win_l, "test", NULL, NULL);
	glfwSetWindowTitle(window, u8"Συγκρουόμενα");

	// Ensure we can capture the escape key being pressed below
	glfwSetKeyCallback(window, keyCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
	glfwGetFramebufferSize(window, &win_l, &win_h);

	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glViewport(0.0f, 0.0f, win_l, win_h);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
	
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint shaderuser = LoadShaders("TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader");
	GLuint Matrix = glGetUniformLocation(shaderuser, "MVP");

	Cube* SC = new Cube();
	Sphere *SPH =new Sphere();
	

	do {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glm::mat4 View = glm::lookAt(
			glm::vec3(cam_x, cam_y, cam_z),
			glm::vec3(50, 50, 50),
			glm::vec3(0, 1, 0)  
		);
		glm::mat4 Projection = glm::perspective(glm::radians(110.0f), 1.0f / 1.0f, 0.1f, 1000.0f);

		glUseProgram(shaderuser);

		glm::mat4 Model = glm::mat4(1.0f);
		glm::mat4 MVP = Projection * View * Model;
		
		
		SC->makeCube(0, 0, 0, 100, k, p, mp);

		SPH->makeSphere(15,mv_updown,mv_lr,mv_io);


		/*if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			while (1) {
				int lucky = rand() % 3 + 1;
				if (lucky == 1) {
					Cube* newC = new Cube();
					newC->makeCube(0, 0, 0,d,k,p,mp);
				}
				else if (lucky == 2) {
					//dhmiourgia sfairas
				}
				else if (lucky == 3) {
					//Dhmiourgia kylindrou
				}
			}
		}*/ 

		glUniformMatrix4fv(Matrix, 1, GL_FALSE, &MVP[0][0]);
		
		
		glPopMatrix();
		glfwSwapBuffers(window);
		glfwPollEvents();
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);


	std::cout << cam_x << std::endl;
	std::cout << cam_y << std::endl;
	std::cout << cam_z << std::endl;

	glDeleteProgram(shaderuser);
	glDeleteVertexArrays(1, &VertexArrayID);

	glfwTerminate();

	return EXIT_SUCCESS;

}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	// actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch (key)
		{
		case GLFW_KEY_A: // kamera
			cam_x = cam_x + 5;
			break;
		case GLFW_KEY_D:
			cam_x = cam_x - 5;
			break;
		case GLFW_KEY_S:
			cam_y = cam_y + 5;
			break;
		case GLFW_KEY_X:
			cam_y = cam_y - 5;
			break;
		case GLFW_KEY_W:
			cam_z = cam_z + 5;
			break;
		case GLFW_KEY_E:
			cam_z = cam_z - 5;
			break;
		case GLFW_KEY_R:
			cam_x = 170;
			cam_y = 110;
			cam_z = -2;
			break;
			//-----------------------------------------
		case GLFW_KEY_UP: // sfaira
			mv_updown = mv_updown + 1;
			break;
		case GLFW_KEY_DOWN:
			mv_updown = mv_updown - 1;
			break;
		case GLFW_KEY_LEFT:
			mv_lr = mv_lr + 1;
			break;
		case GLFW_KEY_RIGHT:
			mv_lr = mv_lr - 1;
			break;
		case GLFW_KEY_EQUAL:
			mv_io = mv_io - 1;
			break;
		case GLFW_KEY_MINUS:
			mv_io = mv_io + 1;
			break;
		}
	}
};

