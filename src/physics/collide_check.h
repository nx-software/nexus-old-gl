#ifndef COLLIDE_CHECK_H
#define COLLIDE_CHECK_H
#include "collider.h"
#include "../graphics/transform/glm/gtx/matrix_decompose.hpp"
bool collide(Box_collider a, Box_collider b){
	glm::mat4 a_transform = a.transform;
	glm::mat4 b_transform = b.transform;
	// get matrix
	glm::vec3 a_scale;
	glm::quat a_rotation;
	glm::vec3 a_translation;
	glm::vec3 a_skew;
	glm::vec4 a_perspective;
	glm::decompose(a_transform, a_scale, a_rotation, a_translation, a_skew, a_perspective);

	glm::vec3 b_scale;
	glm::quat b_rotation;
	glm::vec3 b_translation;
	glm::vec3 b_skew;
	glm::vec4 b_perspective;
	glm::decompose(b_transform, b_scale, b_rotation, b_translation, b_skew, b_perspective);
  
	float a_centerX = a_translation[0];
	float a_centerY = a_translation[1];
	float a_centerZ = a_translation[2];
	
	float b_centerX = b_translation[0];	
	float b_centerY = b_translation[1];
	float b_centerZ = b_translation[2];	
	/*printf("DEBUG FOR COLLISION:\n");
	printf("%f,%f,%f\n%f,%f,%f\n",a_centerX,a_centerY,a_centerZ,b_centerX,b_centerY,b_centerZ);
	printf("SCALE FOR OBJECTS\n%f %f %f\n%f %f %f\n",a_scale.x, a_scale.y, a_scale.z, b_scale.x, b_scale.y, b_scale.z);*/

  
	//glm::vec3 centerToCenter = glm::vec3(a_centerX - b_centerX, a_centerY - b_centerY, a_centerZ - b_centerZ);

  
  
	//float projectionOfCenter = glm::dot(centerToCenter, glm::vec3(1,-1,1));

  //printf("PRC = %d\n",projectionOfCenter);
  
	//return false;
	float a_s = a_scale.x / 2.0f;
	float b_s = b_scale.x / 2.0f;
	return (
		a_centerX - a_s  <= b_centerX + b_s &&
		a_centerX + a_s >= b_centerX - b_s &&
		a_centerY - a_s <= b_centerY + b_s &&
		a_centerY + a_s  >= b_centerY - b_s &&
		a_centerZ - a_s <= b_centerZ + b_s &&
		a_centerZ + a_s  >= b_centerZ - b_s
	);
}

#endif
