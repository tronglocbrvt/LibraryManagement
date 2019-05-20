#include "readerManagement.h"
#include "commonFunction.h"
#include "linkedListReaders.h"
#include "functionsFile.h"


char* getNationalID();
Readers *findReaderWithNationID(char *personID)	// Tìm kiếm độc giả theo CMND
{
	Readers *reader = new Readers;

	FILE *fileReader = fopen(_DIR_DATA_FOLDER_READER, "rb");
	
	while (fread(reader, sizeof(Readers), 1, fileReader) != 0){
		if (strcmp(reader->NationID, personID) == 0)
		{
			fclose(fileReader);
			return reader;
		}
	}

	fclose(fileReader);
	return NULL;
}

Readers *findReaderWithEmail(char *Email)	// Tìm kiếm độc giả theo Email
{
	Readers *reader = new Readers;

	FILE* fileReader = fopen(_DIR_DATA_FOLDER_READER, "rb");

	if (fileReader == NULL)
	{
		return NULL;
	}

	while (fread(reader, sizeof(Readers), 1, fileReader) != 0){
		if (strcmp(reader->Email, Email) == 0)
		{
			fclose(fileReader);
			return reader;
		}
	}

	fclose(fileReader);
	return NULL;
}

Readers *findReaderWithID(char *ID)	// Tìm kiếm độc giả theo ID
{
	Readers *reader = new Readers;

	FILE* fileReader = fopen(_DIR_DATA_FOLDER_READER, "rb");

	if (fileReader == NULL)
	{
		return NULL;
	}


	while (fread(reader, sizeof(Readers), 1, fileReader) != 0){
		if (strcmp(reader->ID, ID) == 0)

		{
			fclose(fileReader);
			return reader;
		}
	}

	fclose(fileReader);
	return NULL;
}

void viewAllReader()	// đọc toàn bộ thông tin độc giả từ file và in ras
{
	Readers *reader = new Readers;

	FILE* fileReader = fopen(_DIR_DATA_FOLDER_READER, "rb");

	if (fileReader == NULL || reader == NULL)
	{
		return;
	}

	while (fread(reader, sizeof(Readers), 1, fileReader) != 0){
		viewInfAReader(*reader);
	}
	Sleep(1000);
	fclose(fileReader);

	delete reader;
}

bool findListReaderWithName(char *personName, LLNodeReader &lsReader){	// Tìm kiếm đọc giả theo họ tên trả về danh sách
	Readers *reader = new Readers;

	if (reader == NULL)
		return 0;

	FILE* fileReader = fopen(_DIR_DATA_FOLDER_READER, "rb");

	if (fileReader == NULL)
	{
		return 0;
	}

	while (fread(reader, sizeof(Readers), 1 ,fileReader) != 0){
		if (strcmp(reader->Fullname, personName) == 0)
		{
			// thêm vào danh sách
			addAtTail(lsReader, *reader);
		}

	}

	delete reader;
	fclose(fileReader);
	return true;
}


bool printReaderFromLL(LLNodeReader ls){ // in ra thông tin độc giả từ Linked List
	NodeReader *pNow = new NodeReader;
	if (pNow == NULL)
	{
		return 0;
	}

	pNow = ls.pHead;

	int index = 0;
	while(pNow != NULL){
		printf("\nDoc gia thu %d:\n", ++index);
		viewInfAReader(pNow->reader);
		pNow = pNow->pNext;
	}

	return 1;
}

Readers addReader()
{
	Readers reader;
	Readers *temp = new Readers;
	FILE *f = fopen(_DIR_DATA_FOLDER_READER, "rb");

	long ID = 1l;
	fseek(f, 0L, SEEK_END);
	long size = ftell(f);

	char *strID = new char[9];
	if (size == 0)
	{
		// ID = 1;
		strcpy(strID, (char*)"00000001");
	}
	else
	{
		rewind(f);
		while (fread(temp, sizeof(Readers), 1, f) != 0)
		{
			ID++;
		}
	}

	fclose(f);

	// strcpy(reader.ID, toStr(ID));
	if ((strcmp(strID, (char*)"00000001")))
	{
		strcpy(strID, temp->ID);
		plusOneIntoAString(strID);
	}
	delete temp;
	strID[8] = '\0';
	strcpy(reader.ID, strID);
	delete[] strID;

	printf("ID:\t%s\n", reader.ID);
	flushall();
	printf("Nhap Ho va Ten: ");
	gets(reader.Fullname);
	getNationalID(reader.NationID);
	getBirthday(reader.Birthday);
	getSex(reader.Sex);
	printf("Nhap Email: ");
	gets(reader.Email);
	printf("Nhap dia chi: ");
	gets(reader.Address);
	reader.creatCard = getToday();
	reader.expireCard = getExpiredDay(reader.creatCard);
	return reader;
}

int askToUpdateReaderToFile() // cập nhật thông tin đọc giả vào file - có hỏi có chắc chắn muốn cập nhật không?
{	
	printf("Ban co chan muon cap nhat khong\n");
	printf("1. Co\n");
	printf("2. Khong\n");

	return (getNumberPressKey(2, 1));
}

bool writeInfReaderToFile() // thêm độc giả vào database
{
	Readers	reader = addReader();
	Readers *temp1 = findReaderWithNationID(reader.NationID);
	Readers *temp2 = findReaderWithEmail(reader.Email);

	switch (askToUpdateReaderToFile()){
	case 1:
		if (temp1 != NULL || temp2 != NULL)
		{
			printf("Doc gia nay da ton tai do trung CMND/Email voi doc gia khac.\n");
			Sleep(1000); // ngưng màn hình 1 giây cho người dùng đọc
			delete temp1;
			delete temp2;
			return 0;
		}
		else
		{
			FILE *f = fopen(_DIR_DATA_FOLDER_READER, "ab");

			if (f == NULL)
				return 0;

			fwrite(&reader, sizeof(Readers), 1, f);
			fclose(f);
			printf("Them doc gia thanh cong.\n");
			delete temp1;
			delete temp2;
			break;
		}
	default:
			delete temp1;
			delete temp2;
			return 0;
	}
	return 1;
}

void viewInfAReader(Readers reader) // Xem thông tin của một người cụ thể
{

	printf("--------------------------------------------------------\n");
	printf("\tThong Tin Doc Gia\n");
	printf("Ma doc gia: %s\n", reader.ID);
	printf("Ho va ten: %s\n", reader.Fullname);
	printf("CMND: %s\n", reader.NationID);
	printf("Ngay sinh: ");
	printfDay(reader.Birthday);
	printf("Gioi tinh: %s\n", (reader.Sex == 0 ? "Nu" : "Nam"));
	printf("Email: %s\n", reader.Email);
	printf("Dia chi: %s\n", reader.Address);
	printf("Ngay lap the: ");
	printfDay(reader.creatCard);
	printf("Ngay het han: ");
	printfDay(reader.expireCard);	
	printf("--------------------------------------------------------\n");
}

void editReader(Readers &reader){ // sửa thông tin độc giả
	system(cls);
	int edit;
	bool end = false;
	do
	{
		switch (getNumberPressKey(editInfReaderMenu(), 0)){
		case 1: // printf("1. Sua Ho va ten\n");
			flushall();
			printf("Nhap Ho va Ten: ");
			gets(reader.Fullname);
			flushall();
			edit = wantEdit();
			if (edit == 0)
				end = true;
			break;
		case 2: // printf("2. Doi CMND\n");
			getNationalID(reader.NationID);
			edit = wantEdit();
			if (edit == 0)
				end = true;
			break;
		case 3: // printf("3. Doi ngay sinh\n");
			getBirthday(reader.Birthday);
			edit = wantEdit();
			if (edit == 0)
				end = true;
			break;
		case 4: // printf("4. Doi gioi tinh\n");
			getSex(reader.Sex);
			edit = wantEdit();
			if (edit == 0)
				end = true;
			break;
		case 5: // printf("5. Doi Email\n");
			flushall();
			printf("Nhap dia chi email / thu dien tu: ");
			gets(reader.Email);
			flushall();
			edit = wantEdit();
			if (edit == 0)
				end = true;
			break;
		case 6: // printf("6. Doi dia chi\n");
			flushall();
			printf("Nhap dia chi: ");
			gets(reader.Address);
			flushall();
			edit = wantEdit();
			if (edit == 0)
				end = true;
			break;
		case 7:
			flushall();
			printf("Gia han the toi ngay: ");
			reader.expireCard = getExpiredDay(getToday());
			printfDay(reader.expireCard);
			edit = wantEdit();
			if (edit == 0)
				end = true;
			break;
		default: 
			return;
		}
	} while (end == false);
}

void editReaderToFile()
{
	FILE *fo = fopen(_DIR_DATA_FOLDER_READER, "rb");
	FILE *ftemp = fopen(_DIR_DATA_FOLDER_READER_TEMP, "wb");

	if (fo == NULL || ftemp == NULL)
		return;

	Readers temp;
	Readers *reader = new Readers;
	if (reader == NULL)
		return;

	flushall();
	getReaderID(reader->ID);
	reader = findReaderWithID(reader->ID);
	if (reader == NULL)
	{
		printf("Doc gia khong ton tai.\n");
		Sleep(1000);
		delete reader;
		return;
	}

	viewInfAReader(*reader);
	Sleep(1000);
	// chỉnh sửa chọn lọc
	while (fread(&temp, sizeof(Readers), 1, fo) != 0)
	{
		if (strcmp(reader->ID, temp.ID) != 0)
			fwrite(&temp, sizeof(Readers), 1, ftemp);
		else
		{
			editReader(*reader);
			fwrite(reader, sizeof(Readers), 1, ftemp);
		}
	}
	textBgColor(RED, BLACK);
	printf("Chinh sua thanh cong.\n");
	textBgColor(WHITE, BLACK);
	viewInfAReader(*reader);
	fclose(fo);
	fclose(ftemp);
	delete reader;
	remove((char*)_DIR_DATA_FOLDER_READER);
	rename((char*)_DIR_DATA_FOLDER_READER_TEMP, (char*)_DIR_DATA_FOLDER_READER);
}

void deleteReaderToFile()
{

	FILE *fo = fopen(_DIR_DATA_FOLDER_READER, "rb");
	FILE *ftemp = fopen(_DIR_DATA_FOLDER_READER_TEMP, "wb");

	if (fo == NULL || ftemp == NULL)
		return;

	Readers temp;
	Readers *reader = new Readers;
	if (reader == NULL)
		return;


	flushall();
	getReaderID(reader->ID);
	reader = findReaderWithID(reader->ID);
	if (reader == NULL)
	{
		printf("Doc gia khong ton tai.\n");
		Sleep(1000);
		delete reader;
		return;
	}

	printf("Thong tin doc gia chuan bi xoa: \n");
	viewInfAReader(*reader);
	printf("Ban co chac chan muon xoa? \n- 1. Dong y \n- 0. Huy\n");
	switch (getNumberPressKey(1, 0)){
		case 1:
			break;
		default:
			fclose(fo);
			fclose(ftemp);
			delete reader;
			remove((char*)_DIR_DATA_FOLDER_READER_TEMP);
			return;
	}


	while (fread(&temp, sizeof(Readers), 1, fo) != 0)
	{
		if (strcmp(reader->ID, temp.ID) != 0)
			fwrite(&temp, sizeof(Readers), 1, ftemp);
	}
	textBgColor(RED, BLACK);
	printf("Xoa thanh cong.\n");
	textBgColor(WHITE, BLACK);
	
	fclose(fo);
	fclose(ftemp);
	delete reader;
	remove((char*)_DIR_DATA_FOLDER_READER);
	rename((char*)_DIR_DATA_FOLDER_READER_TEMP, (char*)_DIR_DATA_FOLDER_READER);
	Sleep(1000);
}

void searchNationID()
{
	Readers *reader = new Readers;

	getNationalID(reader->ID);
	reader = findReaderWithNationID(reader->ID);

	if (reader == NULL)
	{
		printf("Doc gia khong ton tai.\n");
	}
	else
		viewInfAReader(*reader);

	delete reader;
	Sleep(1000);
}

void searchFullName()
{
	Readers *reader = new Readers;

	flushall();
	printf("Nhap ho va ten: ");
	gets(reader->Fullname);

	LLNodeReader lsReader;
	Init(lsReader);

	if (!(findListReaderWithName(reader->Fullname, lsReader)))
	{
		printf("Doc gia khong ton tai.\n");
		Sleep(1000);
	}

	else
		printReaderFromLL(lsReader);

	freeLinkListReader(lsReader);
	delete reader;
	Sleep(1000);
}

void runReaderManagementForAdmin(){
	int choice = 0;
	do {
		choice = getNumberPressKey(printfMenuReaderManagementForAdmin(), 0);
		system(cls);
		switch (choice){
		case 1: // xem danh sách độc giả trong thư viện
			viewAllReader();
			break;
		case 2: // printf("2. Them doc gia.\n");
			writeInfReaderToFile();
			break;
		case 3: // printf("3. Chinh sua thong tin mot doc gia.\n");
			editReaderToFile();
			break;
		case 4: // printf("4. Xoa thong tin mot doc gia.\n");
			deleteReaderToFile();//<<<<<
			break;
		case 5: // Tìm kiếm độc giả qua CMND
			searchNationID();
			break;
		case 6: // Tìm kiếm độc giả qua họ tên
			searchFullName();
			break;
		default:
			break;
		}
		// Sleep(1);
	} while (choice != 0);
}
void runReaderManagementForExpert(){
	int choice = 0;
	do {
		choice = getNumberPressKey(printfMenuReaderManagementForExpert(), 0);
		system(cls);
		switch (choice){
		case 1: // xem danh sách độc giả trong thư viện
			viewAllReader();
			break;
		case 2: // printf("2. Them doc gia.\n");
			writeInfReaderToFile();
			break;
		case 3: // printf("3. Chinh sua thong tin mot doc gia.\n");
			editReaderToFile();
			break;
		// case 4: // printf("4. Xoa thong tin mot doc gia.\n");
		// 	deleteReaderToFile();//<<<<<
		// 	break;
		case 4: // Tìm kiếm độc giả qua CMND
			searchNationID();
			break;
		case 5: // Tìm kiếm độc giả qua họ tên
			searchFullName();
			break;
		default:
			break;
		}
		// Sleep(1);
	} while (choice != 0);
}
void runReaderManagementManager(){
	int choice = 0;
	do {
		choice = getNumberPressKey(printfMenuReaderManagementForManager(), 0);
		system(cls);
		switch (choice){
		case 1: // xem danh sách độc giả trong thư viện
			viewAllReader();
			break;
		case 2: // printf("2. Them doc gia.\n");
			writeInfReaderToFile();
			break;
		case 3: // printf("3. Chinh sua thong tin mot doc gia.\n");
			editReaderToFile();
			break;
		case 4: // printf("4. Xoa thong tin mot doc gia.\n");
			deleteReaderToFile();//<<<<<
			break;
		case 5: // Tìm kiếm độc giả qua CMND
			searchNationID();
			break;
		case 6: // Tìm kiếm độc giả qua họ tên
			searchFullName();
			break;
		default:
			break;
		}
		// Sleep(1);
	} while (choice != 0);
}
void runReaderManagement(int typeAccount)
{
	switch(typeAccount){
		case 1:
			runReaderManagementForAdmin();
			break;
		case 2:
			runReaderManagementForExpert();
			break;
		default:
			runReaderManagementManager();
			break;
	}

}