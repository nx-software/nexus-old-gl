#include "graphics/graphics.h"

int main(){
	// Create Graphics subsystem and initilize the window
	Graphics_System gr = Graphics_System("Nexus 3D Engine");
	int graphicsInitSuccessFull = gr.initGL();
	if(graphicsInitSuccessFull == -1){
		std::cout<<"Error occured while intilizing window.\n";
		return -1;
	}
	// Main loop
	while(1){
		gr.nextTick();
	}
}
