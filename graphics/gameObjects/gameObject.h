#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <cstring>
#include <cstdlib>
#include "../shaders/shader.h"
#include <vector>
#include <iostream>
class GameObject{
private:
	int sizeOfArray(float array[]){
		int i = 0;
		while(array[i++]){}
		return i;
	}
public:
	Shader vShader = Shader("EMPTY_SHADER");
	Shader fShader = Shader("EMPTY_SHADER");
	unsigned int shaderProg;
	float vert[90000];
	GameObject(float vert[]){
		memcpy(vert, this->vert, sizeof(vert)+sizeOfArray(vert));
	}
	void addVShader(Shader s){
		this->vShader = s;
	}
	void addFShader(Shader s){
		this->fShader = s;
	}
};
#endif
