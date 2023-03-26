#ifndef SHADER_H
#define SHADER_H
#include "../glad/include/glad/glad.h"
#include "../transform/glm/glm.hpp"
#include "../transform/glm/ext/matrix_transform.hpp"
#include "../transform/glm/gtc/type_ptr.hpp"
#include "../transform/transform.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <regex>
#include <vector>
class Shader{
public:
	// program ID
	unsigned int ID;
	unsigned int shaderProg;
	std::string vShaderSrc;
	std::string fShaderSrc;
	char* vertexFName;
	char* fragFName;
	int locations = 0;
	std::vector<int> finalTypes;
	Shader(){}
	Shader(char* vertexSP, char* fragSP, std::vector<int> finalTypes){
		this->finalTypes = finalTypes;
		this->vertexFName = vertexSP;
		this->fragFName = fragSP;
		// read from file
		FILE* vertFile = fopen(vertexSP, "r");
		FILE* fragFile = fopen(fragSP, "r");
		if(vertFile != NULL && fragFile != NULL){
			// get size of both files
			fseek(vertFile, 0L, SEEK_END);
			size_t sizeOfVFile = ftell(vertFile);
			char vertexShaderData[ftell(vertFile)];
			fseek(fragFile, 0L, SEEK_END);
			size_t sizeOfFFile = ftell(fragFile);
			char fragShaderData[ftell(fragFile)];
			rewind(vertFile);
			rewind(fragFile);
			// read
			fread(vertexShaderData, sizeof(vertexShaderData), 1, vertFile);
			fread(fragShaderData, sizeof(fragShaderData), 1, fragFile);
			vShaderSrc = vertexShaderData;
			fShaderSrc = fragShaderData;
			// get location
			std::string locVS = vShaderSrc;
			char* loc = "layout";
			size_t found = locVS.find("layout");
			while(found != std::string::npos){
				found = locVS.find("layout");
				if(found != std::string::npos){
				locVS.replace(found, strlen(loc), ""); 
				//printf("LOC = %d and we have :\n",locations);
				//std::cout << locVS << "\n";
				locations++;
				}
			}
			printf("VS = %d \n",locations);
			//
			vShaderSrc[sizeOfVFile] = '\0';
			fShaderSrc[sizeOfFFile] = '\0';
			//==printf("READ VERTEX FILE AS FOLLOWS: \n");
			//printf("%s\n",vShaderSrc);
			//printf("===============================\n");
		}else{
			printf("Error occured when trying to get shader files. File not found!\n");
			if(vertFile == NULL){
				printf("Vertex shader file not found!\n");
			}
			if(fragFile == NULL){
				printf("Fragment shader file not found!\n");
			}
		}
	}
	/*
		===================
		SHADER FUNCTIONS
		===================
	*/
	void setInt(char* name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name), value); 
	}
	void setVec3(const std::string &name, const glm::vec3 &value) const
    	{ 
    		glUseProgram(shaderProg);
    		//printf("setVec3 (glmvec3 version) called with args = [%s, %f, %f, %f] in shader %d\n",name.c_str(), value.x,value.y,value.z,shaderProg);
        	glUniform3fv(glGetUniformLocation(shaderProg, name.c_str()), 1, &value[0]); 
    	}
	void setVec3(const std::string &name, float x, float y, float z) const
	{
		glUseProgram(shaderProg);
		//printf("setVec3 called with args = [%s, %f, %f, %f] in shader %d\n",name.c_str(), x,y,z,shaderProg);
		 glUniform3f(glGetUniformLocation(shaderProg, name.c_str()), x, y, z); 
	}
};
#endif
