#ifndef ENGINE_H
#define ENGINE_H
#include "graphics/graphics.h"
#include "graphics/gameObjects/gameObject.h"
#include "graphics/shaders/shader.h"
#include "graphics/textures/texture.h"
#include <list>
class Nexus{
private:
	Graphics_System gr = Graphics_System("NULL",0,0);
public:
	std::vector<GameObject*> gameObjs;
	
	Nexus(char* name, float width, float height){
		printf("=============================\n");
		printf("       NEXUS 3D ENGINE       \n");
		printf("=============================\n");
		gr = Graphics_System(name, width, height);
		int f = gr.initGL();
		if(f == -1)
			std::cout << "Failed to create window.\n";
	}
	void initGameObj(){
		gr.initGameObj(gameObjs);
	}
	void updateGraphics(){
		gr.nextTick(gameObjs);
	}
	void updateBackground(float x, float y, float z, float a){
		this->gr.colorX = x;
		this->gr.colorY = y;
		this->gr.colorZ = z;
		this->gr.colorA = a;
	}
	void addObject(GameObject* obj){
		gameObjs.push_back(obj);
	}
	void compileShaders(){
		for(int i = 0; i < gameObjs.size(); i++){
			//printf("Now comp shader read ya frag file like: \n%s\n",gameObjs[i].s.fShaderSrc);
			gr.compShadersAndCreateShaderProgram(gameObjs[i]->s, gameObjs[i]);
			if(gameObjs[i]->shaderProg == NULL)
				std::cout<< "SHADER PROGRAM IS NULL, THIS SHOULD NOT OCCUR!\n";
			//else
			//	printf("unsigned int shaderProg is not null and is %x\n",gameObjs[i].shaderProg);
		}
		initGameObj();
	}
	void loadScript(char* fileName){
	//	Script = new Script(fileName, this);
	}
	float getTime(){
		return gr.getTime();
	}
};
#endif
