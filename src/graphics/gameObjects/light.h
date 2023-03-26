#ifndef LIGHT_H
#define LIGHT_H
#include "../transform/glm/glm.hpp"
#include "../transform/glm/ext/matrix_transform.hpp"
#include "../transform/glm/gtc/type_ptr.hpp"
class Light{
public:
	glm::vec3 color = glm::vec3(-99.0f,-99.0f,-99.0f);
	Light(glm::vec3 color){
		this->color = color;
	}
	Light(){}
};
#endif
