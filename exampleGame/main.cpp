#include "../engine.h"

int main(){
	//Shader shader = Shader("vShader.vf","fShader.ff");
	Nexus nx = Nexus("Nexus 3D Engine Demo",800,600);
	float vertic[] = {
		-0.5, -0.5, 0.0f,
		0.5, -0.5, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	GameObject triangle = GameObject(vertic,"vShader.vf","fShader.ff");
	nx.addObject(triangle);
	nx.compileShaders();
	nx.updateBackground(0.3,0.4,0.7,1);
	while(1)
		nx.updateGraphics();
}
