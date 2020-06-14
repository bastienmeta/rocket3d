#ifndef __MESH_H__
#define __MESH_H__

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace glm;
using namespace std;

bool get_next_uncommented_line(std::ifstream &infile, std::string &result) {
    while(getline(infile,result)) {
        if(result.length() > 1 && result[0] != '#') {
            return true;
        }
    }
    return false;
}

class Mesh{
public:
	vector<vec3> V;
	vector<vec3> Nv;
	vector<vec3> Nf;	
	vec3 color;
	float shininess;
	vector<unsigned int> F;
    bool loaded;
    unsigned int nvertices, nfaces, nedges;	
    GLuint vbo;
    GLuint vao;
    GLuint ebo;
    GLuint nbo;

	Mesh(string path, vec3 color, float shiny=1.0):color(color),shininess(shiny){

		std::cout << path;
		readOFF(path);
		std::cout << "\tV: " << V.size() << "  F: " << F.size() << std::endl;

		glGenVertexArrays(1, &vao);		
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, V.size() * sizeof(glm::vec3), &V[0], GL_STATIC_DRAW);	
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
		glEnableVertexAttribArray(0);

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, F.size() * sizeof(unsigned int), &F[0], GL_STATIC_DRAW);
			
		glGenBuffers(1, &nbo);
		glBindBuffer(GL_ARRAY_BUFFER, nbo);
		glBufferData(GL_ARRAY_BUFFER, Nv.size() * sizeof(glm::vec3), &Nv[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);		
	}

	void setGlBuffers(GLuint color_buf, GLuint shiny_buf){
 		glUniform3fv(color_buf, 1, value_ptr(color));
 		glUniform1fv(shiny_buf, 1, &shininess); 		
	}

	bool readOFF(string path){
	    std::ifstream infile(path);
	    if(!infile.is_open()) {
	        return false;
	    }

	    std::string info;
	    if (!get_next_uncommented_line(infile, info)) {
	        return false;
	    }
	    std::istringstream info_stream;
	    info_stream.str(info); std::string buf;
	    info_stream >> buf >> nvertices >> nfaces >> nedges;

	    V.reserve(nvertices);
	    for(auto i=0; i < nvertices; ++i) {
	        if (!get_next_uncommented_line(infile,info)) {
	            return false;
	        }
	        std::istringstream info_stream(info);
	        glm::vec3 point;
	        info_stream >> point.x >> point.y >> point.z;	        
	        V.emplace_back(point);
	    }

	    Nv.reserve(nvertices);
	    for(auto i=0; i < nvertices; ++i)
        	Nv.emplace_back(vec3(0,0,0));

	    F.reserve(nfaces*3);
	    Nf.reserve(nfaces);
	    for(auto i=0; i < nfaces; ++i) {
	        if (!get_next_uncommented_line(infile,info)) {
	            return false;
	        }
	        std::istringstream info_stream(info);
	        unsigned int n;
	        unsigned int index;
	        info_stream >> n;
	        vec3 points[n];
	        int indices[n];
	        for (auto j = 0; j < n; ++j) {
	            info_stream >> index;
	        	F.emplace_back(index);
	        	points[j] = V[index];
	        	indices[j] = index;
	        }

	        vec3 nml = glm::cross(points[1]-points[0], points[2]-points[0]);
	        Nf.emplace_back(nml);

	        for (auto j = 0; j < n; ++j) 
	        	Nv[indices[j]] += nml;
	    }

	    for(auto i=0; i < nvertices; ++i){
	    	Nv[i] = glm::normalize(Nv[i]);
	    }

	    infile.close();
	    return (loaded = true);
	}	

	void draw(){
		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glDrawElements(GL_TRIANGLES, F.size(), GL_UNSIGNED_INT, 0 );
		glBindVertexArray(0);
	}	
};

#endif
