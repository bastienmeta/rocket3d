#include <stdlib.h>
#include <iostream>

#include "../include/window.h"
#include "../include/mechanics.h"

Window::Window()
{
    if (!glfwInit()){
        std::cout << "Failed to init GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    #ifdef __APPLE__
        glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #endif
}

Window::Window(int width, int height)
:Window()
{
    window = glfwCreateWindow(width, height, "rocket game", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        std::cout << "Failed to create GLFW window" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGL()) {
        std::cout << "Failed to load OpenGL" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    event_manager = new EventManager();
    scene = new Scene();
    
//    EventManager::Callback cb = std::bind(&Scene::press, scene);
//    event_manager->add_binding(GLFW_KEY_SPACE, cb);
    
    time_last_rendered = Clock::now();
}

Window::~Window(){
    glfwTerminate();
}

void Window::main_loop(){
    std::shared_ptr<Ship> ship = scene->ship;
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    
    double leftover = 0.0;
    while (!glfwWindowShouldClose(window))
    {
        auto now = Clock::now();
        double dt = leftover + std::chrono::duration_cast<std::chrono::milliseconds>(now - time_last_rendered).count();


        if(dt > 1000/60.0){
            leftover = dt - 1000/60.0;
            dt = 1000/60.0;
            
            time_last_rendered = now;
            
            scene->physics_step(dt);
            scene->render();
            
            int state = glfwGetKey(window, GLFW_KEY_SPACE);
            if (state == GLFW_PRESS)
                ship->thrust();
            
            state = glfwGetKey(window, GLFW_KEY_LEFT);
            if (state == GLFW_PRESS)
                ship->yaw(Ship::LEFT);
            
            state = glfwGetKey(window, GLFW_KEY_RIGHT);
            if (state == GLFW_PRESS)
                ship->yaw(Ship::RIGHT);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
}
