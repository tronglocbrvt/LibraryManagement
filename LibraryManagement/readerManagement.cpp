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

Readers *findReaderWithID(const FILE *&fileReader, char *&personID){	// Tìm kiếm đọc giả theo CMND
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

Readers *findReaderWithName(const FILE *&fileReader, char *&personName){	// Tìm kiếm đọc giả theo họ tên
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

	while(pNow != NULL){
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

bool viewInfAReader(FILE *fileReader){ // Xem thông tin của một người cụ thể
	int choice = 0;
	Readers	*reader = new Readers();
	char *StrGetFrmUser = new char();

	reader = NULL;

	if (fileReader == NULL)
	{
		return 0;
	}

	do {
		choice = getNumberPressKey(printfSubMenuReaderManagement());
		strcpy(StrGetFrmUser, getStringFrmUser((char*)"Nhap thong tin tim kiem"));

		switch (choice){
			case 1:
				*reader = *findReaderWithID(StrGetFrmUser);
				break;
			case 2:
				*reader = *findReaderWithName(StrGetFrmUser);
				break;
		}
		if (reader == NULL) // tức độc giả không thay đổi -> không tìm thấy.
		{
			printf("Doc gia nay khong ton tai\n");
			return 0;
		}
		printfReader(*reader);
	}while (choice != 0);

	return 1;
}



