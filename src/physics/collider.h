#ifndef COLLIDER_H
#define COLLIDER_H
#include "../graphics/transform/glm/glm.hpp"
#include "../graphics/gameObjects/gameObject.h"
class Box_collider{
private:
public:
	glm::mat4 transform;
	GameObject* gm;
	Box_collider(GameObject* gm){
		this->gm = gm;		
	}
	void update(){
		if(gm){
			this->transform = gm->transform; 
		}	
	}
};
#endif
