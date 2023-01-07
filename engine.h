#ifndef ENGINE_H
#define ENGINE_H
#include "graphics/graphics.h"
#include "graphics/gameObjects/gameObject.h"
#include "graphics/shaders/shader.h"
#include <list>
class Nexus{
private:
	Graphics_System gr = Graphics_System("NULL",0,0);
public:
	std::vector<GameObject> gameObjs;
	
	Nexus(char* name, int width, int height){
		gr = Graphics_System(name, width, height);
		int f = gr.initGL();
		if(f == -1)
			std::cout << "Failed to create window.\n";
	}
	void initGameObj(){
		gr.initGameObj(gameObjs);
	}
	void updateGraphics(){
		gr.nextTick();
	}
	void updateBackground(float x, float y, float z, float a){
		this->gr.colorX = x;
		this->gr.colorY = y;
		this->gr.colorZ = z;
		this->gr.colorA = a;
	}
	void addObject(GameObject obj){
		gameObjs.push_back(obj);
	}
	
	void compileShaders(){
		for(int i = 0; i < gameObjs.size(); i++){
			gr.compShadersAndCreateShaderProgram(gameObjs[i].vShader, gameObjs[i].fShader);
		}
	}
};
#endif

