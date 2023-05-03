#include "../transform/glm/glm.hpp"
#include "../transform/glm/ext/matrix_transform.hpp"
#include "../transform/glm/gtc/type_ptr.hpp"
#ifndef MESH_H
#define MESH_H

typedef unsigned int uint;
// Vertex
struct Vertex{
	glm::vec3 Pos; // self explanatory
	glm::vec3 Normal; // Normal coords
	glm::vec2 TexCoord; // Coords for texture
};
// Texture
struct Texture{
	unsigned int id;
	char* type;
	char* path;
};

// Mesh
class Mesh{
	public:
		std::vector<Vertex> verts;
		std::vector<unsigned int> inds;
		std::vector<Texture> texs;
		Mesh(std::vector<Vertex> v, std::vector<unsigned int> i, std::vector<Texture> t){
			this->verts = v;
			this->inds = i;
			this->texs = t;
			setup();
		}
		
		void Draw(Shader &shader){
			unsigned int diffuseN = 1;
			unsigned int specN = 1;
			//printf("(TX,V,I) = %d,%d,%d\n",texs.size(),verts.size(), inds.size());
			for(uint i = 0; i < texs.size(); i++){
				glActiveTexture(GL_TEXTURE0 + i);
				std::string num;
				std::string name = texs[i].type;
				if(name ==  "texture_diffuse")
					num = std::to_string(diffuseN++);
				else if(name == "texture_specular")
					num = std::to_string(specN++);
				shader.setInt(("material." + std::string(name) + std::string(num)).c_str(), i);
				glBindTexture(GL_TEXTURE_2D, texs[i].id);
			}
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, inds.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	private:
		// stuff for render (remebr?)
		unsigned int VAO, VBO, EBO;
		
		void setup(){
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO); // create gl buffer for the VBO
			glGenBuffers(1, &EBO); // create gl buffer fpr tje EBO
			
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO); // whenever we add to the array buffer
			glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), &verts[0], GL_STATIC_DRAW); // copy VBO to array buffer
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, inds.size() * sizeof(unsigned int), &inds[0], GL_STATIC_DRAW);
			// vertex pos
			glEnableVertexAttribArray(0);
    			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex), (void*)offsetof(Vertex,Normal));
    			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,  sizeof(Vertex), (void*)offsetof(Vertex,TexCoord));
			
			glBindVertexArray(0);
			
			
			printf("Textures loaded %d\n",texs.size());
			
		}
			
};
#endif
