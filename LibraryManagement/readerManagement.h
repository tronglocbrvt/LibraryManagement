#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "commonFunction.h"
#include "LibraryManagement.h"


char *getNationalID();

Readers *findReaderWithID(const FILE *&fileReader, char *&personID);	// Tìm kiếm đọc giả theo CMND

Readers *findReaderWithName(const FILE *&fileReader, char *&personName);	// Tìm kiếm đọc giả theo họ tên

void printfReader(const Readers &reader); // in thông tin đọc giả
bool printfAllReader(const FILE *&fileReader);	// đọc toàn bộ thông tin đọc giả từ file và in ra -> không đưa vào link list

bool printfAllReader(const LLNodeReader *&ls); // int ra thông tin đọc giả từ Link List khi đã có Link List

bool getAllReaderToLL(const FILE *&fileReader, LLNodeReader *&ls);	// đọc toàn bộ thông tin đọc giả từ file nhưng không in ra -> đưa vào link list

Readers *setReaderInf(char *readerID); // tạo thông tin 1 đọc gỉa
bool addAnInfToFile(const FILE *fileReader, const Readers *reader);	// thêm thông tin đọc giả vào file

bool editReaderInf(Readers *reader); // sửa thông tin đọc giả

bool updateReaderToFile(const FILE *fileReader, const Readers *reader){	// cập nhật thông tin đọc giả vào file - có hỏi có chắc chắn muốn cập nhật không
	printf("Ban co chan muon cap nhat khong\n");
	printf("1. Co\n");
	printf("2. Khong\n");

	switch (getNumberPressKey(2,1)){
		case 1:

			return 1;
			break;
		case 2:
			return 0;
			break;
	}
	return 1;
}

	// 2 trường hợp: 1: cập nhập bằng linklist, 2: cập nhật trực tiếp

bool viewInfAReader(FILE *fileReader){
	int choice = 0;
	Readers	*reader = new Readers();
	char *StrGetFrmUser = new char();

	if (fileReader == NULL || reader == NULL)
	{
		return 0;
	}
	do {
		choice = getNumberPressKey(printfSubMenuReaderManagement());
		int getEnter = getchar();
		gets(StrGetFrmUser);

		switch (choice){
			case 1:
				*reader = *findReaderWithID(StrGetFrmUser);
				break;
			case 2:
				*reader = *findReaderWithName(StrGetFrmUser);
				break;
		}

		printfReader(*reader);
	}while (choice != 0);

	return 1;
}


void runReaderManagement(){

	FILE *pFile = fopen("Release/Reader/databaseReader.bin", "rb");
	if (pFile == NULL)
	{
		FILE *pFile = fopen("Release/Reader/databaseReader.bin", "wb");
	}

	int choice = 0;
	do {
		choice = getNumberPressKey(printfMenuReaderManagement());
		switch (choice){
			case 1:
				printfAllReader(pFile);
				break;
			case 2:
				
				break;
			case 3:
			
				break;
			case 4:
			
				break;
			case 5:
				
				break;
		}
	}while (choice != 0);

}


