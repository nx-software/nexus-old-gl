#ifndef COLLIDE_CHECK_H
#define COLLIDE_CHECK_H
#include "collider.h"
bool collide(Box_collider a, Box_collider b){
	glm::mat4 a_transform = a.transform;
	glm::mat4 b_transform = b.transform;
	
	float a_centerX = a_transform[0].x;
	float a_centerY = a_transform[1].y;
	float a_centerZ = a_transform[2].z;
	
	float b_centerX = b_transform[0].z;	
	float b_centerY = b_transform[1].y;
	float b_centerZ = b_transform[2].z;
	
	printf("%f,%f,%f\n%f,%f,%f\n",a_centerX,a_centerY,a_centerZ,b_centerX,b_centerY,b_centerZ);
	
	glm::vec3 centerToCenter = glm::vec3(a_centerX - b_centerX, a_centerY - b_centerY, a_centerZ - b_centerZ);
	
	float projectionOfCenter = glm::dot(centerToCenter, glm::vec3(1,-1,1));
	return false;
}

#endif
