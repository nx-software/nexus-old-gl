#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "glad/include/glad/glad.h"
#include "gameObjects/gameObject.h"
#include "shaders/shader.h"
#include "textures/texture.h"
#include "../utils/utils.h"
// transform
#include "transform/glm/glm.hpp"
#include "transform/glm/ext/matrix_transform.hpp"
#include "transform/glm/gtc/type_ptr.hpp"
#include "transform/transform.h"
//
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
	GLfloat fov = 45.0f, near = 0.1f, far = 100.0f;
	unsigned int VAO, VBO, EBO;
	// create matrices (matrix refrence no way???) for our projecion (in this case perspective) and view
	glm::mat4 view = glm::mat4(1.0f);
	
	glm::mat4 projection;
	Graphics_System(char* name, float width, float height){
		this->name = name;
		this->width = width;
		this->height = height;
		this->projection = glm::perspective(glm::radians(fov), 800.0f/600.0f, near, far);
		view = glm::translate(view, glm::vec3(0.0f,0.0f,-3.0f)); // DEBUG
	}
	/*
		INITGL(VOID)
		Creates window and inits GL (no way?)
	*/
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
		// enable depth buffering
		glEnable(GL_DEPTH_TEST);
	}
	/*
		Updates graphics, including:
			- Background color
			- Models
			- Shaders && Textures
	*/
	void nextTick(std::vector<GameObject*> gObs){
		processInput();
		// Color 
		if(colorX && colorY && colorZ && colorA){
			glClearColor(colorX, colorY, colorZ, colorA);
		}else{
			glClearColor(0.2f,0.3f,0.3f,1.0f);
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for(int i = 0; i < gObs.size(); i++){
			glBindTexture(GL_TEXTURE_2D, gObs[i]->Tex.textureID);
			glUseProgram(gObs[i]->shaderProg);
			// perspective / transformation stuff
			glUniformMatrix4fv(glGetUniformLocation(gObs[i]->shaderProg, "model"), 1, GL_FALSE, glm::value_ptr(gObs[i]->transform));
			glUniformMatrix4fv(glGetUniformLocation(gObs[i]->shaderProg, "view"), 1, GL_FALSE, glm::value_ptr(this->view));
			glUniformMatrix4fv(glGetUniformLocation(gObs[i]->shaderProg, "projection"), 1, GL_FALSE, glm::value_ptr(this->projection));
			// 
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0 , 36);
		}
		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}
	/*
		Gets time from GLFW
	*/
	float getTime(){
		return (float)glfwGetTime();
	}
	/*
		In future versions of Nexus this will be used to tell the game 
		what keys have been pressed
	*/
	void processInput(){
		if(glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			exit(0);
	}
	/*
		Create a gameobject-
	*/
	void initGameObj(std::vector<GameObject*> gameObjs){
		for(int i = 0; i < gameObjs.size(); i++){
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);
			glGenBuffers(1, &VBO); // create gl buffer for the VBO
			glBindBuffer(GL_ARRAY_BUFFER, VBO); // whenever we add to the array buffer
			glBufferData(GL_ARRAY_BUFFER, sizeof(gameObjs[i]->vert), gameObjs[i]->vert, GL_STATIC_DRAW); // copy VBO to array buffer
			glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    			glEnableVertexAttribArray(1);
			// init texture
			loadGLTexture(&gameObjs[i]->Tex);
			setInt("tex",gameObjs[i]->Tex.textureID, gameObjs[i]->s.ID);
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	/*
		Check if shader compiled correctly
	*/
	void checkShaderStatus(unsigned int shader, Shader s){
		int success;
		char infoLog[512]; // error message
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if(!success){
			glGetShaderInfoLog(shader, 512, NULL, infoLog); // get error
			printf("===================================\n");
			std::cout << "Error compile shader: " << infoLog << "\n";
			std::cout << "Vertex Shader data: \n";
			printf("%s\n",s.vShaderSrc.c_str());
			std::cout << "Frag Shader data\n";
			printf("%s\n",s.fShaderSrc.c_str());
			printf("===================================\n");
			exit(1);	
		}
	}
	/*
		Check if link shaders completed successfully
	*/
	void checkLinkStatus(unsigned int shaderProg){
		int success;
		char infoLog[512]; // error
		glGetProgramiv(shaderProg, GL_LINK_STATUS, &success);
		if(!success){
			glGetProgramInfoLog(shaderProg, 512, NULL, infoLog); // get error
			std::cout << "Error link shader prog: " << infoLog << "\n";
		}
	}
	/*
		Compile shaders
	*/
	void compShadersAndCreateShaderProgram(Shader shader, GameObject* gameObject){
		const char* vShade = shader.vShaderSrc.c_str();
		const char* fShade = shader.fShaderSrc.c_str();
		gameObject->shaderProg = glCreateProgram();
		unsigned int cShader;
		cShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(cShader, 1, &vShade, NULL);
		glCompileShader(cShader); // compile the shader
		checkShaderStatus(cShader,shader);
		// attach shaders to program 
		glAttachShader(gameObject->shaderProg, cShader);
		//
		cShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(cShader, 1, &fShade, NULL);
		glCompileShader(cShader); // compile the shader
		checkShaderStatus(cShader,shader);
		// attach shaders to program 
		glAttachShader(gameObject->shaderProg, cShader);
		//
		glLinkProgram(gameObject->shaderProg);
		checkLinkStatus(gameObject->shaderProg);
		glDeleteShader(cShader);
	}
	/*
		Load texture
	*/
	void loadGLTexture(texture* Tex){
		glGenTextures(1, &Tex->textureID);
		glBindTexture(GL_TEXTURE_2D, Tex->textureID); // any options applied to GL_TEXTURE_2D will be set to the Texture ID provided
		
		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// gen texture
		if(Tex->data){
			// load tex
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Tex->width, Tex->height, 0, GL_RGB, GL_UNSIGNED_BYTE, Tex->data);
			// generate mipmap
			glGenerateMipmap(GL_TEXTURE_2D);
			//
			
		}else{
			printf("Failed to generate texture, texture file does not exist!\n");
			printf("Check integrity of game files.\n");
		}
	}
	/*
		===================
		SHADER FUNCTIONS
		===================
	*/
	void setInt(std::string name, int value, int id) {
		glUniform1i(glGetUniformLocation(id, name.c_str()), value); 
	}
};
#endif
