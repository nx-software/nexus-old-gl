#include "../engine.h"
#include "../graphics/objread.h"
// for menu
#include "../graphics/gui/imgui.h"
//#include "../graphics/gui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <vector>
int main(){
	// create main camera
	Camera cam = Camera(0.0f,0.0f,3.0f);
	Nexus nx = Nexus("Electro Corp - Nexus 3d Engine Example Game",800.0f,600.0f, &cam);	
	float vert[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    	};
    	objreader obj = objreader("exampleGame/teapot.obj");
	// GAMEOBJECT REQUIRES:      model name|vertices|vertex shader|frag shader|texture name
	std::vector<int> triType, lightType;
	triType.push_back(3);
	triType.push_back(3);
	triType.push_back(2);
	lightType.push_back(3);
	lightType.push_back(3);
	GameObject triangle = GameObject("model1",vert, "exampleGame/vs","exampleGame/fs","wall.jpg", triType);
	GameObject lightM = GameObject("light1", vert, "exampleGame/vShader.vf","exampleGame/lfshader.ff", "win.jpg",lightType, glm::vec3(1.0f,1.0f,1.0f));
	printf("Objects created.\n");
	//GameObject tri2 = GameObject("model2",vert, "vShader.vf","fShader.ff","win.jpg");
	nx.addObject(&triangle);
	nx.addObject(&lightM);
	printf("Shaders added.\n");
	//nx.addObject(&tri2);
	nx.compileShaders();
	printf("Shaders compiled.\n");
	lightM.translate(glm::vec3(1.2f, 1.0f, 2.0f));
	lightM.scale(0.5f);
	triangle.scale(10.0f);
	triangle.translate(glm::vec3(0.0f,-0.5f,0.0f));
	//triangle.rotate(45.0f,AXIS_Y);
	nx.updateBackground(0.3,0.4,0.7,1);
	printf("Main loop started\n");
	//nx.setCurrentProgram(triangle);
	//ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	//ImGui_ImplGlfw_InitForOpenGL(nx.getWindow(), true);
	//ImGui_ImplOpenGL3_Init("#version 130");
	while(1){
		//ImGui_ImplOpenGL3_NewFrame();
		//ImGui_ImplGlfw_NewFrame();
		//ImGui::NewFrame();
		//ImGui::Begin("Nexus Engine demo");
		//ImGui::Text("This is a demo of the Nexus engine.");  
		//tri2.rotate(cos(nx.getTime()),AXIS_X);
		//tri2.rotate(tan(nx.getTime()),AXIS_Z);
		//tri2.rotate(cos(nx.getTime()),AXIS_Y);
		//ImGui::End();
		//ImGui::Render();
		nx.updateGraphics();
		//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		lightM.rotate(sin(nx.getTime()),AXIS_X);
		lightM.rotate(cos(nx.getTime()),AXIS_Z);
		lightM.rotate(sin(nx.getTime()),AXIS_Y);
		//lightM.translate(glm::vec3(sin(nx.getTime()),cos(nx.getTime()),sin(nx.getTime())));
		lightM.scale(sin(nx.getTime()));
		triangle.s.setVec3("objectColor",glm::vec3(0.35f,0.5f,0.31f));//, 1.0f, 0.5f, 0.31f);
		triangle.s.setVec3("lightColor", lightM.l.color);
		triangle.s.setVec3("lightPos",lightM.lastPos);
		triangle.s.setVec3("viewPos", cam.transform);
		cam.pointAtGameObject(triangle);
		//cam.updateTransform(sin(nx.getTime()) * 10.0f,0.0f,cos(nx.getTime()) * 10.0f);
		switch(nx.getInput()){
			case nx.KEY_W:
			cam.updateTransform(cam.x + 0.5f, cam.y, cam.z);
			break;
			case nx.KEY_A:
			cam.updateTransform(cam.x, cam.y - 0.5f, cam.z);
			break;
			case nx.KEY_S:
			cam.updateTransform(cam.x, cam.y + 0.5f, cam.z);
			break;
			case nx.KEY_D:
			cam.updateTransform(cam.x - 0.5f, cam.y, cam.z);
			break;
			case nx.KEY_NONE:
			cam.updateTransform(cam.x, cam.y, cam.z);
			break;
			default:
			cam.updateTransform(cam.x, cam.y, cam.z);
			break;
		};
		
	}
	return 0;
}
