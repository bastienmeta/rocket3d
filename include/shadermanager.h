#ifndef shader_manager_h
#define shader_manager_h

#include "shader.h"
#include <memory>
#include <map>

class ShaderManager{
public:
    ShaderManager(){
        shaders["advanced_blinn"] = std::make_shared<Shader>("../../shaders/vs.glsl", "../../shaders/advanced_blinn_fs.glsl");
    }
    
    std::shared_ptr<Shader> get(std::string key){
        return shaders[key];
    }
    
private:
    std::map<std::string, std::shared_ptr<Shader>> shaders;
};

#endif
