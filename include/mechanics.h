//
//  newton.h
//  app
//
//  Created by bwailly on 16/06/2020.
//

#ifndef mechanics_h
#define mechanics_h

#include <glm/glm.hpp>
#include <memory>

#include "spaceobject.h"

namespace Mechanics{
    const double G = 6.67430e-11;
    glm::vec3 compute_gravity_acceleration(std::shared_ptr<SpaceObject> obj, std::shared_ptr<SpaceObject> other);
    double compute_angular_acceleration(std::shared_ptr<SpaceObject> obj, double push);
    double compute_circular_orbit_velocity(std::shared_ptr<SpaceObject> obj, std::shared_ptr<SpaceObject> other);
};
#endif /* newton_h */
