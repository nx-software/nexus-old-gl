#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "glad/include/glad/glad.h"
#include "gameObjects/gameObject.h"
#include "shaders/shader.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <list>
#include <iterator>
#include <vector>
class Graphics_System{
private:
	GLFWwindow* window;
	int width, height;
	char* name;
public:
	float colorX, colorY, colorZ, colorA;
	Graphics_System(char* name, int width, int height){
		this->name = name;
		this->width = width;
		this->height = height;
	}
	int initGL(){
		// Initilize GLFW
		glfwInit();
		// Set Version
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		// Create window
		this->window = glfwCreateWindow(800,600, this->name, NULL, NULL); // The first null is to disable fullscreen
		if(window == NULL){
			std::cout << "Window creation failed!\n";
			return -1;
		}
		glfwMakeContextCurrent(this->window);
		// Init glad so we can call gl functions
		if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
			std::cout<< "Glad init failed!\n";
			return -1;
		}
		// Init viewport
		glViewport(0,0,this->width,this->height);
	}
	void nextTick(){
		processInput();
		// Color 
		if(colorX && colorY && colorZ && colorA){
			glClearColor(colorX, colorY, colorZ, colorA);
		}else{
			glClearColor(0.2f,0.3f,0.3f,1.0f);
		}
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(this->window);
		glfwPollEvents();
		
	}
	void processInput(){
		if(glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			std::cout << "ESCAPE\n";
	}
	void initGameObj(std::vector<GameObject> gameObjs){
		for(int i = 0; i < gameObjs.size(); i++){
			unsigned int VBO; // create VBO for gameobject
			glGenBuffers(1, &VBO); // create gl buffer for the VBO
			glBindBuffer(GL_ARRAY_BUFFER, VBO); // whenever we add to the array buffer
			glBufferData(GL_ARRAY_BUFFER, sizeof(gameObjs[i].vert), gameObjs[i].vert, GL_STATIC_DRAW); // copy VBO to array buffer
		}
	}
	void checkShaderStatus(unsigned int shader){
		int success;
		char infoLog[512]; // error message
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if(!success){
			glGetShaderInfoLog(shader, 512, NULL, infoLog); // get error
			std::cout << "Error compile shader: " << infoLog << "\n";
		}
	}
	void compShadersAndCreateShaderProgram(std::vector<Shader> vShader, std::vector<Shader> fShader, GameObject gameObject){
		unsigned int cShader;
		for(int i = 0; i < vShader.size(); i++){			
			cShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(cShader, 1, &vShader[i].data, NULL);
			glCompileShader(cShader); // compile the shader
			checkShaderStatus(cShader);
		}
		for(int i = 0; i < fShader.size(); i++){			
			cShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(cShader, 1, &fShader[i].data, NULL);
			glCompileShader(cShader); // compile the shader
			checkShaderStatus(cShader);
		}
		// we now create an epic shader program so we can link them together
		
	}
};
#endif
