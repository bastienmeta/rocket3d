#ifndef _rigidbody_h
#define _rigidbody_h_

#include <memory>
#incluide <glm/glm.hpp>

class RigidBody{
public:
    virtual bool collides(std::shared_ptr<RigidBody> other) = 0;
    virtual glm::vec3 normal_impulse(std::shared_ptr<RigidBody> other) = 0;
}

#endif
