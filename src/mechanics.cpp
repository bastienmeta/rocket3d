#include "../include/mechanics.h"
#include <cmath>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

// F = ma
// a = F/m
// F = G.m.m2/d^2
// => a = G.m2/d^2
glm::vec3 Mechanics::compute_gravity_acceleration(std::shared_ptr<SpaceObject> obj, std::shared_ptr<SpaceObject> other){
    glm::vec3 appart = other->get_position() - obj->get_position();
    glm::vec3 acc = glm::normalize(appart);
    double norm = G * other->get_mass() / pow(appart.length(), 2);
    std::cout << norm << std::endl;
    return (float)norm * acc;
}

// F = Ia
// a = F/I
// I = m.r^2
// => a = F/m.r^2
// object has a fixed rotation axis and a single radius
// force is applied at the maximum radius, on the set rotation axis
double Mechanics::compute_angular_acceleration(std::shared_ptr<SpaceObject> obj, double f){
    return f / (obj->get_mass() * pow(obj->get_radius(), 2));
}

// compute orbital speed obj needs to have for it to be in a circular orbit aroung other
double Mechanics::compute_circular_orbit_velocity(std::shared_ptr<SpaceObject> obj, std::shared_ptr<SpaceObject> other){
    double r = glm::length(obj->get_position() - other->get_position());
    std::cout << sqrt(G * (other->get_mass()) / r) << std::endl;
    return sqrt(G * (other->get_mass()) / r);
}
