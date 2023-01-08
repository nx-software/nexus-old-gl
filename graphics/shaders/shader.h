#ifndef SHADER_H
#define SHADER_H
#include "../glad/include/glad/glad.h"

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

class Shader{
public:
	// program ID
	unsigned int ID;
	std::string vShaderSrc;
	std::string fShaderSrc;
	char* vertexFName;
	char* fragFName;
	Shader(){}
	Shader(char* vertexSP, char* fragSP){
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
			vShaderSrc[sizeOfVFile+1] = '\0';
			fShaderSrc[sizeOfFFile+1] = '\0';
			printf("READ VERTEX FILE AS FOLLOWS: \n");
			printf("%s\n",vShaderSrc);
			printf("===============================\n");
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
	// set values
	void setBool(const std::string &name, bool val) const;
	void setInt(const std::string &name, int val) const;
	void setFloat(const std::string &name, float val) const;
	
};
#endif
