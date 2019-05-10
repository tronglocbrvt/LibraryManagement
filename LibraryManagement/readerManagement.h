#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "commonFunction.h"
#include "LibraryManagement.h"


char *getNationalID();

Readers *findReaderWithNationID(const FILE *&fileReader, char *&personID);	// Tìm kiếm đọc giả theo CMND

Readers *findReaderWithName(const FILE *&fileReader, char *&personName);	// Tìm kiếm đọc giả theo họ tên
void findListReaderWithName(const FILE *&fileReader, char *&personName, LLNodeReader *&lsReader); // Tìm kiếm đọc giả theo họ tên và thêm vào danh sách

Readers *getTheLastReader(const FILE *&fileReader); // Lấy thông tin đọc giả cuối cùng trong file, trả về null nếu file rỗng.

void printfReader(const Readers &reader); // in thông tin đọc giả
bool printfAllReader(const FILE *&fileReader);	// đọc toàn bộ thông tin đọc giả từ file và in ra -> không đưa vào link list

bool printfAllReader(const LLNodeReader *&ls); // int ra thông tin đọc giả từ Link List khi đã có Link List

bool getAllReaderToLL(const FILE *&fileReader, LLNodeReader *&ls);	// đọc toàn bộ thông tin đọc giả từ file nhưng không in ra -> đưa vào link list

Readers *setReaderInf(char *readerID); // tạo thông tin 1 đọc gỉa
bool addAnInfToFile(const FILE *fileReader, const Readers *reader);	// thêm thông tin đọc giả vào file

bool editReaderInf(Readers *reader); // sửa thông tin đọc giả

bool askToUpdateReaderToFile();	// cập nhật thông tin đọc giả vào file - có hỏi có chắc chắn muốn cập nhật không

	// 2 trường hợp: 1: cập nhập bằng linklist, 2: cập nhật trực tiếp

bool viewInfAReader(FILE *fileReader); // Xem thông tin của một người cụ thể

bool deleteReader(const FILE *&fileReader, const Readers *&reader); // xoá một độc giả

bool editReaderInfToFile(FILE *fileReader){	// chỉnh sửa thông tin đọc giả
	Readers	*reader = InitNode();
	LLNodeReader *&lsReader = Init();
	
	if (fileReader == NULL || getTheLastReader(fileReader) == NULL)
	{
		return 0;
	}

	int choice = 0;
	char *StrGetFrmUser = new char();

	do {
		choice = getNumberPressKey(printfSubMenuReaderManagement());
		strcpy(StrGetFrmUser, getStringFrmUser((char*)"Nhap thong tin tim kiem"));

		switch (choice){
			case 1: // tìm kiếm theo CMND
				*reader = *findReaderWithID(fileReader, StrGetFrmUser);
				if (reader == NULL)
				{
					printf("Doc gia nay khong ton tai.\n");
					system("pause");
					continue;
				}
				break;
			case 2: // tìm kiếm theo tên
				findListReaderWithName(fileReader, StrGetFrmUser, lsReader);
				if (lsReader->pHead == NULL)
				{
					printf("Doc gia nay khong ton tai.\n");
					system("pause");
					continue;
				}
				break;
		}
		system("cls");
	}while (choice != 0);

	switch (askToUpdateReaderToFile()){
		case 1: // có
			if (reader != NULL)
			{
				deleteReader(fileReader, reader);
			}
			else if (lsReader->pHead != NULL)
			{
				deleteReader(fileReader, lsReader->pHead);
			}
			else return 0;
			break;
		default: // không
			return 0;
	}
	return 1;

}
bool deleteReaderInfToFile(FILE *fileReader);	// xoá thông tin một độc giả - hàm khởi chạy -- lọc >> doing here

bool addNewReaderInfToFile(FILE *fileReader);  // thêm độc giả vào database

void runReaderManagement(){

	FILE *fileReader = fopen("Release/Reader/databaseReader.bin", "rb");
	if (fileReader == NULL)
	{
		FILE *fileReader = fopen("Release/Reader/databaseReader.bin", "wb");
	}

	int choice = 0;
	do {
		choice = getNumberPressKey(printfMenuReaderManagement());
		switch (choice){
			case 1:
				printfAllReader(fileReader);
				break;
			case 2: // printf("2. Them doc gia.\n");
				addNewReaderInfToFile(fileReader);
				break;
			case 3: // printf("3. Chinh sua thong tin mot doc gia.\n");
			
				break;
			case 4: // printf("4. Xoa thong tin mot doc gia.\n");
				deleteReaderInfToFile(FILE *fileReader);
				break;
			case 5:
				viewInfAReader(fileReader);
				break;
			default:
				break;
		}
	}while (choice != 0);

}


