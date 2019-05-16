#include "readerManagement.h"


char* getNationalID()
{
	char *idNa = new char[13];
	int flag = 0;
	do
	{
		printf("Nhap CMND (9 so hoac 12 so): ");
		gets(idNa);
			
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

Readers *findReaderWithNationID(char *personID){	// Tìm kiếm độc giả theo CMND
	Readers *reader = new Readers();

	FILE* fileReader = fopen("Release/Reader/databaseReader.bin", "rb");
	
	if (fileReader == NULL)
	{
		return NULL;
	}
	
	while (fread(reader, sizeof(reader), 1, fileReader) != 0){
		if (strcmp(reader->ID, personID) == 0)
		{
			fclose(fileReader);
			return NULL;
		}
	}

	fclose(fileReader);
	return reader;
}

Readers *findReaderWithName(FILE *fileReader, char *&personName){	// Tìm kiếm đọc giả theo họ tên trả về danh sách
	Readers *reader = new Readers();
	long int currentPoiter = ftell(fileReader);
	fseek(fileReader, 0, SEEK_SET);

	reader = NULL;

	if (fileReader == NULL)
	{
		return NULL;
	}
	
	while (fread(reader, sizeof(reader), 1, fileReader) != 0){
		if (strcmp(reader->Fullname, personName) == 0)
		{
			break;
		}
	}
	
	fseek(fileReader, currentPoiter, SEEK_SET);
	return reader;
}

bool findListReaderWithName(char *&personName, LLNodeReader *&lsReader){	// Tìm kiếm đọc giả theo họ tên trả về danh sách
	Readers *reader = new Readers();

	if (reader == NULL)
		return false;

	FILE* fileReader = fopen("Release/Reader/databaseReader.bin", "rb");

	if (fileReader == NULL)
	{
		return 0;
	}

	while (fread(reader, sizeof(reader), 1 ,fileReader) != 0){
		if (strcmp(reader->Fullname, personName) == 0)
		{
			// thêm vào danh sách
			fAddAtTail(lsReader, reader);
		}
	}

	delete reader;
	return true;
}

Readers *getTheLastReader(){ // Lấy thông tin đọc giả cuối cùng trong file, trả về null nếu file rỗng.

	Readers *reader = new Readers();

	FILE* fileReader = fopen("Release/Reader/databaseReader.bin", "rb");

	fseek(fileReader, 0L, SEEK_END);
	long size = ftell(fileReader);
	if (size == 0)
	{
		fclose(fileReader);
		return NULL;
	}

	rewind(fileReader);
	while (fread(reader, sizeof(Readers), 1, fileReader) != 0)
	{
		
	}
	fclose(fileReader);
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

	printf("Ngay het han:\t\t");
	printfDay(reader.expireCard);

}

bool printfAllReader(){	// đọc toàn bộ thông tin đọc giả từ file và in ra -> không đưa vào link list
	Readers *reader = new Readers();

	FILE* fileReader = fopen("Release/Reader/databaseReader.bin", "rb");

	if (fileReader == NULL || reader == NULL)
	{
		return 0;
	}
	
	while (fread(reader, sizeof(Readers), 1 ,fileReader) != 0){
		printfReader(*reader);
	}
	
	fclose(fileReader);
	delete reader;

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

	strcpy(reader->ID, ID);

	// thêm họ và tên
	printf("Nhap Ho va Ten: ");
	clearSTDIN();
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
		clearSTDIN();

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

bool addAnInfToFile(const Readers *reader){	// thêm thông tin đọc giả vào file

	FILE* fileReader = fopen("Release/Reader/databaseReader.bin", "ab");

	if (fileReader == NULL)
	{
		return 0;
	}

	fwrite(reader, sizeof(Readers), 1, fileReader);
	fclose(fileReader);

	return 1;
}

bool editReaderInf(Readers *reader){

	switch (getNumberPressKey(editInfReaderMenu(), 0)){
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

int askToUpdateReaderToFile(){	// cập nhật thông tin đọc giả vào file - có hỏi có chắc chắn muốn cập nhật không
	printf("Ban co chan muon cap nhat khong\n");
	printf("1. Co\n");
	printf("2. Khong\n");

	return (getNumberPressKey(2,1));
}

bool addNewReaderInfToFile(){  // thêm độc giả vào database

	Readers	*reader = new Readers;
	
	reader = getTheLastReader();

	if (reader == NULL)
	{
		reader = setReaderInf((char*)"00000001");
	}

	else
	{
		plusOneIntoAString(reader->ID);
		reader = setReaderInf(reader->ID);
	}
	switch (askToUpdateReaderToFile()){
	case 1:
		if (findReaderWithNationID(reader->NationID) == NULL)
		{
			printf("Doc gia nay da ton tai.\n");
			system("pause");
			delete reader;
			return 0;
		}
			addAnInfToFile(reader);
			delete reader;
			break;
	default:
			delete reader;
			return 0;
			break;
	}
	return 1;
}

bool viewInfAReader(){ // Xem thông tin của một người cụ thể
	int choice = 0;
	Readers	*reader = new Readers();

	if (reader == NULL)
		return false;

	FILE* fileReader = fopen("Release/Reader/databaseReader.bin", "rb");

	if (fileReader == NULL)
	{
		return 0;
	}

	char *StrGetFrmUser = new char();

	reader = NULL;

	bool flag = false;
	LLNodeReader *lsReader = Init();

	do {
		choice = getNumberPressKey(printfSubMenuReaderManagement(), 0);
		strcpy(StrGetFrmUser, getStringFrmUser((char*)"Nhap thong tin tim kiem"));

		switch (choice){
			case 1:
				*reader = *findReaderWithName(fileReader, StrGetFrmUser);
				flag = (reader == NULL ? true : false);
				break;
			case 2:
				findListReaderWithName(StrGetFrmUser, lsReader);
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

bool deleteReader(Readers *reader){ // xoá một độc giả
	
	FILE* fileReader = fopen("Release/Reader/databaseReader.bin", "rb");

	FILE* ftemp = fopen("Release/Reader/databaseReaderTemp.bin", "wb");

	if (fileReader == NULL || ftemp == NULL)
		return false;

	Readers *readerTemp = new Readers; 

	while (fread(readerTemp, sizeof(Readers), 1, fileReader) != 0)
	{
		if (strcmp(reader->NationID, readerTemp->NationID) != 0)
			fwrite(readerTemp, sizeof(Readers), 1, ftemp);
		else
			continue;
	}

	fclose(fileReader);
	fclose(ftemp);

	remove((char*)"Release/Reader/databaseReader.bin");
	rename((char*)"Release/Reader/databaseReaderTemp.bin", (char*)"Release/Reader/databaseReader.bin");

	return true;
}

bool editReader(Readers *&reader){ // sửa thông tin độc giả >> doing here 
	switch(getNumberPressKey(editInfReaderMenu(), 0)){
		case 1: // printf("1. Sua Ho va ten\n");
			printf("Nhap Ho va Ten: ");
			gets(reader->Fullname);
			break;
		case 2: // printf("2. Doi CMND\n");
			strcpy(reader->NationID, getNationalID());
			break;
		case 3: // printf("3. Doi ngay sinh\n");
			printf("Nhap ngay thang nam sinh:\n");
			reader->Birthday = getDayFrmUser();
			break;
		case 4: // printf("4. Doi gioi tinh\n");
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
		case 5: // printf("5. Doi Email\n");
			printf("Nhap dia chi email / thu dien tu: ");
			gets(reader->Email);
			break;
		case 6: // printf("6. Doi dia chi\n");
			printf("Nhap dia chi: ");
			gets(reader->Address);
			break;
		case 7: 
			printf("7. Gia han the toi ngay ");
			reader->expireCard = getExpiredDay(getToday());
			printfDay(reader->expireCard);
			break;
		default: // printf("0. Quay ve\n");
			break;
	}
	return 1;
}

bool editReaderInfToFile(){	// chỉnh sửa thông tin đọc giả >> hàm khởi chaỵ
	Readers	*reader = new Readers;
	LLNodeReader *lsReader = Init();
	if (reader == NULL || lsReader == NULL)
		return 0;

	FILE* fileReader = fopen("Release/Reader/databaseReader.bin", "rb");
	if (fileReader == NULL)
	{
		return 0;
	}

	int choice = 0;
	char *StrGetFrmUser = new char();

	do {
		choice = getNumberPressKey(printfSubMenuReaderManagement(), 0);
		strcpy(StrGetFrmUser, getStringFrmUser((char*)"Nhap thong tin tim kiem"));

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

		Readers *readerTemp = new Readers();
		if (lsReader->pHead != NULL)
		{
			printfAllReader(lsReader);
			readerTemp = findReaderAtNumberic(lsReader, getNumber((char*)"Chon 1 doc gia: "));
			printf("Da chon!\n");
			system("pause");
		}

		if (askToUpdateReaderToFile() == 1)
		{
			deleteReader(reader);
			addAnInfToFile(readerTemp);
		}
		system(cls);
	}while (choice != 0);

	fclose(fileReader);
	return 1;

}

bool deleteReaderInfToFile(){	// xoá thông tin một độc giả - hàm khởi chạy -- lọc >> doing here
	Readers	*reader = new Readers;
	char *StrGetFrmUser = new char();

	int choice = 0;

	do {
		choice = getNumberPressKey(printfSubMenuReaderManagement(), 0);
		strcpy(StrGetFrmUser, getStringFrmUser((char*)"Nhap thong tin tim kiem"));
		LLNodeReader *lsReader = Init();

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
}


void runReaderManagement()
{
	int choice = 0;
	do {
		choice = getNumberPressKey(printfMenuReaderManagement(), 0);
		system(cls);
		switch (choice){
			case 1:
				printfAllReader();
				break;
			case 2: // printf("2. Them doc gia.\n");
				addNewReaderInfToFile();
				break;
			case 3: // printf("3. Chinh sua thong tin mot doc gia.\n");
				editReaderInfToFile();
				break;
			case 4: // printf("4. Xoa thong tin mot doc gia.\n");
				deleteReaderInfToFile();
				break;
			case 5:
				viewInfAReader();
				break;
			default:
				break;
		}
	}while (choice != 0);

}



