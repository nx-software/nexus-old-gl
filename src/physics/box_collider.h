#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H
#include "collider.h"
#include "../graphics/transform/glm/glm.hpp"
#include "../graphics/gameObjects/gameObject.h"
class Box_collider : public Collider{
private:
public:
	glm::mat4 transform;
	/*Box_collider(GameObject* gm){
		this->gm = gm;		
	}*/
	using Collider::Collider;
	void update(){
		if(gm){
			this->transform = gm->transform; 
		}	
	}
};
#endif
