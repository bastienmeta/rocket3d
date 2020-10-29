#include "../include/spaceobject.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>

SpaceObject::SpaceObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> mat, double mass, double scale)
:mesh(mesh), material(mat), mass(mass), acceleration(glm::vec3(0.0, 0.0, 0.0)), new_acceleration(glm::vec3(0.0, 0.0, 0.0)), rotation_axis(glm::vec3(0.0, 1.0, 0.0)), rotation_speed(0.0), radius(scale),
T(glm::mat4(1.0)), R(glm::mat4(1.0)), S(glm::mat4(scale)), model(glm::mat4(1.0))
{
    S[3][3] = 1.0;
}

SpaceObject::~SpaceObject(){
}

void SpaceObject::set_position(glm::vec3 pos){
    position = glm::vec3(0.0,0.0,0.0);
    T = glm::mat4(1.0);
    translate(pos);
}

void SpaceObject::set_velocity(glm::vec3 vel){
    velocity = vel;
}

void SpaceObject::set_rotation(glm::vec3 axis, double speed){
    rotation_axis = glm::normalize(axis);
    rotation_speed = speed;
}

glm::vec3& SpaceObject::get_position(){
    return position;
}

double SpaceObject::get_mass(){
    return mass;
}

double SpaceObject::get_radius(){
    return radius;
}

void SpaceObject::register_rotation(double a){
    rotation_acc += a;
}

void SpaceObject::apply_rotation(double dt){
    rotate(rotation_axis, rotation_speed * dt + rotation_acc * dt * dt);
    rotation_speed += rotation_acc * dt;
    rotation_acc = 0.0;
}

void SpaceObject::register_acceleration(glm::vec3 &a){
    acceleration += a;
}

void SpaceObject::apply_acceleration(double dt){
    // x(t+dt) = x(t) + v(t).dt + a(t).dt^2
    glm::vec3 dp = velocity * (float)dt + acceleration * (float)(dt * dt);
    translate(dp);
    
    // v(t+dt) = v(t) + a(t).dt
    velocity += acceleration * (float)dt;

    acceleration = glm::vec3(0.0, 0.0, 0.0);
}

void SpaceObject::set_uniforms(){
    material->set_uniforms();
}

void SpaceObject::translate(glm::vec3& vec){
    position += vec;
    T = glm::translate(T, vec);
}

void SpaceObject::rotate(glm::vec3& axis, float angle){
    R = glm::rotate(R, angle, axis);
}

void SpaceObject::scale(float factor){
    S = glm::scale(S, glm::vec3(factor, factor, factor));
}

void SpaceObject::scale_xyz(glm::vec3& scale){
    S = glm::scale(S, scale);
}

glm::mat4& SpaceObject::get_model(){
    model = T*R*S;
    return model;
}

GLuint SpaceObject::get_shader_id(){
    return material->get_shader_id();
}

void SpaceObject::draw(){
    mesh->draw();
}

bool SpaceObject::collides(std::shared_ptr<SpaceObject> other){
    float dist = glm::length(other->position - position);
    return dist < other->radius + radius ;
}

// https://en.wikipedia.org/wiki/Inelastic_collision
void SpaceObject::resolve_collision(std::shared_ptr<SpaceObject> other){
    double Cr = 1.0;
    glm::vec3 out = position - other->position;
    glm::vec3 dir = glm::normalize(out);
    float dist = radius - other->radius;
    glm::vec3 disp = (dist - glm::length(out)) * dir;
    translate(disp);

    double normal_impulse = (1.0 + Cr) * (glm::length(other->velocity) - glm::length(velocity)) * mass * other->mass / (mass + other->mass) ;
    
    glm::vec3 dva = (float)(normal_impulse / mass) * dir;
    velocity += dva;
    
    glm::vec3 dvb = (float)(normal_impulse / other->mass) * dir;
    other->velocity += dvb;
}
