#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <cstring>
#include <cstdlib>
#include "../shaders/shader.h"
#include <vector>
class GameObject{
private:
	int sizeOfArray(float array[]){
		int i = 0;
		while(array[i++]){}
		return i;
	}
public:
	std::vector<Shader> vShader;
	std::vector<Shader> fShader;
	float vert[90000];
	GameObject(float vert[]){
		memcpy(vert, this->vert, sizeof(vert)+sizeOfArray(vert));
	}
	void addVShader(Shader s){
		vShader.push_back(s);
	}
	void addFShader(Shader s){
		fShader.push_back(s);
	}
};
#endif
