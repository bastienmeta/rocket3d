#ifndef window_h
#define window_h

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <memory>

#include "../include/eventmanager.h"
#include "../include/scene.h"

struct DestroyglfwWin{
    void operator()(GLFWwindow* ptr){
         glfwDestroyWindow(ptr);
    }
};

class Window{
public:
    Window();
    Window(int width, int height);
    ~Window();
    
    void main_loop();
    
private:
    using Clock = std::chrono::high_resolution_clock;
    using Time = std::chrono::high_resolution_clock::time_point;
    
    GLFWwindow* window;
    EventManager* event_manager;
    Scene* scene;
    Time time_last_rendered;
};

#endif

