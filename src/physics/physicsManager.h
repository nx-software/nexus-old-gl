#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H
#include <vector>
#include "collider.h"
#include "rigidbody.h"
#include "collide_check.h"
class PhysicsManager{
private:
public:
  std::vector<RigidBody*> rbs;
  void physicsUpdate(){
    for(int i = 0; i < rbs.size(); i++){
      for(int g = 0; g < rbs.size(); g++){
        if(g != i){
          if(collide(*(rbs[i]->bc),*(rbs[g]->bc))){
            //printf("COLLISION COLLISION COLLISION COLLISION\n");
            
          }
        }
      } 
    }
  }
  void addRigidBody(RigidBody* rb){
    rbs.push_back(rb);
  }
};
#endif
