#include "bookManagement.h"


char *getISBN()
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

Books *findBookWithNationID(const FILE *&fileBook, char *&personID){	// Tìm kiếm đọc giả theo CMND
	Books *book = new Books();
	long int currentPoiter = ftell(fileBook);
	fseek(fileBook, 0, SEEK_SET);

	book = NULL;

	if (fileBook == NULL)
	{
		return NULL;
	}
	
	while (fread(book, sizeof(book), 1 ,f) != NULL){
		if (strcmp(book->ID, personID) == 0)
		{
			break;
		}
	}
	
	fseek(fileBook, currentPoiter, SEEK_SET);
	return book;
}

Books *findBookWithName(const FILE *&fileBook, char *&personName){	// Tìm kiếm đọc giả theo họ tên trả về danh sách
	Books *book = new Books();
	long int currentPoiter = ftell(fileBook);
	fseek(fileBook, 0, SEEK_SET);

	book = NULL;

	if (fileBook == NULL)
	{
		return NULL;
	}
	
	while (fread(book, sizeof(book), 1 ,f) != NULL){
		if (strcmp(book->Fullname, personName) == 0)
		{
			break;
		}
	}
	
	fseek(fileBook, currentPoiter, SEEK_SET);
	return book;
}

bool findListBookWithName(const FILE *&fileBook, char *&personName, LLNodeBook *&lsBook){	// Tìm kiếm đọc giả theo họ tên trả về danh sách
	Books *book = new Books();
	long int currentPoiter = ftell(fileBook);
	fseek(fileBook, 0, SEEK_SET);

	book = NULL;

	if (fileBook == NULL)
	{
		return false;
	}
	
	while (fread(book, sizeof(book), 1 ,f) != NULL){
		if (strcmp(book->Fullname, personName) == 0)
		{
			// thêm vào danh sách
			fAddAtTail(lsBook, book);
		}
	}
	
	fseek(fileBook, currentPoiter, SEEK_SET);
	return true;
}

Books *getTheLastBook(const FILE *&fileBook){ // Lấy thông tin đọc giả cuối cùng trong file, trả về null nếu file rỗng.
	long int current = ftell(fileBook);

	Books *book = new Books();

	fseek(fileBook, 0, SEEK_SET);
	fread(book, sizeof(Books), 1, fileBook); // lấy độc giả đầu
	if (book == NULL)
	{
		return NULL;
	}

	fseek(fileBook, -sizeof(Books), SEEK_END);
	fread(book, sizeof(Books), 1, fileBook); // lấy đọc giả cuối

	fseek(fileBook, current, SEEK_SET);

	return book;
}

void printfBook(Books book){

	printf("Ma doc gia:\t\t%s\n", book.ID);

	printf("Ho ten day du:\t\t%s\n", book.Fullname);

	printf("CMND:\t\t%s\n", book.NationID);

	printf("Ngay sinh:\t\t");
	printfDay(book.Birthday);

	printf("Gioi tinh:\t\t%s\n", (book.Sex == 0 ? (char *)"Nu" : (char *)"Nam"));

	printf("Thu dien tu:\t\t%s\n", book.Email);

	printf("Dia chi:\t\t%s\n", book.Address);

	printf("Ngay lap the:\t\t");
	printfDay(book.creatCard);

	printf("Ngay het han:\t\t%");
	printfDay(book.expireCard);

}

bool printfAllBook(FILE *fileBook){	// đọc toàn bộ thông tin đọc giả từ file và in ra -> không đưa vào link list
	Books *book = new Books();
	if (fileBook == NULL || book == NULL)
	{
		return 0;
	}
	
	while (fread(book, sizeof(book), 1 ,f) != NULL){
		printfBook(*book);
	}
	
	fseek(fileBook, 0, SEEK_SET);
	return 1;
}

bool printfAllBook(const LLNodeBook *ls){ // int ra thông tin đọc giả từ Link List khi đã có Link List
	NodeBook *pNow = new NodeBook();
	if (ls == NULL || pNow == NULL)
	{
		return 0;
	}
	pNow = ls->pHead;

	int index = 0;
	while(pNow != NULL){
		printf("\nDoc gia thu %d:\n", ++index);
		printfBook(*pNow->book);
		pNow = pNow->pNext;
	}

	return 1;
}

bool getAllBookToLL(const FILE *&fileBook, LLNodeBook *&ls){	// đọc toàn bộ thông tin đọc giả từ file nhưng không in ra -> đưa vào link list
	Books *book = new Books();
	long int currentPoiter = ftell(fileBook);
	fseek(fileBook, 0, SEEK_SET);

	if (fileBook == NULL || book == NULL)
	{
		return 0;
	}
	
	while (fread(book, sizeof(book), 1 ,f) != NULL){
		fAddAtTail(ls, book); // cập nhật vào cuối danh sách
	}
	
	fseek(fileBook, currentPoiter, SEEK_SET);
	return 1;
}

Books *setBookInf(char *readerID){
	Books *book;
	int temp;
 	// thêm mã đọc giả -- tự động
	strcpy(book->ID, readerID);
	// thêm họ và tên
	printf("Nhap Ho va Ten: ");
	gets(book->Fullname);

	printf("Nhap ngay thang nam sinh:\n");
	*book->Birthday = getDayFrmUser();

	strcpy(book->NationID, getISBN());

	printf("Nhap dia chi: ");
	gets(book->Address);

	do
	{
		printf("Nhap gioi tinh (Nam nhap 1; Nu nhap 0): ");
		scanf("%d", &book->Sex);
		temp = getchar();

		if (book->Sex != 0 && book->Sex != 1)
			printf("Vui long nhap lai. Nam nhap 1, Nu nhap 0.\n");
		else break;
	} while (1);

	printf("Nhap dia chi email / thu dien tu: ");
	gets(book->Email);
	
	// ngày lập thẻ -- lấy ngày tạo tài khoản : hôm nay
	book->creatCard = getToday();
	// ngày hết hạn là ngày tối đa được lập của thẻ, ngày tối đa là một hằng số
	book->expireCard = getExpiredDay(book->creatCard);
	//
	return book;
}

bool addAnInfToFile(const FILE *fileBook, const Books *book){	// thêm thông tin đọc giả vào file

	if (fileBook == NULL || book == NULL)
	{
		return 0;
	}

	long int currentPoiter = ftell(fileBook);
	fseek(fileBook, 0, SEEK_END);

	fwrite(book, sizeof(Books), 1, fileBook);

	fseel(fileBook, currentPoiter, SEEK_SET);

	return 1;
}

bool editBookInf(Books *book){

	switch(getNumberPressKey(printfEditBookInf())){
		case 1:
			printf("Nhap Ho va Ten: ");
			gets(book->Fullname);
			break;
		case 2:
			printf("Nhap moi CMND de sua:\n");
			strcpy(book->NationID, getISBN());
			break;
		case 3:
			printf("Nhap ngay thang nam sinh:\n");
			book->Birthday = getDayFrmUser();
			break;
		case 4:
			do
			{
				printf("Nhap gioi tinh (Nam nhap 1; Nu nhap 0): ");
				scanf("%d", &book->Sex);
				int temp = getchar();

				if (book->Sex != 0 && book->Sex != 1)
					printf("Vui long nhap lai. Nam nhap 1, Nu nhap 0.\n");
				else break;
			} while (1);
			break;
		case 5:
			printf("Nhap dia chi email / thu dien tu: ");
			gets(book->Email);
			break;
		case 6:
			printf("Nhap dia chi: ");
			gets(book->Address);
			break;
		case 7:
			book->expireCard = getExpiredDay(getToday());
			break;

	}
	return true;
}

bool askToUpdateBookToFile(){	// cập nhật thông tin đọc giả vào file - có hỏi có chắc chắn muốn cập nhật không
	printf("Ban co chan muon cap nhat khong\n");
	printf("1. Co\n");
	printf("2. Khong\n");

	return (getNumberPressKey(2,1));
}

bool addNewBookInfToFile(FILE *fileBook){  // thêm độc giả vào database

	Books	*book = new Books();
	
	if (fileBook == NULL)
	{
		return 0;
	}

	*book = *getTheLastBook(fileBook);
	if (book == NULL)
	{
		*book = *setBookInf((char*)"000000001");
	}

	char *strID = new char();
	strcpy(strID, book->ID);
	plusOneIntoAString(strID);
	*book = setBookInf(strID);

	if (findBookWithNationID(fileBook, book->NationID) == NULL)
	{
		printf("Doc gia nay da ton tai.\n");
		system("pause");
		return 0;
	}

	switch (askToUpdateBookToFile()){
		case 1:
			addAnInfToFile(fileBook, book);
			break;
		default:
			return 0;
			break;
	}
}

bool viewInfABook(FILE *fileBook){ // Xem thông tin của một người cụ thể
	int choice = 0;
	Books	*book = new Books();
	char *StrGetFrmUser = new char();

	book = NULL;

	if (fileBook == NULL)
	{
		return 0;
	}

	bool flag = false;

	do {
		choice = getNumberPressKey(printfSubMenuBookManagement());
		strcpy(StrGetFrmUser, getStringFrmUser((char*)"Nhap thong tin tim kiem"));

		switch (choice){
			case 1:
				*book = *findBookWithID(fileBook, StrGetFrmUser);
				flag = (book == NULL ? true : false);
				break;
			case 2:
				LLNodeBook *&lsBook = Init();
				findListBookWithName(fileBook, StrGetFrmUser, lsBook);
				flag = (lsBook->pHead == NULL ? true : false);
				break;
		}
		if (flag == false) // tức -> không tìm thấy độc giả.
		{
			printf("Doc gia nay khong ton tai\n");
			return 0;
		}

		if (book != NULL)
		{
			printfBook(*book);	
		}

		if (lsBook->pHead != NULL)
		{
			printfLLNodeBook(lsBook);	
		}
		
	}while (choice != 0);

	return 1;
}

bool deleteBook(const FILE *&fileBook, const Books *&book){ // xoá một độc giả
	FILE *fileBook = fopen("Release/Book/databaseBook.bin", "rb");
	FILE *ftemp = fopen("Release/Book/databaseBookTemp.bin", "wb");

	if (fileBook == NULL || ftemp == NULL)
		return false;

	Books *bookTemp = InitNode();

	while (fread(&bookTemp, sizeof(Books), 1, fileBook) != NULL)
	{
		if (strcmp(book->NationID, bookTemp->NationID) != 0)
			fwrite(&bookTemp, sizeof(Books), 1, ftemp);
		else
			continue;
	}

	fclose(fileBook);
	fclose(ftemp);

	remove((char*)"Release/Book/databaseBook.bin");
	rename((char*)"Release/Book/databaseBookTemp.bin", (char*)"Release/Book/databaseBook.bin");

	return true;
}
bool editBook(Books *&book){ // sửa thông tin độc giả >> doing here 
	switch(getNumberPressKey(editInfBookMenu())){
		case 1: // printf("1. Sua Ho va ten\n");
			printf("Nhap Ho va Ten: ");
			gets(book->Fullname);
			break;
		case 2: // printf("2. Doi CMND\n");
			strcpy(book->NationID, getISBN());
			break;
		case 3: // printf("3. Doi ngay sinh\n");
			printf("Nhap ngay thang nam sinh:\n");
			*book->Birthday = getDayFrmUser();
			break;
		case 4: // printf("4. Doi gioi tinh\n");
			do
			{
				printf("Nhap gioi tinh (Nam nhap 1; Nu nhap 0): ");
				scanf("%d", &book->Sex);
				temp = getchar();

				if (book->Sex != 0 && book->Sex != 1)
					printf("Vui long nhap lai. Nam nhap 1, Nu nhap 0.\n");
				else break;
			} while (1);
			break;
		case 5: // printf("5. Doi Email\n");
			printf("Nhap dia chi email / thu dien tu: ");
			gets(book->Email);
			break;
		case 6: // printf("6. Doi dia chi\n");
			printf("Nhap dia chi: ");
			gets(book->Address);
			break;
		case 7: 
			printf("7. Gia han the toi ngay ");
			book->expireCard = getExpiredDay(getToday());
			printfDay(book->expireCard);
			break;
		default: // printf("0. Quay ve\n");
			break;
	}
	//
}

bool editBookInfToFile(FILE *fileBook){	// chỉnh sửa thông tin đọc giả >> hàm khởi chaỵ
	Books	*book = InitNode();
	LLNodeBook *&lsBook = Init();
	
	if (fileBook == NULL || getTheLastBook(fileBook) == NULL)
	{
		return 0;
	}

	int choice = 0;
	char *StrGetFrmUser = new char();

	do {
		choice = getNumberPressKey(printfSubMenuBookManagement());
		strcpy(StrGetFrmUser, getStringFrmUser((char*)"Nhap thong tin tim kiem"));

		switch (choice){
			case 1: // tìm kiếm theo CMND
				*book = *findBookWithID(fileBook, StrGetFrmUser);
				if (book == NULL)
				{
					printf("Doc gia nay khong ton tai.\n");
					system("pause");
					continue;
				}
				break;
			case 2: // tìm kiếm theo tên
				findListBookWithName(fileBook, StrGetFrmUser, lsBook);
				if (lsBook->pHead == NULL)
				{
					printf("Doc gia nay khong ton tai.\n");
					system("pause");
					continue;
				}
				break;
		}

		Books *bookTemp = new Books();
		if (lsBook->pHead != NULL)
		{
			printfAllBook(lsBook);
			bookTemp = findBookAtNumberic(lsBook, getNumber((char*)"Chon 1 doc gia: "))
			printf("Da chon!\n");
			system("pause");
		}

		if (askToUpdateBookToFile() == true){
			deleteBook(fileBook, book);
			addAnInfToFile(fileBook, bookTemp);
		}
		system("cls");
	}while (choice != 0);
	return 1;

}

bool deleteBookInfToFile(FILE *fileBook){	// xoá thông tin một độc giả - hàm khởi chạy -- lọc >> doing here
	Books	*book = InitNode();
	LLNodeBook *&lsBook = Init();
	
	if (fileBook == NULL || getTheLastBook(fileBook) == NULL)
	{
		return 0;
	}

	int choice = 0;
	char *StrGetFrmUser = new char();

	do {
		choice = getNumberPressKey(printfSubMenuBookManagement());
		strcpy(StrGetFrmUser, getStringFrmUser((char*)"Nhap thong tin tim kiem"));

		switch (choice){
			case 1: // tìm kiếm theo CMND
				*book = *findBookWithID(fileBook, StrGetFrmUser);
				if (book == NULL)
				{
					printf("Doc gia nay khong ton tai.\n");
					system("pause");
					continue;
				}
				break;
			case 2: // tìm kiếm theo tên
				findListBookWithName(fileBook, StrGetFrmUser, lsBook);
				if (lsBook->pHead == NULL)
				{
					printf("Doc gia nay khong ton tai.\n");
					system("pause");
					continue;
				}
				break;
		}
		if (askToUpdateBookToFile() == true){
			if (book != NULL)
				{
					deleteBook(fileBook, book);
				}
				else if (lsBook->pHead != NULL)
				{
					printfAllBook(lsBook);
					deleteBook(fileBook, findBookAtNumberic(lsBook, getNumber((char*)"Chon 1 doc gia: ")));
				}
				else return 0;
				
		}
		system("cls");
	}while (choice != 0);
	return 1;
}


void runBookManagement(){

	FILE *fileBook = fopen("Release/Book/databaseBook.bin", "rb");
	if (fileBook == NULL)
	{
		FILE *fileBook = fopen("Release/Book/databaseBook.bin", "wb");
	}

	int choice = 0;
	do {
		choice = getNumberPressKey(printfMenuBookManagement());
		switch (choice){
			case 1:
				printfAllBook(fileBook);
				break;
			case 2: // printf("2. Them doc gia.\n");
				addNewBookInfToFile(fileBook);
				break;
			case 3: // printf("3. Chinh sua thong tin mot doc gia.\n");
				editBookInfToFile(fileBook);
				break;
			case 4: // printf("4. Xoa thong tin mot doc gia.\n");
				deleteBookInfToFile(fileBook);
				break;
			case 5:
				viewInfABook(fileBook);
				break;
			default:
				break;
		}
	}while (choice != 0);

}


