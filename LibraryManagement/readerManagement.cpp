#include "readerManagement.h"
#include "commonFunction.h"
#include "Menu.h"

char *getNationalID()
{
	int flag = 0;
	char *idNa = new char();
	do
	{
		printf("Nhap CMND (9 so hoac 12 so): ");
		scanf("%s", idNa);
		int temp = getchar();
		
		if (strlen(idNa) != 9 && strlen(idNa) != 12)
		{
			printf("CMND khong hop le. Vui long nhap lai.\n");
			continue;
		}

		flag = 1; 
		for (int i = 0; i < strlen(idNa); i++)
		{
			if (!isNumber(idNa[i]))
			{
				flag = 0;
				printf("CMND khong hop le. Vui long nhap lai.\n");
				break;
			}
		}
	} while (flag == 0);
	return idNa;
}

Readers *findReaderWithNationID(const FILE *&fileReader, char *&personID){	// Tìm kiếm đọc giả theo CMND
	Readers *reader = new Readers();
	long int currentPoiter = ftell(fileReader);
	fseek(fileReader, 0, SEEK_SET);

	reader = NULL;

	if (fileReader == NULL)
	{
		return NULL;
	}
	
	while (fread(reader, sizeof(reader), 1 ,f) != NULL){
		if (strcmp(reader->ID, personID) == 0)
		{
			break;
		}
	}
	
	fseek(fileReader, currentPoiter, SEEK_SET);
	return reader;
}

Readers *findReaderWithName(const FILE *&fileReader, char *&personName){	// Tìm kiếm đọc giả theo họ tên trả về danh sách
	Readers *reader = new Readers();
	long int currentPoiter = ftell(fileReader);
	fseek(fileReader, 0, SEEK_SET);

	reader = NULL;

	if (fileReader == NULL)
	{
		return NULL;
	}
	
	while (fread(reader, sizeof(reader), 1 ,f) != NULL){
		if (strcmp(reader->Fullname, personName) == 0)
		{
			break;
		}
	}
	
	fseek(fileReader, currentPoiter, SEEK_SET);
	return reader;
}

bool findListReaderWithName(const FILE *&fileReader, char *&personName, LLNodeReader *&lsReader){	// Tìm kiếm đọc giả theo họ tên trả về danh sách
	Readers *reader = new Readers();
	long int currentPoiter = ftell(fileReader);
	fseek(fileReader, 0, SEEK_SET);

	reader = NULL;

	if (fileReader == NULL)
	{
		return false;
	}
	
	while (fread(reader, sizeof(reader), 1 ,f) != NULL){
		if (strcmp(reader->Fullname, personName) == 0)
		{
			// thêm vào danh sách
			fAddAtTail(lsReader, reader);
		}
	}
	
	fseek(fileReader, currentPoiter, SEEK_SET);
	return true;
}

Readers *getTheLastReader(const FILE *&fileReader){ // Lấy thông tin đọc giả cuối cùng trong file, trả về null nếu file rỗng.
	long int current = ftell(fileReader);

	Readers *reader = new Readers();

	fseek(fileReader, 0, SEEK_SET);
	fread(reader, sizeof(Readers), 1, fileReader); // lấy độc giả đầu
	if (reader == NULL)
	{
		return NULL;
	}

	fseek(fileReader, -sizeof(Readers), SEEK_END);
	fread(reader, sizeof(Readers), 1, fileReader); // lấy đọc giả cuối

	fseek(fileReader, current, SEEK_SET);

	return reader;
}

void printfReader(Readers reader){

	printf("Ma doc gia:\t\t%s\n", reader.ID);

	printf("Ho ten day du:\t\t%s\n", reader.Fullname);

	printf("CMND:\t\t%s\n", reader.NationID);

	printf("Ngay sinh:\t\t");
	printfDay(reader.Birthday);

	printf("Gioi tinh:\t\t%s\n", (reader.Sex == 0 ? (char *)"Nu" : (char *)"Nam"));

	printf("Thu dien tu:\t\t%s\n", reader.Email);

	printf("Dia chi:\t\t%s\n", reader.Address);

	printf("Ngay lap the:\t\t");
	printfDay(reader.creatCard);

	printf("Ngay het han:\t\t%");
	printfDay(reader.expireCard);

}

bool printfAllReader(FILE *fileReader){	// đọc toàn bộ thông tin đọc giả từ file và in ra -> không đưa vào link list
	Readers *reader = new Readers();
	if (fileReader == NULL || reader == NULL)
	{
		return 0;
	}
	
	while (fread(reader, sizeof(reader), 1 ,f) != NULL){
		printfReader(*reader);
	}
	
	fseek(fileReader, 0, SEEK_SET);
	return 1;
}

bool printfAllReader(const LLNodeReader *ls){ // int ra thông tin đọc giả từ Link List khi đã có Link List
	NodeReader *pNow = new NodeReader();
	if (ls == NULL || pNow == NULL)
	{
		return 0;
	}
	pNow = ls->pHead;

	int index = 0;
	while(pNow != NULL){
		printf("\nDoc gia thu %d:\n", ++index);
		printfReader(*pNow->reader);
		pNow = pNow->pNext;
	}

	return 1;
}

bool getAllReaderToLL(const FILE *&fileReader, LLNodeReader *&ls){	// đọc toàn bộ thông tin đọc giả từ file nhưng không in ra -> đưa vào link list
	Readers *reader = new Readers();
	long int currentPoiter = ftell(fileReader);
	fseek(fileReader, 0, SEEK_SET);

	if (fileReader == NULL || reader == NULL)
	{
		return 0;
	}
	
	while (fread(reader, sizeof(reader), 1 ,f) != NULL){
		fAddAtTail(ls, reader); // cập nhật vào cuối danh sách
	}
	
	fseek(fileReader, currentPoiter, SEEK_SET);
	return 1;
}

Readers *setReaderInf(char *readerID){
	Readers *reader;
	int temp;
 	// thêm mã đọc giả -- tự động
	strcpy(reader->ID, readerID);
	// thêm họ và tên
	printf("Nhap Ho va Ten: ");
	gets(reader->Fullname);

	printf("Nhap ngay thang nam sinh:\n");
	*reader->Birthday = getDayFrmUser();

	strcpy(reader->NationID, getNationalID());

	printf("Nhap dia chi: ");
	gets(reader->Address);

	do
	{
		printf("Nhap gioi tinh (Nam nhap 1; Nu nhap 0): ");
		scanf("%d", &reader->Sex);
		temp = getchar();

		if (reader->Sex != 0 && reader->Sex != 1)
			printf("Vui long nhap lai. Nam nhap 1, Nu nhap 0.\n");
		else break;
	} while (1);

	printf("Nhap dia chi email / thu dien tu: ");
	gets(reader->Email);
	
	// ngày lập thẻ -- lấy ngày tạo tài khoản : hôm nay
	reader->creatCard = getToday();
	// ngày hết hạn là ngày tối đa được lập của thẻ, ngày tối đa là một hằng số
	reader->expireCard = getExpiredDay(reader->creatCard);
	//
	return reader;
}

bool addAnInfToFile(const FILE *fileReader, const Readers *reader){	// thêm thông tin đọc giả vào file

	if (fileReader == NULL || reader == NULL)
	{
		return 0;
	}

	long int currentPoiter = ftell(fileReader);
	fseek(fileReader, 0, SEEK_END);

	fwrite(reader, sizeof(Readers), 1, fileReader);

	fseel(fileReader, currentPoiter, SEEK_SET);

	return 1;
}

bool editReaderInf(Readers *reader){

	switch(getNumberPressKey(printfEditReaderInf())){
		case 1:
			printf("Nhap Ho va Ten: ");
			gets(reader->Fullname);
			break;
		case 2:
			printf("Nhap moi CMND de sua:\n");
			strcpy(reader->NationID, getNationalID());
			break;
		case 3:
			printf("Nhap ngay thang nam sinh:\n");
			reader->Birthday = getDayFrmUser();
			break;
		case 4:
			do
			{
				printf("Nhap gioi tinh (Nam nhap 1; Nu nhap 0): ");
				scanf("%d", &reader->Sex);
				int temp = getchar();

				if (reader->Sex != 0 && reader->Sex != 1)
					printf("Vui long nhap lai. Nam nhap 1, Nu nhap 0.\n");
				else break;
			} while (1);
			break;
		case 5:
			printf("Nhap dia chi email / thu dien tu: ");
			gets(reader->Email);
			break;
		case 6:
			printf("Nhap dia chi: ");
			gets(reader->Address);
			break;
		case 7:
			reader->expireCard = getExpiredDay(getToday());
			break;

	}
	return true;
}

bool askToUpdateReaderToFile(){	// cập nhật thông tin đọc giả vào file - có hỏi có chắc chắn muốn cập nhật không
	printf("Ban co chan muon cap nhat khong\n");
	printf("1. Co\n");
	printf("2. Khong\n");

	return (getNumberPressKey(2,1));
}

bool addNewReaderInfToFile(FILE *fileReader){  // thêm độc giả vào database

	Readers	*reader = new Readers();
	
	if (fileReader == NULL)
	{
		return 0;
	}

	*reader = *getTheLastReader(fileReader);
	if (reader == NULL)
	{
		*reader = *setReaderInf((char*)"000000001");
	}

	char *strID = new char();
	strcpy(strID, reader->ID);
	plusOneIntoAString(strID);
	*reader = setReaderInf(strID);

	if (findReaderWithNationID(fileReader, reader->NationID) == NULL)
	{
		printf("Doc gia nay da ton tai.\n");
		system("pause");
		return 0;
	}

	switch (askToUpdateReaderToFile()){
		case 1:
			addAnInfToFile(fileReader, reader);
			break;
		default:
			return 0;
			break;
	}
}

bool viewInfAReader(FILE *fileReader){ // Xem thông tin của một người cụ thể
	int choice = 0;
	Readers	*reader = new Readers();
	char *StrGetFrmUser = new char();

	reader = NULL;

	if (fileReader == NULL)
	{
		return 0;
	}

	bool flag = false;

	do {
		choice = getNumberPressKey(printfSubMenuReaderManagement());
		strcpy(StrGetFrmUser, getStringFrmUser((char*)"Nhap thong tin tim kiem"));

		switch (choice){
			case 1:
				*reader = *findReaderWithID(fileReader, StrGetFrmUser);
				flag = (reader == NULL ? true : false);
				break;
			case 2:
				LLNodeReader *&lsReader = Init();
				findListReaderWithName(fileReader, StrGetFrmUser, lsReader);
				flag = (lsReader->pHead == NULL ? true : false);
				break;
		}
		if (flag == false) // tức -> không tìm thấy độc giả.
		{
			printf("Doc gia nay khong ton tai\n");
			return 0;
		}

		if (reader != NULL)
		{
			printfReader(*reader);	
		}

		if (lsReader->pHead != NULL)
		{
			printfLLNodeReader(lsReader);	
		}
		
	}while (choice != 0);

	return 1;
}

bool deleteReader(const FILE *&fileReader, const Readers *&reader){ // xoá một độc giả
	FILE *fileReader = fopen("Release/Reader/databaseReader.bin", "rb");
	FILE *ftemp = fopen("Release/Reader/databaseReaderTemp.bin", "wb");

	if (fileReader == NULL || ftemp == NULL)
		return false;

	Readers *readerTemp = InitNode();

	while (fread(&readerTemp, sizeof(Readers), 1, fileReader) != NULL)
	{
		if (strcmp(reader->NationID, readerTemp->NationID) != 0)
			fwrite(&readerTemp, sizeof(Readers), 1, ftemp);
		else
			continue;
	}

	fclose(fileReader);
	fclose(ftemp);

	remove((char*)"Release/Reader/databaseReader.bin");
	rename((char*)"Release/Reader/databaseReaderTemp.bin", (char*)"Release/Reader/databaseReader.bin");

	return true;
}

bool deleteReaderInfToFile(FILE *fileReader){	// xoá thông tin một độc giả - hàm khởi chạy -- lọc >> doing here
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
				printfAllReader(lsReader);
				deleteReader(fileReader, findReaderAtNumberic(lsReader, getNumber((char*)"Chon 1 doc gia: ")));
			}
			else return 0;
			break;
		default: // không
			return 0;
	}
	return 1;
}



