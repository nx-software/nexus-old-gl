#ifndef UTILS_H
#define UTILS_H
void throwError(char* name, char* Htext, char* Stext){
	// size
	int size = 0;
	if(strlen(name) > size)
		size = strlen(name);
	if(strlen(Htext) > size)
		size = strlen(Htext);
	if(strlen(Stext) > size)
		size = strlen(Stext);
	// title bar
	for(int i = 0; i < (size - strlen(name))/2; i++)
		printf("=");
	printf("%s",name);
	for(int i = 0; i < (size - strlen(name))/2; i++)
		printf("=");
	printf("\n");
}
#endif
