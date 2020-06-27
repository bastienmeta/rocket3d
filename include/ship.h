#ifndef _ship_h_
#define _ship_h_

#include "spaceobject.h"

class Ship : public SpaceObject{
public:
    Ship(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> mat, double mass, double scale);
    glm::vec3 get_direction();
    void thrust(float dt, float speed);
    void yaw(double a, float dt, float speed);
    
private:
    float power = 1e-14;
};

#endif
