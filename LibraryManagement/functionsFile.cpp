#include "functionsFile.h"
#define _DIR_DATA_FOLDER "Release/Database/"


FILE *openFile(char *nameFile, char *mode){

	char *dirFile = new char(strlen((char*)_DIR_DATA_FOLDER) + 10);
	strcat(dirFile,_DIR_DATA_FOLDER);
	strcat(dirFile, nameFile);

	FILE *ptrFile = fopen(dirFile, mode);
	return ptrFile;
}
