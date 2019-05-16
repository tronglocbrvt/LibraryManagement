#include "readerManagement.h"
#include "commonFunction.h"
#include "linkedListReaders.h"

<<<<<<< HEAD

char* getNationalID()
=======
Readers *findReaderWithNationID(char *personID)	// Tìm kiếm độc giả theo CMND
>>>>>>> 6ce69f4f629c66c06ba86d08b7de0d318b0b5b96
{
	Readers *reader = new Readers;

	FILE* fileReader = fopen("Release/Reader/databaseReader.bin", "rb");
	
	if (fileReader == NULL)
	{
		return NULL;
	}
	
<<<<<<< HEAD
	while (fread(reader, sizeof(reader), 1, fileReader) != 0){
		if (strcmp(reader->ID, personID) == 0)
=======
	while (fread(reader, sizeof(Readers), 1, fileReader) != NULL){
		if (strcmp(reader->NationID, personID) == 0)
>>>>>>> 6ce69f4f629c66c06ba86d08b7de0d318b0b5b96
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

	FILE* fileReader = fopen("Release/Reader/databaseReader.bin", "rb");

	if (fileReader == NULL)
	{
		return NULL;
	}
<<<<<<< HEAD
	
	while (fread(reader, sizeof(reader), 1, fileReader) != 0){
		if (strcmp(reader->Fullname, personName) == 0)
=======

	while (fread(reader, sizeof(Readers), 1, fileReader) != NULL){
		if (strcmp(reader->Email, Email) == 0)
>>>>>>> 6ce69f4f629c66c06ba86d08b7de0d318b0b5b96
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

	FILE* fileReader = fopen("Release/Reader/databaseReader.bin", "rb");

	if (fileReader == NULL)
	{
		return NULL;
	}

<<<<<<< HEAD
	while (fread(reader, sizeof(reader), 1 ,fileReader) != 0){
		if (strcmp(reader->Fullname, personName) == 0)
=======
	while (fread(reader, sizeof(Readers), 1, fileReader) != NULL){
		if (strcmp(reader->ID, ID) == 0)
>>>>>>> 6ce69f4f629c66c06ba86d08b7de0d318b0b5b96
		{
			fclose(fileReader);
			return reader;
		}
	}

	fclose(fileReader);
	return NULL;
}

<<<<<<< HEAD
Readers *getTheLastReader(){ // Lấy thông tin đọc giả cuối cùng trong file, trả về null nếu file rỗng.

	Readers *reader = new Readers();
=======
void viewAllReader()	// đọc toàn bộ thông tin độc giả từ file và in ras
{
	Readers *reader = new Readers;
>>>>>>> 6ce69f4f629c66c06ba86d08b7de0d318b0b5b96

	FILE* fileReader = fopen("Release/Reader/databaseReader.bin", "rb");

	if (fileReader == NULL || reader == NULL)
	{
		return;
	}

<<<<<<< HEAD
	rewind(fileReader);
	while (fread(reader, sizeof(Readers), 1, fileReader) != 0)
	{
		
=======
	while (fread(reader, sizeof(Readers), 1, fileReader) != NULL){
		viewInfAReader(*reader);
>>>>>>> 6ce69f4f629c66c06ba86d08b7de0d318b0b5b96
	}

	fclose(fileReader);
<<<<<<< HEAD
	return reader;
=======
	delete reader;
>>>>>>> 6ce69f4f629c66c06ba86d08b7de0d318b0b5b96
}


<<<<<<< HEAD
	printf("Ngay het han:\t\t");
	printfDay(reader.expireCard);

}
=======
//Readers *findReaderWithName(char *personName){	// Tìm kiếm đọc giả theo họ tên trả về danh sách
//	Readers *reader = new Readers;
//	FILE* fileReader = fopen("Release/Reader/databaseReader.bin", "rb");
//
//	if (reader == NULL || fileReader == NULL)
//	{
//		return NULL;
//	}
//
//	long int currentPoiter = ftell(fileReader);
//	fseek(fileReader, 0, SEEK_SET);
//
//	reader = NULL;
//
//	while (fread(reader, sizeof(Readers), 1, fileReader) != NULL){
//		if (strcmp(reader->Fullname, personName) == 0)
//		{
//			break;
//		}
//	}
//	
//	fseek(fileReader, currentPoiter, SEEK_SET);
//	fclose(fileReader);
//
//	return reader;
//}

bool findListReaderWithName(char *personName, LLNodeReader &lsReader){	// Tìm kiếm đọc giả theo họ tên trả về danh sách
	Readers *reader = new Readers;
>>>>>>> 6ce69f4f629c66c06ba86d08b7de0d318b0b5b96

	if (reader == NULL)
		return 0;

	FILE* fileReader = fopen("Release/Reader/databaseReader.bin", "rb");

	if (fileReader == NULL)
	{
		return 0;
	}
<<<<<<< HEAD
	
	while (fread(reader, sizeof(Readers), 1 ,fileReader) != 0){
		printfReader(*reader);
=======

	while (fread(reader, sizeof(Readers), 1 ,fileReader) != NULL){
		if (strcmp(reader->Fullname, personName) == 0)
		{
			// thêm vào danh sách
			addAtTail(lsReader, *reader);
		}
>>>>>>> 6ce69f4f629c66c06ba86d08b7de0d318b0b5b96
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
//
//bool getAllReaderToLL(FILE *fileReader, LLNodeReader *&ls){	// đọc toàn bộ thông tin đọc giả từ file nhưng không in ra -> đưa vào link list
//	Readers *reader = new Readers();
//	long int currentPoiter = ftell(fileReader);
//	fseek(fileReader, 0, SEEK_SET);
//
//	if (fileReader == NULL || reader == NULL)
//	{
//		return 0;
//	}
//	
//	while (fread(reader, sizeof(reader), 1 ,fileReader) != NULL){
//		fAddAtTail(ls, reader); // cập nhật vào cuối danh sách
//	}
//	
//	fseek(fileReader, currentPoiter, SEEK_SET);
//	return 1;
//}
//
//Readers *setReaderInf(char ID[]){
//	
//	Readers *reader = new Readers;
//
//	if (reader == NULL)
//		return NULL;
//
//	strcpy(reader->ID, ID);
//
//	// thêm họ và tên
//	printf("Nhap Ho va Ten: ");
//	flushall();
//	gets(reader->Fullname);
//
//	printf("Nhap ngay thang nam sinh:\n");
//	reader->Birthday = getDayFrmUser();
//
//	char *nationID = getNationalID();
//	strcpy(reader->NationID, nationID);
//
//	printf("Nhap dia chi: ");
//	gets(reader->Address);
//
//	do
//	{
//		printf("Nhap gioi tinh (Nam nhap 1; Nu nhap 0): ");
//		scanf("%d", &reader->Sex);
//		flushall();
//
//		if (reader->Sex != 0 && reader->Sex != 1)
//			printf("Vui long nhap lai. Nam nhap 1, Nu nhap 0.\n");
//		else break;
//	} while (1);
//
//	printf("Nhap dia chi email / thu dien tu: ");
//	gets(reader->Email);
//	
//	// ngày lập thẻ -- lấy ngày tạo tài khoản : hôm nay
//	reader->creatCard = getToday();
//	// ngày hết hạn là ngày tối đa được lập của thẻ, ngày tối đa là một hằng số
//	reader->expireCard = getExpiredDay(reader->creatCard);
//	//
//	return reader;
//}
//
//bool addAnInfToFile(const Readers *reader){	// thêm thông tin đọc giả vào file
//
//	FILE* fileReader = fopen("Release/Reader/databaseReader.bin", "ab");
//
//	if (fileReader == NULL)
//	{
//		return 0;
//	}
//
//	fwrite(reader, sizeof(Readers), 1, fileReader);
//	fclose(fileReader);
//
//	return 1;
//}
//
//bool editReaderInf(Readers *reader){
//
//	switch (getNumberPressKey(editInfReaderMenu(), 0)){
//		case 1:
//			printf("Nhap Ho va Ten: ");
//			gets(reader->Fullname);
//			break;
//		case 2:
//			printf("Nhap moi CMND de sua:\n");
//			strcpy(reader->NationID, getNationalID());
//			break;
//		case 3:
//			printf("Nhap ngay thang nam sinh:\n");
//			reader->Birthday = getDayFrmUser();
//			break;
//		case 4:
//			do
//			{
//				printf("Nhap gioi tinh (Nam nhap 1; Nu nhap 0): ");
//				scanf("%d", &reader->Sex);
//				int temp = getchar();
//
//				if (reader->Sex != 0 && reader->Sex != 1)
//					printf("Vui long nhap lai. Nam nhap 1, Nu nhap 0.\n");
//				else break;
//			} while (1);
//			break;
//		case 5:
//			printf("Nhap dia chi email / thu dien tu: ");
//			gets(reader->Email);
//			break;
//		case 6:
//			printf("Nhap dia chi: ");
//			gets(reader->Address);
//			break;
//		case 7:
//			reader->expireCard = getExpiredDay(getToday());
//			break;
//
//	}
//	return true;
//}
//


//
//bool viewInfAReader(){ // Xem thông tin của một người cụ thể
//	int choice = 0;
//	Readers	*reader = new Readers();
//
//	if (reader == NULL)
//		return false;
//
//	FILE* fileReader = fopen("Release/Reader/databaseReader.bin", "rb");
//
//	if (fileReader == NULL)
//	{
//		return 0;
//	}
//
//	char *StrGetFrmUser = new char();
//
//	reader = NULL;
//
//	bool flag = false;
//	LLNodeReader *lsReader = Init();
//
//	do {
//		choice = getNumberPressKey(printfSubMenuReaderManagement(), 0);
//		strcpy(StrGetFrmUser, getStringFrmUser((char*)"Nhap thong tin tim kiem"));
//
//		switch (choice){
//			case 1:
//				*reader = *findReaderWithName(fileReader, StrGetFrmUser);
//				flag = (reader == NULL ? true : false);
//				break;
//			case 2:
//				findListReaderWithName(StrGetFrmUser, lsReader);
//				flag = (lsReader->pHead == NULL ? true : false);
//				break;
//		}
//		if (flag == false) // tức -> không tìm thấy độc giả.
//		{
//			printf("Doc gia nay khong ton tai\n");
//			return 0;
//		}
//
//		if (reader != NULL)
//		{
//			printfReader(*reader);	
//		}
//
//		if (lsReader->pHead != NULL)
//		{
//			printfLLNodeReader(lsReader);	
//		}
//		
//	}while (choice != 0);
//
//	return 1;
//}
//
//bool deleteReader(Readers *reader){ // xoá một độc giả
//	
//	FILE* fileReader = fopen("Release/Reader/databaseReader.bin", "rb");
//
//	FILE* ftemp = fopen("Release/Reader/databaseReaderTemp.bin", "wb");
//
//	if (fileReader == NULL || ftemp == NULL)
//		return false;
//
//	Readers *readerTemp = new Readers; 
//
//	while (fread(readerTemp, sizeof(Readers), 1, fileReader) != NULL)
//	{
//		if (strcmp(reader->NationID, readerTemp->NationID) != 0)
//			fwrite(readerTemp, sizeof(Readers), 1, ftemp);
//		else
//			continue;
//	}
//
//	fclose(fileReader);
//	fclose(ftemp);
//
//	remove((char*)"Release/Reader/databaseReader.bin");
//	rename((char*)"Release/Reader/databaseReaderTemp.bin", (char*)"Release/Reader/databaseReader.bin");
//
//	return true;
//}
//

//bool editReaderInfToFile(){	// chỉnh sửa thông tin đọc giả >> hàm khởi chaỵ
//	Readers	*reader = new Readers;
//	LLNodeReader *lsReader = Init();
//	if (reader == NULL || lsReader == NULL)
//		return 0;
//
//	FILE* fileReader = fopen("Release/Reader/databaseReader.bin", "rb");
//	if (fileReader == NULL)
//	{
//		return 0;
//	}
//
//	int choice = 0;
//	char *StrGetFrmUser = new char();
//
//	do {
//		choice = getNumberPressKey(printfSubMenuReaderManagement(), 0);
//		strcpy(StrGetFrmUser, getStringFrmUser((char*)"Nhap thong tin tim kiem"));
//
//		switch (choice){
//			case 1: // tìm kiếm theo CMND
//				*reader = *findReaderWithNationID(StrGetFrmUser);
//				if (reader == NULL)
//				{
//					printf("Doc gia nay khong ton tai.\n");
//					system("pause");
//					continue;
//				}
//				break;
//			case 2: // tìm kiếm theo tên
//				findListReaderWithName(StrGetFrmUser, lsReader);
//				if (lsReader->pHead == NULL)
//				{
//					printf("Doc gia nay khong ton tai.\n");
//					system("pause");
//					continue;
//				}
//				break;
//		}
//
//		Readers *readerTemp = new Readers();
//		if (lsReader->pHead != NULL)
//		{
//			printfAllReader(lsReader);
//			readerTemp = findReaderAtNumberic(lsReader, getNumber((char*)"Chon 1 doc gia: "));
//			printf("Da chon!\n");
//			system("pause");
//		}
//
//		if (askToUpdateReaderToFile() == 1)
//		{
//			deleteReader(reader);
//			addAnInfToFile(readerTemp);
//		}
//		system("cls");
//	}while (choice != 0);
//
//	fclose(fileReader);
//	return 1;
//
//}
//
//bool deleteReaderInfToFile(){	// xoá thông tin một độc giả - hàm khởi chạy -- lọc >> doing here
//	Readers	*reader = new Readers;
//	char *StrGetFrmUser = new char();
//
//	int choice = 0;
//
//	do {
//		choice = getNumberPressKey(printfSubMenuReaderManagement(), 0);
//		strcpy(StrGetFrmUser, getStringFrmUser((char*)"Nhap thong tin tim kiem"));
//		LLNodeReader *lsReader = Init();
//
//		switch (choice){
//			case 1: // tìm kiếm theo CMND
//				*reader = *findReaderWithNationID(StrGetFrmUser);
//				if (reader == NULL)
//				{
//					printf("Doc gia nay khong ton tai.\n");
//					system("pause");
//					continue;
//				}
//				break;
//			case 2: // tìm kiếm theo tên
//				findListReaderWithName(StrGetFrmUser, lsReader);
//				if (lsReader->pHead == NULL)
//				{
//					printf("Doc gia nay khong ton tai.\n");
//					system("pause");
//					continue;
//				}
//				break;
//		}
//		if (askToUpdateReaderToFile() == 1){
//			if (reader != NULL)
//				{
//					deleteReader(reader);
//				}
//				else if (lsReader->pHead != NULL)
//				{
//					printfAllReader(lsReader);
//					deleteReader(findReaderAtNumberic(lsReader, getNumber((char*)"Chon 1 doc gia: ")));
//				}
//				else return 0;
//				
//		}
//		system("cls");
//	}while (choice != 0);
//	return 1;
//}
//
//


Readers addReader()
{
	Readers reader;
	Readers *temp = new Readers;
	FILE *f = fopen("Release/Reader/databaseReader.bin", "rb");
	long ID = 1;
	fseek(f, 0L, SEEK_END);
	long size = ftell(f);
		if (size == 0)
		{
			ID = 1;
		}
		else
		{
			rewind(f);
			while (fread(temp, sizeof(Readers), 1, f) != NULL)
			{
				ID++;
			}
		}

<<<<<<< HEAD
bool getAllReaderToLL(FILE *fileReader, LLNodeReader *&ls){	// đọc toàn bộ thông tin đọc giả từ file nhưng không in ra -> đưa vào link list
	Readers *reader = new Readers();
	long int currentPoiter = ftell(fileReader);
	fseek(fileReader, 0, SEEK_SET);

	if (fileReader == NULL || reader == NULL)
	{
		return 0;
	}
	
	while (fread(reader, sizeof(reader), 1 ,fileReader) != 0){
		fAddAtTail(ls, reader); // cập nhật vào cuối danh sách
	}
	
	fseek(fileReader, currentPoiter, SEEK_SET);
	return 1;
}

Readers *setReaderInf(char ID[]){
	
	Readers *reader = new Readers;

	if (reader == NULL)
		return NULL;
=======
	fclose(f);
	delete temp;
>>>>>>> 6ce69f4f629c66c06ba86d08b7de0d318b0b5b96

	strcpy(reader.ID, toStr(ID));

<<<<<<< HEAD
	// thêm họ và tên
	printf("Nhap Ho va Ten: ");
	// clearSTDIN();
	gets(reader->Fullname);

	printf("Nhap ngay thang nam sinh:\n");
	reader->Birthday = getDayFrmUser();

	char *nationID = getNationalID();
	strcpy(reader->NationID, nationID);

	printf("Nhap dia chi: ");
	gets(reader->Address);

	do
	{
		printf("Nhap gioi tinh (Nam nhap 1; Nu nhap 0): ");
		scanf("%d", &reader->Sex);
		// clearSTDIN();

		if (reader->Sex != 0 && reader->Sex != 1)
			printf("Vui long nhap lai. Nam nhap 1, Nu nhap 0.\n");
		else break;
	} while (1);
=======
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
>>>>>>> 6ce69f4f629c66c06ba86d08b7de0d318b0b5b96

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
			FILE *f = fopen("Release/Reader/databaseReader.bin", "ab");

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
	printf("Thong tin cua ma doc gia: %s\n", reader.ID);
	printf("Ho va ten: %s\n", reader.Fullname);
	printf("CMND: %s\n", reader.NationID);
	printf("Ngay sinh: ");
	printfDay(reader.Birthday);
	printf("Gioi tinh (nam la 1, nu la 0): %s\n", (reader.Sex == 0 ? "Nu" : "Nam"));
	printf("Email: %s\n", reader.Email);
	printf("Dia chi: %s\n", reader.Address);
	printf("Ngay lap the: ");
	printfDay(reader.creatCard);
	printf("Ngay het han: ");
	printfDay(reader.expireCard);	
	printf("--------------------------------------------------------\n");
}

void editReader(Readers &reader){ // sửa thông tin độc giả

<<<<<<< HEAD
	while (fread(readerTemp, sizeof(Readers), 1, fileReader) != 0)
=======
	int edit;
	bool end = false;
	do
>>>>>>> 6ce69f4f629c66c06ba86d08b7de0d318b0b5b96
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
		default: // printf("0. Quay ve\n");
			return;
		}
	} while (end == false);
}

void editReaderToFile()
{
	FILE *fo = fopen("Release/Reader/databaseReader.bin", "rb");
	FILE *ftemp = fopen("Release/Reader/readerTemp.bin", "wb");

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
	while (fread(&temp, sizeof(Readers), 1, fo) != NULL)
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
	remove((char*)"Release/Reader/databaseReader.bin");
	rename((char*)"Release/Reader/readerTemp.bin", (char*)"Release/Reader/databaseReader.bin");
}

void deleteReaderToFile()
{

	FILE *fo = fopen("Release/Reader/databaseReader.bin", "rb");
	FILE *ftemp = fopen("Release/Reader/readerTemp.bin", "wb");

	if (fo == NULL || ftemp == NULL)
		return;

<<<<<<< HEAD
		if (askToUpdateReaderToFile() == 1)
		{
			deleteReader(reader);
			addAnInfToFile(readerTemp);
		}
		system(cls);
	}while (choice != 0);
=======
	Readers temp;
	Readers *reader = new Readers;
	if (reader == NULL)
		return;
>>>>>>> 6ce69f4f629c66c06ba86d08b7de0d318b0b5b96

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

	while (fread(&temp, sizeof(Readers), 1, fo) != NULL)
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
	remove((char*)"Release/Reader/databaseReader.bin");
	rename((char*)"Release/Reader/readerTemp.bin", (char*)"Release/Reader/databaseReader.bin");
}

void searchNationID()
{
	Readers *reader = new Readers;

	getNationalID(reader->ID);

	reader = findReaderWithNationID(reader->ID);
	if (reader == NULL)
	{
		printf("Doc gia khong ton tai.\n");
		Sleep(1000);
	}
	else
		viewInfAReader(*reader);

<<<<<<< HEAD
		switch (choice){
			case 1: // tìm kiếm theo CMND
				*reader = *findReaderWithNationID(StrGetFrmUser);
				if (reader == NULL)
				{
					printf("Doc gia nay khong ton tai.\n");
					system("pause");
					continue;
				}
				break;
			case 2: // tìm kiếm theo tên
				findListReaderWithName(StrGetFrmUser, lsReader);
				if (lsReader->pHead == NULL)
				{
					printf("Doc gia nay khong ton tai.\n");
					system("pause");
					continue;
				}
				break;
		}
		if (askToUpdateReaderToFile() == 1){
			if (reader != NULL)
				{
					deleteReader(reader);
				}
				else if (lsReader->pHead != NULL)
				{
					printfAllReader(lsReader);
					deleteReader(findReaderAtNumberic(lsReader, getNumber((char*)"Chon 1 doc gia: ")));
				}
				else return 0;
				
		}
		system(cls);
	}while (choice != 0);
	return 1;
=======
	delete reader;
>>>>>>> 6ce69f4f629c66c06ba86d08b7de0d318b0b5b96
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
}

void runReaderManagement()
{
	int choice = 0;
	do {
		choice = getNumberPressKey(printfMenuReaderManagement(), 0);
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
			deleteReaderToFile();
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
	} while (choice != 0);

}