#ifndef CAMERA_H
#define CAMERA_H
// includes for glm
#include "../transform/glm/glm.hpp"
#include "../transform/glm/ext/matrix_transform.hpp"
#include "../transform/glm/gtc/type_ptr.hpp"
class camera{
private:
public:
	glm::vec3 transform = glm::vec3(0.0f,0.0f,3.0f);
	// use this in cutscenes, perhaps point at a gameObject?
	glm::vec3 target = glm::vec3(0.0f, 0.0f,0.0f);
	glm::vec3 dir = glm::normalize(transform - target); // keep in mind this is the reverse of the "direction"
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::normalize(glm::cross(up, dir));
	// camera up axis
	glm::vec3 camUp = glm::cross(dir, right);
};
#endif
