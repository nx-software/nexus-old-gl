#include "../src/engine.h"
#include "../src/physics/box_collider.h"
#include "../src/physics/collider.h"
#include "../src/physics/collide_check.h"
#include "../src/graphics/objread.h"
#include "../src/physics/physicsManager.h"
#include <GLFW/glfw3.h>
#include <vector>
int main(){
	// create main camera
	Camera cam = Camera(0.0f,0.0f,3.0f);
	Nexus nx = Nexus("Electro Corp - Nexus 3d Engine Example Game",800.0f,600.0f, &cam);
	GameObject triangle = GameObject("model1","exampleGame/teapot.obj", "exampleGame/shaders/vs","exampleGame/shaders/fs","exampleGame/textures/wall.jpg");
	nx.addObject(&triangle);
	nx.compileShaders();
	while(1){
		nx.updateGraphics();
	}
}
