#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "../transform/glm/glm.hpp"
#include "../transform/glm/ext/matrix_transform.hpp"
#include "../transform/glm/gtc/type_ptr.hpp"
/*	
	basic math lesson (adapted from learnopengl.com)
	vectors are cool objects with *magnitude* and *direction* like 5 mph east
	         /\              <- very cool arrow
	         /
	        /  
	now we can find the dot product
	whats a dot product????/??///// dikf gidjg
	it takes two vector and returns a scaler, like the equation for work
	W = F(force, a vector) * D (distance, a vector) * cos theta(the angle)
	dot product equation is 
	P = V * V * cos theta
	i see some simallarites here
*/
// basic transforms (just call glm::rotate)
glm::mat4 tr_rotate(glm::mat4 original, float degrees, glm::vec3 axis){
	return glm::rotate(original, glm::radians(degrees), axis);
}
glm::mat4 tr_translate(glm::mat4 original, glm::vec3 target){
	return glm::translate(original, target);
}
glm::mat4 tr_scale(glm::mat4 original, float factor){
	return glm::scale(original, glm::vec3((float)factor));
}
#endif
