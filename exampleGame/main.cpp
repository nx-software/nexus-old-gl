#include "../engine.h"

int main(){
	Nexus nx = Nexus("Nexus 3D Engine Demo",800,600);
	float vert[] = {                         // tex coords
	     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
	     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  
	    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.5f, 1.0f,   
	};
	// GAMEOBJECT REQUIRES:      model name|vertices|vertex shader|frag shader|texture name
	GameObject triangle = GameObject("model1",vert,"vShader.vf","fShader.ff","left.jpg");
	nx.addObject(triangle);
	nx.compileShaders();
	nx.updateBackground(0.3,0.4,0.7,1);
	while(1)
		nx.updateGraphics();
}
