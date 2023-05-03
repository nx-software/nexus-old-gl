#include "../src/engine.h"
#include "../src/physics/box_collider.h"
#include "../src/physics/collider.h"
#include "../src/physics/collide_check.h"
#include "../src/graphics/objread.h"
#include "../src/physics/physicsManager.h"
#include <GLFW/glfw3.h>
#include <vector>

#define DEBUG 1
bool fMouse, pause;
float yaw = -90.0f;
float pitch = 0.0f;
float lX = 0.0f;
float lY = 0.0f;
int main(){
	// create main camera
	Camera cam = Camera(0.0f,0.0f,3.0f);
	Nexus nx = Nexus("Electro Corp - Nexus 3d Engine Example Game",800.0f,600.0f, &cam);
	nx.grabCursor();
	GameObject triangle = GameObject("model1","exampleGame/obj/CasaMedievalC.obj", "exampleGame/shaders/vs","exampleGame/shaders/fs");
	GameObject lightM = GameObject("light1", "exampleGame/obj/CasaMedievalC.obj", "exampleGame/shaders/vShader.vf","exampleGame/shaders/lfshader.ff", glm::vec3(1.0f,1.0f,1.0f));
	triangle.scale(0.3f);
	lightM.scale(0.1f);
	nx.addObject(&triangle);
	nx.addObject(&lightM);
	nx.compileShaders();
	nx.updateBackground(0.3,0.4,0.7,1);
	printf("Loading complete.\n");
	while(1){
		triangle.s.setVec3("objectColor",glm::vec3(0.35f,0.5f,0.31f));//, 1.0f, 0.5f, 0.31f);
		triangle.s.setVec3("lightColor", lightM.l.color);
		triangle.s.setVec3("lightPos",lightM.lastPos);
		triangle.s.setVec3("viewPos", cam.transform);
		nx.updateGraphics();
		if(!pause)
		lightM.translate(glm::vec3(sin(nx.getTime()),cos(nx.getTime()),sin(nx.getTime())));
		switch(nx.getInput()){
			case nx.KEY_W:
			cam.rawUpdate(0.5f * cam.front);
			//triangle.translate(glm::vec3(0.0f,-0.1f,0.0f));
			break;
			case nx.KEY_A:
			cam.rawUpdate(glm::normalize(glm::cross(cam.front, cam.up)) * 0.5f);
			//cam.updateTransform(cam.x, cam.y - 0.5f, cam.z);
			break;
			case nx.KEY_S:
			cam.rawUpdate(-0.5f * cam.front);
			//triangle.translate(glm::vec3(0.0f,0.1f,0.0f));
			break;
			case nx.KEY_D:
			cam.rawUpdate(glm::normalize(glm::cross(cam.front, cam.up)) * -0.5f);
			//cam.updateTransform(cam.x - 0.5f, cam.y, cam.z);
			break;
			case nx.KEY_NONE:
			//cam.updateTransform(cam.x, sin(nx.getTime()), cos(nx.getTime()));
			break;
			case nx.KEY_ENTER:
			pause = !pause;
			default:
			cam.updateTransform(cam.x, cam.y, cam.z);
      
			break;
		};	
		// mouse func
		
		mouseCoords g = nx.getMouse();
		float x = g.x;
		float y = g.y;
		if(fMouse){
			lX = x;
			lY = y;
			fMouse = false; 
		}
		float xOff = x - lX;
		float yOff = y - lY;
		lX = x;
		lY = y;
		float sense = 0.1f;
		xOff *= sense;
		yOff *= sense;
		
		yaw+= xOff;
		pitch = yOff;
		
		if(pitch > 89.0f) pitch = 89.0f;
		if(pitch < -89.0f) pitch = -89.0f;
		
		cam.front = glm::normalize(glm::vec3(cos(glm::radians(yaw)) * cos(glm::radians(pitch)),sin(glm::radians(pitch)), sin(glm::radians(yaw)) * cos(glm::radians(pitch))));
	}
}
