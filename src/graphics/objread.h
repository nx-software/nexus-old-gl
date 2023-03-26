/*
	obj file reader by Electro-Corp
*/
#ifndef OBJREAD
#define OBJREAD
#include <stdlib.h>
#include <stdio.h>
class objreader{
public:
	//float vert[];

	
	objreader(char* filename){
		
		// openfile
		FILE* fp = fopen(filename, "r");
		if(fp == NULL)
			printf("File %s not found!\n",filename);
		else{
			printf("Loading from file %s...\n",filename);
			fseek(fp, 0L, SEEK_END);
			char data[ftell(fp)];
			int t = ftell(fp);
			char** file = (char**) calloc(ftell(fp), sizeof(char*));
			for (int i = 0; i < ftell(fp); i++ )
			{
			    file[i] = (char*) calloc(300, sizeof(char));
			}
			rewind(fp);
			printf("Size found.\n");
			fread(data, sizeof(data), 1, fp);
			printf("File read.\n");
			// file loaded, now to parse
			int x = 0,y = 0,i = 0;
			while(data[i++]){
				//printf("Data[%d]\n",i);
				if(data[i] == '\n'){y++;x=0;}
				else{
					file[y][x] = data[i];
				}
			}
		}
	}
};
#endif
