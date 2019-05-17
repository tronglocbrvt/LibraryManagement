#include "functionsFile.h"


FILE *openFile(char* dir, char *nameFile, char *mode){

	char *dirFile = new char(strlen(dir) + 20);
	strcat(dirFile,dir);
	strcat(dirFile, nameFile);

	FILE *ptrFile = fopen(dirFile, mode);
	return ptrFile;
}
