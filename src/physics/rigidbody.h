#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include "../graphics/transform/transform.h"
class RigidBody{
private:
public:
  glm::vec3 velocity = glm::vec3(0.0f,0.0f,0.0f);
  glm::vec3 angluarVelocity = glm::vec3(0.0f,0.0f,0.0f);
  Box_collider* bc;
  bool useGravity = true;
  RigidBody(Box_collider* bc){
    this->bc = bc;
  }
  void rigidBodyCalculate(void){//(Box_collider* hit){
    /*if(hit){
      
    }else{*/
       tr_translate(this->bc->transform,glm::vec3(0.0f,-9.8f,0.0f));
    //}
  }
};
#endif