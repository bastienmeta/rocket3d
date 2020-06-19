#include "../include/mechanics.h"
#include<cmath>

glm::vec3 Mechanics::Newton::compute_acceleration(std::shared_ptr<SpaceObject> obj, std::shared_ptr<SpaceObject> other){
    glm::vec3 appart = other->get_position() - obj->get_position();
    glm::vec3 acc = glm::normalize(appart);
    double norm = 0.5 * G * other->get_mass() / pow(appart.length(), 2);
    return (float)norm * acc;
}
