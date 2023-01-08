#include "../engine.h"

int main(){
	//Shader shader = Shader("vShader.vf","fShader.ff");
	Nexus nx = Nexus("Nexus 3D Engine Demo",800,600);
	float vert[] = {                         // tex coords
	     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
	     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  
	    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.5f, 1.0f,   
	};
	
	GameObject triangle = GameObject(vert,"vShader.vf","fShader.ff","wall.jpg");
	printf("{MAIN} FRAG: \n%s\n",triangle.s.fShaderSrc);
	nx.addObject(triangle);
	nx.compileShaders();
	nx.updateBackground(0.3,0.4,0.7,1);
	while(1)
		nx.updateGraphics();
}
