#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _DIR_DATA_FOLDER "Release/Database/"
#define _NAME_FILE_READER_ "readerManagement.txt"

// #define _NAME_FILE_VIEW "CurAccount.txt"
// #define _MAX_CHAR_OF_INF_ 32
// #define _END_LINE_MACOS_ 2
// #define _STRING_LOREM ""

FILE *openFile(char *nameFile, char *mode);