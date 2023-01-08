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
	Shader s = Shader("","");
	unsigned int shaderProg;
	float vert[50];
	GameObject(float vert[], char* vShaderName, char* fShaderName){
		//memcpy(vert, this->vert, sizeof(vert)+sizeOfArray(vert));
		for(int i = 0; i < 50; i++){
			this->vert[i] = vert[i]; 
			if(i % 10 == 0)
				printf("%f\n",vert[i]); 
			else
				printf("%f | ",vert[i]); 
		}
		printf("\n");
		this->s = Shader(vShaderName, fShaderName);
		printf("[gameObject] Gameobject read vertex shader (from src %s) as follows: \n%s\n",vShaderName,this->s.vShaderSrc);
		printf("[gameObject] Gameobject read frag shader (from src %s) as follows: \n%s\n",fShaderName,this->s.fShaderSrc);
	}
	
};
#endif
