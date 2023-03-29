#ifndef COLLIDER_H
#define COLLIDER_H
#include "../graphics/transform/glm/glm.hpp"
#include "../graphics/gameObjects/gameObject.h"
class Collider{
private:
public:
	GameObject* gm;
	Collider(GameObject* gm){
		this->gm = gm;		
	}
};
#endif
