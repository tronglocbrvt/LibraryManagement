#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "commonFunction.h"
#include "LibraryManagement.h"

char *getNationalID();
void printfReader(Readers reader);

Readers setReaderInf(char *readerID);

bool editReaderInf(Readers *reader);
