#include "../include/eventmanager.h"

EventManager::EventManager(){}

void EventManager::add_binding(int key, Callback& callback){
    key_press_callbacks[key] = callback;
}

void EventManager::key_press(int key){
    key_press_callbacks[key]();
}
