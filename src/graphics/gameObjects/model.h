#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "../textures/stb_image.h"
#ifndef MODEL_H
#define MODEL_H
class Model{
	public:
		Model(char* path){
			load(path);
			printf("Model loaded from path %s has %d meshes.\n",path, meshes.size());
		}
		Model(){
		};
		void Draw(Shader &shader){
			for(unsigned int i = 0; i < meshes.size(); i++){
				meshes[i].Draw(shader);
			}
		}
	private:
		std::vector<Mesh> meshes;
		std::string dir;
		std::vector<Texture> txLoad;
		void load(std::string path){
			Assimp::Importer import;
			const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
			if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
				// error
				printf("Error loading model: %s\n", import.GetErrorString());
				exit(1);
			}
			dir = path.substr(0, path.find_last_of('/'));
			procNode(scene->mRootNode, scene);
		}
		void procNode(aiNode* node, const aiScene *scene){
			for(unsigned int i = 0; i < node->mNumMeshes; i++){
				aiMesh *AIme = scene->mMeshes[node->mMeshes[i]];
				meshes.push_back(procMesh(AIme, scene));
			}
			// keep doin for the nodes children
			for(unsigned int i = 0; i < node->mNumChildren; i++){
				procNode(node->mChildren[i], scene); // recursion?????
			}
		}
		Mesh procMesh(aiMesh* mesh, const aiScene *scene){
			std::vector<Vertex> verts;
			std::vector<unsigned int> inds;
			std::vector<Texture> texs;
			
			for(unsigned int i = 0; i < mesh->mNumVertices; i++){
				Vertex v;
				// process the info
				glm::vec3 vec;
				vec.x = mesh->mVertices[i].x;
				vec.y = mesh->mVertices[i].y;
				vec.z = mesh->mVertices[i].z;
				// get the normals
				v.Pos = vec;
				vec.x = mesh->mNormals[i].x;
				vec.y = mesh->mNormals[i].y;
				vec.z = mesh->mNormals[i].z;
				v.Normal = vec;
				// tex coords
				if(mesh->mTextureCoords[0]){
					glm::vec2 ve;
					ve.x = mesh->mTextureCoords[0][i].x;
					ve.y = mesh->mTextureCoords[0][i].y;
					v.TexCoord = ve;
				}else
					v.TexCoord = glm::vec2(0.0f,0.0f); // none
				verts.push_back(v);
			}
			// indices
			for(unsigned int i = 0; i < mesh->mNumFaces; i++){
				aiFace face = mesh->mFaces[i];
				for(unsigned int j = 0	; j < face.mNumIndices; j++){
					inds.push_back(face.mIndices[j]);
				}
			}
			// materials
			if(mesh->mMaterialIndex >= 0){
				aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];
				std::vector<Texture> diffMap = loadMatTexs(mat, aiTextureType_DIFFUSE, "texture_diffuse");
				texs.insert(texs.end(), diffMap.begin(), diffMap.end());
				std::vector<Texture> specMap = loadMatTexs(mat, aiTextureType_SPECULAR, "texture_specular");
				texs.insert(texs.end(), specMap.begin(), specMap.end());
				printf("TEXS SIZE %d mesh->mMaterialIndex %d\n",texs.size(), mesh->mMaterialIndex);
			}
			return Mesh(verts, inds, texs);
		}
		std::vector<Texture> loadMatTexs(aiMaterial *mat, aiTextureType type, std::string tName){
			printf("loadMatTexs called\n");
			std::vector<Texture> textures;
			//printf("%s type has cound %d\n",tName.c_str(),mat->GetTextureCount(type));
			for(unsigned int i = 0; i < mat->GetTextureCount(type); i++){
				aiString str;
				mat->GetTexture(type, i, &str);
				bool d = false;
				for(int j = 0; j < txLoad.size(); j++){
					printf("%s vs %s\n",txLoad[j].path, str.C_Str());
					if(std::strcmp(txLoad[j].path, str.C_Str()) == 0){
						d = true;
						break;
					}
				}
				if(!d){
					Texture te;
					te.id = TextureFromFile(str.C_Str(), dir, false);
					te.type = tName.c_str();
					te.path = str.C_Str();
					textures.push_back(te);
					txLoad.push_back(te);
				}
			}
			printf("txLoad length was %d\n", txLoad.size());
			return textures;
		}
		unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma){
		    std::string filename = std::string(path);
		    filename = directory + '/' + filename;
		    unsigned int textureID;
		    glGenTextures(1, &textureID);
		    int width, height, nrComponents;
		    stbi_set_flip_vertically_on_load(true);
		    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
		    if (data){
			GLenum format;
			if (nrComponents == 1)
			    format = GL_RED;
			else if (nrComponents == 3)
			    format = GL_RGB;
			else if (nrComponents == 4)
			    format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		    }
		    else{
			printf("Texture load failed at %s\n", path);
			stbi_image_free(data);
		    }

		    return textureID;
		}
};
#endif
