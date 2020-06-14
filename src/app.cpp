#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "../include/shader.h"
#include "../include/mesh.h"

using namespace glm;

int main()
{
    GLFWwindow* window;
    if (!glfwInit())
        return -1;

#ifdef __APPLE__
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    window = glfwCreateWindow(800, 800, "Coucou", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGL()) {
        exit(EXIT_FAILURE);
    }
    
    Shader shader( "../../shaders/vs.glsl", "../../shaders/fs.glsl" );
    shader.use();
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(.0, .0, .0, .0);
    
    Mesh tchouri("../../meshes/tchouri.off", vec3(0.4, 0.3, 0.1), 2.0);
    
    // lights
    vec3 directionnal_light = vec3(3, 8, 10);
    directionnal_light = glm::normalize(directionnal_light);
    GLuint DirLightID = glGetUniformLocation(shader.ID, "dirlight_world");

    vec3 point_light_pos = vec3(10, 5, 20);
    GLuint PointLightID = glGetUniformLocation(shader.ID, "pointlight_world");

    // matrices
    vec3 camera_position = vec3(2.0, 4.0, 0.0);
    vec3 camera_target = vec3(0.0, 0.0, 0.0);
    vec3 camera_up = vec3(0.0, 1.0, 0.0);
    glm::mat4 Projection = glm::frustum(-1.0, 1.0, -1.0, 1.0, 1.0, 1000.0);
    glm::mat4 View = glm::lookAt(camera_position, camera_target, camera_up);
    glm::mat4 MVP = Projection * View;

    GLuint MatrixID = glGetUniformLocation(shader.ID, "MVP");
    GLuint ViewID = glGetUniformLocation(shader.ID, "V");
    GLuint ProjID = glGetUniformLocation(shader.ID, "P");
    GLuint ColorID = glGetUniformLocation(shader.ID, "mesh_diffuse");
    GLuint CamposID = glGetUniformLocation(shader.ID, "eye_world");
    GLuint ShininessID = glGetUniformLocation(shader.ID, "shininess");

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader.ID);

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(MVP));
        glUniformMatrix4fv(ProjID, 1, GL_FALSE, glm::value_ptr(Projection));
        glUniformMatrix4fv(ViewID, 1, GL_FALSE, glm::value_ptr(View));
        glUniform3fv(CamposID, 1, glm::value_ptr(camera_position));

        glUniform3fv(DirLightID, 1, glm::value_ptr(directionnal_light));
        glUniform3fv(PointLightID, 1, glm::value_ptr(point_light_pos));

        tchouri.setGlBuffers(ColorID, ShininessID);
        tchouri.draw();

        glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
