/*
	Main file for the Nexus Editor
*/
#include "../engine.h"

int main(){
	Camera cam = Camera(0.0f,0.0f,3.0f);
	// Create main window
	Nexus nx = Nexus("Nexus 3D Map Editor",1080,720,cam);
	while(1){
		nx.updateGraphics();
	}
}
