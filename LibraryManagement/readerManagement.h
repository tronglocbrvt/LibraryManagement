#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "commonFunction.h"
#include "LibraryManagement.h"


void printfReader(Readers reader);

Readers setReaderInf(char *readerID);

Readers editReaderInf(char *readerID);
