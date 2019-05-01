#include "functionsFile"

FILE *openFile(char *nameFile, char *mode){

	char *dirFile = new char();
	strcat(dirFile,_DIR_DATA_FOLDER);
	strcat(dirFile, nameFile);

	FILE *ptrFile = fopen(dirFile, mode);
	return ptrFile;
}