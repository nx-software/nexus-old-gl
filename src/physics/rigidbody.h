#ifndef RIGIDBODY_H
#define RIGIDBODY_H
class RigidBody{
private:
public:
  float yVelocity, xVelocity, zVelocity;
  Box_collider* bc;
  bool useGravity = true;
  RigidBody(Box_collider* bc){
    this->bc = bc;
  }
};
#endif