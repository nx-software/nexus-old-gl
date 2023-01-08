#ifndef TEXTURE_H
#define TEXTURE_H
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
class texture{
public:
	unsigned int textureID;
	int width, height, nrChannels;
	unsigned char *data;
	texture(char* fileName){
		data = stbi_load(fileName, &width, &height, &nrChannels, 0);
		if(!data){
			printf("Error loading filel %s.\n",fileName);
		}	
	}
	texture(){}
};
#endif
