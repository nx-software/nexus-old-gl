#ifndef ENGINE_H
#define ENGINE_H
#include "graphics/graphics.h"
#include "graphics/gameObjects/gameObject.h"
#include "graphics/gameObjects/light.h"
#include "graphics/shaders/shader.h"
#include "graphics/textures/texture.h"
#include "graphics/gameObjects/camera.h"
#include "graphics/transform/glm/glm.hpp"
#include "graphics/transform/glm/ext/matrix_transform.hpp"
#include "graphics/transform/glm/gtc/type_ptr.hpp"
#include <list>
#include <GLFW/glfw3.h>
class Nexus{
private:
	Camera cam = Camera(0,0,0);
	Graphics_System gr = Graphics_System("NULL",0,0,&cam);
public:
	enum keys{
		KEY_W = 0,
		KEY_S = 2,
		KEY_A = 1, 
		KEY_D = 3,
		KEY_NONE = 99	
	};
	std::vector<GameObject*> gameObjs;
	std::vector<Light> lights;
	Nexus(char* name, float width, float height, Camera* cam){
		printf("=============================\n");
		printf("       NEXUS 3D ENGINE       \n");
		printf("=============================\n");
		gr = Graphics_System(name, width, height, cam);
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
			if(gameObjs[i]->s.shaderProg == NULL)
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
	enum keys getInput(){
		return gr.getInput();
	}
	GLFWwindow* getWindow(){
		return gr.GetWindow();
	}
	
};
#endif
