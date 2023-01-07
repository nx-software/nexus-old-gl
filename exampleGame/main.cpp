#include "../engine.h"

int main(){
	// shaders
	char *vertexShader = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";
	char *fragShader = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
	"}\0";
	Shader vertex = Shader(vertexShader);
	Shader frag = Shader(fragShader);
	Nexus nx = Nexus("Nexus 3D Engine Demo",800,600);
	float vertic[] = {
		-0.5, -0.5, 0.0f,
		0.5, -0.5, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	GameObject triangle = GameObject(vertic);
	triangle.addVShader(vertex);
	triangle.addFShader(frag);
	nx.addObject(triangle);
	nx.compileShaders();
	nx.updateBackground(0.3,0.4,0.7,1);
	while(1)
		nx.updateGraphics();
}
