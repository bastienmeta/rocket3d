#ifndef event_manager_h
#define event_manager_h

#include <map>
#include <vector>

class EventManager{
public:
    using Callback = std::function<void()>;
    
    EventManager();
    
    void add_binding(int key, Callback& callback);
    void key_press(int key);

private:
    std::map<int, Callback> key_press_callbacks;
};

#endif
