#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <cstring>
#include <cstdlib>
#include "../shaders/shader.h"
#include "../textures/texture.h"
#include "../transform/glm/glm.hpp"
#include "../transform/glm/ext/matrix_transform.hpp"
#include "../transform/glm/gtc/type_ptr.hpp"
#include "../transform/transform.h"
#include <vector>
#include <iostream>
// axis of rotations to make it easier to use
enum rotationAxis{
	AXIS_X = 0,
	AXIS_Y = 1,
	AXIS_Z = 2,
};
class GameObject{
private:
	int sizeOfArray(float array[]){
		int i = 0;
		while(array[i++]){}
		return i;
	}
public:
	Shader s;
	unsigned int shaderProg;
	float vert[180];

	texture Tex;
	char* name;
	// TRANSFORM SECTION
	glm::mat4 transform = glm::mat4(1.0f);
	GameObject(char* name,float vert[], char* vShaderName, char* fShaderName, char* texName){
		this->name = name;
		//memcpy(vert, this->vert, sizeof(vert)+sizeOfArray(vert));
		for(int i = 0; i < 180; i++){
			this->vert[i] = vert[i]; 

			if(i % 5 == 0)
				printf("%f\n",this->vert[i]); 
			else
				printf("%f | ",this->vert[i]); 
		}
		printf("\n");
		Tex = texture(texName);
		s = Shader(vShaderName, fShaderName);
		//printf("[gameObject] Gameobject read frag shader (from src %s) as follows: \n%s\n",fShaderName,this->s.fShaderSrc);
		//printf("[gameObject] Gameobject read vertex shader (from src %s) as follows: \n%s\n",vShaderName,this->s.vShaderSrc);
	}
	void rotate(float degrees, enum rotationAxis rA){
		glm::vec3 a = glm::vec3(0.0,0.0,1.0);
		switch(rA){
			case AXIS_X:
				a = glm::vec3(1.0,0.0,0.0);
				break;
			case AXIS_Y:
				a = glm::vec3(0.0,1.0,0.0);
				break;
			case AXIS_Z:
				a = glm::vec3(0.0,0.0,1.0);
				break;
			default:
				a = glm::vec3(0.0,0.0,1.0);
				break;
		}
		this->transform = tr_rotate(this->transform, degrees, a);
	}
};
#endif
