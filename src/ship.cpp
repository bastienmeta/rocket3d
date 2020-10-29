#define GLM_FORCE_SWIZZLE
#include "../include/ship.h"

#include <glm/gtx/string_cast.hpp>
#include <iostream>

Ship::Ship(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> mat, double mass, double scale)
:SpaceObject(mesh, mat, mass, scale)
{
    glm::vec3 x = glm::vec3(1.0, 0.0, 0.0);
    rotate(x, -M_PI/2);
    rotation_axis = glm::normalize((R * glm::vec4(0.0, 0.0, 1.0, 1.0)).xyz());
    rotation_speed = 0;
}

glm::vec3 Ship::direction(){
    return glm::normalize((R * glm::vec4(0.0, 0.0, 1.0, 1.0)).xyz());
}

void Ship::thrust(){
    glm::vec3 acc = thrust_power * direction();
    register_acceleration(acc);
}

void Ship::yaw(Direction d){
    if(d == LEFT)
        register_rotation(-rcs_power * angular_momentum());
    else
        register_rotation(rcs_power * angular_momentum());
}

double Ship::angular_momentum(){
    return mass * radius * radius;
}

#undef GLM_FORCE_SWIZZLE
