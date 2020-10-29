#ifndef _ship_h_
#define _ship_h_

#include "spaceobject.h"

class Ship : public SpaceObject{
public:
    enum Direction {LEFT, RIGHT};
    Ship(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> mat, double mass, double scale);
    void thrust();
    void yaw(Direction d);
    
private:
    float thrust_power = 1e-5;
    float rcs_power = 1e-6;
    
    double angular_momentum();
    glm::vec3 direction();
};

#endif
