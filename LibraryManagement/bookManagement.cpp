#include "bookManagement.h"

Books *findBookWithISBN(char *ISBN)	// Tìm kiếm sách theo ISBN
{
	Books *book = new Books;

	FILE* fileBook = fopen(_DIR_DATA_FOLDER_BOOK, "rb");

	if (book == NULL || fileBook == NULL)
	{
		return NULL;
	}

	while (fread(book, sizeof(Books), 1, fileBook) != 0){
		if (strcmp(book->ISBN, ISBN) == 0)
		{
			fclose(fileBook);
			return book;
		}
	}

	fclose(fileBook);
	delete book;
	return NULL;
}

bool findListBookWithName(char *nameBook, LLNodeBook &lsBook){	// Tìm kiếm sách theo tên sách
	Books *book = new Books;

	if (book == NULL)
		return 0;

	FILE* fileBook = fopen(_DIR_DATA_FOLDER_BOOK, "rb");

	if (fileBook == NULL)
	{
		return 0;
	}

	int flag = 0;
	while (fread(book, sizeof(Books), 1, fileBook) != 0){
		if (strcmpi(book->nameBook, nameBook) == 0)
		{
			// thêm vào danh sách
			addAtTail(lsBook, *book);
			flag = 1;
		}
	}

	delete book;
	fclose(fileBook);
	if (flag == 1)
		return 1;
	return 0;
}

void viewAllBook()	// đọc toàn bộ thông tin sách từ file và in ra
{
	Books *book = new Books;
	FILE* fileBook = fopen(_DIR_DATA_FOLDER_BOOK, "rb");

	if (fileBook == NULL || book == NULL)
	{	
		return;
	}

	system(cls);
	showTitleViewBook();

	while (fread(book, sizeof(Books), 1, fileBook) != 0){
		viewInfABook(*book);
	}
	
	fclose(fileBook);
	delete book;
	stopSceen();
}

bool printBookFromLL(LLNodeBook ls){ // in ra thông tin sách từ Linked List
	NodeBook *pNow = new NodeBook;
	if (pNow == NULL)
	{
		return 0;
	}

	pNow = ls.pHead;

	while (pNow != NULL){
		viewInfABook(pNow->book);
		pNow = pNow->pNext;
	}

	return 1;
}

Books addBook()
{
	Books book;

	int flag = 0;
	do
	{
		flushall();
		printf("Nhap ISBN < 13 chu so >: ");
		gets(book.ISBN);

		if (strlen(book.ISBN) != 13)
		{
			printf("ISBN phai co 13 chu so. Vui long nhap lai.\n");
			continue;
		}

		flag = 1;
		for (int i = 0; i < strlen(book.ISBN); i++)
		{
			if (!isNumber(book.ISBN[i]))
			{
				flag = 0;
				printf("ISBN khong hop le. Vui long nhap lai.\n");
				break;
			}
		}


	} while (flag == 0);

	// getchar();
	printf("Nhap ten sach: ");
	gets(book.nameBook);

	printf("Nhap ten tac gia: ");
	gets(book.Author);

	printf("Nhap ten nha xuat ban: ");
	gets(book.publishCompany);

	printf("Nhap nam xuat ban: ");
	scanf("%d", &book.yearPublish);

	flushall();
	printf("Nhap the loai: ");
	gets(book.Category);

	printf("Nhap gia tien: ");
	scanf("%ld", &book.priceBook);

	printf("Nhap so quyen sach: ");
	scanf("%d", &book.numBook);

	return book;
}

int askToUpdateBookToFile() // cập nhật thông tin sách vào file - hỏi có chắc chắn muốn cập nhật không?
{
	textBgColor(PURPLE, BLACK);
	printf("Ban co chan muon cap nhat khong?\n");
	printf("1. Co\n");
	printf("2. Khong\n");
	textBgColor(WHITE, BLACK);

	return (getNumberPressKey(2, 1));
}

bool writeInfBookToFile() // thêm sách vào database
{
	system(cls);
	showTitleAddNewBook();
	Books book = addBook();

	Books *temp = findBookWithISBN(book.ISBN);

	switch (askToUpdateBookToFile()){
		case 1:
			if (temp != NULL)
			{
				system(cls);
				showTitleAddNewBook();
				textBgColor(RED, BLACK);
				printf("ISBN nay da ton tai.\n");
				Sleep(1000); // ngưng màn hình 1 giây cho người dùng đọc
				delete temp;
				return 0;
			}
			else
			{
				FILE *f = fopen(_DIR_DATA_FOLDER_BOOK, "ab");

				if (f == NULL)
					return 0;

				fwrite(&book, sizeof(Books), 1, f);
				fclose(f);
				
				system(cls);
				showTitleAddNewBook();
				textBgColor(RED, BLACK);
				printf("Them thong tin sach thanh cong.\n");
				Sleep(1000);
				delete temp;
				break;
			}
		default:
			delete temp;
			return 0;
		}
	return 1;
}

void viewInfABook(Books book) // Xem thông tin của sách
{
	textBgColor(WHITE, BLACK);
	char *stringMoneyPayement = intMoneyToStringMoney(book.priceBook);
	printf("|>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>|\n");
	printf("|^   ISBN:  %-14s  Ten Sach:  %-43sv|\n", book.ISBN, book.nameBook);
	printf("|^   Ten tac gia:           %-51s   v|\n", book.Author);
	printf("|^   The loai:              %-51s   v|\n", book.Category);
	printf("|^   Nha xuat ban:  %-40sNam xuat ban:  %4d   v|\n", book.publishCompany, book.yearPublish);
	printf("|^   So luong sach hien co:  %6d   |  Gia tien:  %18s VND        v|\n", book.numBook, stringMoneyPayement);
	printf("|<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<|\n");
}

bool editBook(Books &book){ // sửa thông tin sách

	int edit;
	bool end = false;
	do
	{
		textBgColor(WHITE, BLACK);
		switch (getNumberPressKey(editInfBookMenu(), 0)){
		case 0:
			return 0;
		case 1: // Sửa tên sách
			flushall();
			printf("\n");
			printf("Nhap ten sach moi: ");
			gets(book.nameBook);
			edit = wantEdit();
			if (edit == 0)
				end = true;
			break;
		case 2: // Sửa tên tác giả
			flushall();
			printf("Nhap ten tac gia moi: ");
			gets(book.Author);
			edit = wantEdit();
			if (edit == 0)
				end = true;
			break;
		case 3: // Sửa tên nhà xuất bản
			flushall();
			printf("Nhap ten nha xuat ban moi: ");
			gets(book.publishCompany);
			edit = wantEdit();
			if (edit == 0)
				end = true;
			break;
		case 4: // Sửa năm xuất bản
			flushall();
			printf("Nhap nam xuat ban moi: ");
			scanf("%d", &book.yearPublish);
			edit = wantEdit();
			if (edit == 0)
				end = true;
			break;
		case 5: // Sửa thể loại sách
			flushall();
			printf("Nhap the loai sach moi: ");
			gets(book.Category);
			edit = wantEdit();
			if (edit == 0)
				end = true;
			break;
		case 6: // Sửa giá sách
			flushall();
			printf("Nhap gia sach moi: ");
			scanf("%ld", &book.priceBook);
			edit = wantEdit();
			if (edit == 0)
				end = true;
			break;
		case 7: // Sửa số lượng sách
			flushall();
			printf("Nhap so luong sach moi: ");
			scanf("%d", &book.numBook);
			edit = wantEdit();
			if (edit == 0)
				end = true;
			break;
		default: // quay về
			break;
		}
	} while (end == false);
	return 1;
}

void editBookToFile()
{
	FILE *fo = fopen(_DIR_DATA_FOLDER_BOOK, "rb");
	FILE *ftemp = fopen(_DIR_DATA_FOLDER_BOOK_TEMP, "wb");

	if (fo == NULL || ftemp == NULL)
		return;

	Books temp;
	Books *book = new Books;
	if (book == NULL)
		return;

	system(cls);
	showTitleEditBook();
	flushall();
	printf("Nhap vao ISBN cua sach muon chinh sua: ");
	gets(book->ISBN);

	book = findBookWithISBN(book->ISBN);
	if (book == NULL)
	{
		system(cls);
		showTitleEditBook();
		textBgColor(RED, BLACK);
		printf("Sach khong ton tai.\n");
		Sleep(1000);
		fclose(fo);
		fclose(ftemp);
		delete book;
		return;
	}

	viewInfABook(*book);

	while (fread(&temp, sizeof(Books), 1, fo) != 0)
	{
		if (strcmp(book->ISBN, temp.ISBN) != 0)
			fwrite(&temp, sizeof(Books), 1, ftemp);
		else
		{
			if (editBook(*book))
			{
				fwrite(book, sizeof(Books), 1, ftemp);
				textBgColor(RED, BLACK);
				printf("Chinh sua thanh cong.\n");
				textBgColor(WHITE, BLACK);
				Sleep(1000);
				system(cls);
				showTitleAfterEditBook();
				viewInfABook(*book);
				stopSceen();
			}
			else 
				fwrite(book, sizeof(Books), 1, ftemp);
		}
		
	}
	fclose(fo);
	fclose(ftemp);
	delete book;
	remove((char*)_DIR_DATA_FOLDER_BOOK);
	rename((char*)_DIR_DATA_FOLDER_BOOK_TEMP, (char*)_DIR_DATA_FOLDER_BOOK);
}

void deleteBookToFile() // Xóa sách trong file
{

	FILE *fo = fopen(_DIR_DATA_FOLDER_BOOK, "rb");
	FILE *ftemp = fopen(_DIR_DATA_FOLDER_BOOK_TEMP, "wb");

	if (fo == NULL || ftemp == NULL)
		return;

	Books temp;
	Books *book = new Books;
	if (book == NULL)
		return;

	system(cls);
	showTitleDeleteBook();
	flushall();
	printf("Nhap vao ISBN cua sach muon xoa: ");
	gets(book->ISBN);

	book = findBookWithISBN(book->ISBN);
	if (book == NULL)
	{
		system(cls);
		showTitleDeleteBook();
		textBgColor(RED, BLACK);
		printf("Sach khong ton tai.\n");
		Sleep(1000);
		fclose(fo);
		fclose(ftemp);
		delete book;
		return;
	}

	textBgColor(PURPLE, BLACK);
	printf("Thong tin cuon sach chuan bi xoa: \n");
	viewInfABook(*book);

	textBgColor(PURPLE, BLACK);
	printf("Ban co chac chan muon xoa? \n- 1. Dong y \n- 0. Huy\n");
	textBgColor(WHITE, BLACK);

	switch (getNumberPressKey(1, 0)){
		case 1:
			break;
		default:
			fclose(fo);
			fclose(ftemp);
			delete book;
			remove((char*)_DIR_DATA_FOLDER_BOOK_TEMP);
			return;
	}

	while (fread(&temp, sizeof(Books), 1, fo) != 0)
	{
		if (strcmp(book->ISBN, temp.ISBN) != 0)
			fwrite(&temp, sizeof(Books), 1, ftemp);
	}
	system(cls);
	showTitleDeleteBook();
	textBgColor(RED, BLACK);
	printf("Xoa thanh cong.\n");
	Sleep(1000);
	textBgColor(WHITE, BLACK);

	fclose(fo);
	fclose(ftemp);
	delete book;
	remove((char*)_DIR_DATA_FOLDER_BOOK);
	rename((char*)_DIR_DATA_FOLDER_BOOK_TEMP, (char*)_DIR_DATA_FOLDER_BOOK);
}

void searchISBN() // Tìm sách qua ISBN
{
	Books *book = new Books;

	if (book == NULL)
		return;

	system(cls);
	showTitleFindBookByISBN();

	flushall();
	printf("Nhap vao ISBN: ");
	gets(book->ISBN);

	book = findBookWithISBN(book->ISBN);
	if (book == NULL)
	{
		system(cls);
		showTitleFindBookByISBN();
		textBgColor(RED, BLACK);
		printf("Sach khong ton tai.\n");
		Sleep(1000);
	}
	else
	{
		viewInfABook(*book);
		stopSceen();
	}

	delete book;
}

void searchBookName()
{
	Books *book = new Books;
	if (book == NULL)
		return;

	system(cls);
	showTitleFindBookByName();

	flushall();
	printf("Nhap ten sach: ");
	gets(book->nameBook);

	LLNodeBook lsBook;
	Init(lsBook);

	if (!(findListBookWithName(book->nameBook, lsBook)))
	{
		system(cls);
		showTitleFindBookByName();
		textBgColor(RED, BLACK);
		printf("Sach khong ton tai.\n");
		Sleep(1000);
	}

	else
	{
		system(cls);
		showTitleFindBookByName();
		printBookFromLL(lsBook);
		stopSceen();
	}

	freeLinkListBook(lsBook);
	delete book;
}

void runBookManagementForAdmin(){
	int choice = 0;
	do {
		choice = getNumberPressKey(printfMenuBookManagementForAdmin(), 0);
		system(cls);
		switch (choice){
		case 1: // xem danh sách sách trong thư viện
			viewAllBook();
			break;
		case 2: // Thêm sách
			writeInfBookToFile();
			break;
		case 3: // Chỉnh sửa thông tin một quyển sách
			editBookToFile();
			break;
		case 4: // Xóa thông tin 1 quyển sách
			deleteBookToFile();
			break;
		case 5: // Tìm kiếm sách qua ISBN
			searchISBN();
			break;
		case 6: // Tìm kiếm sách qua tên sách.
			searchBookName();
			break;
		default:
			break;
		}
	} while (choice != 0);
}
void runBookManagementForExpert(){
	int choice = 0;
	do {
		choice = getNumberPressKey(printfMenuBookManagementForExpert(), 0);
		system(cls);
		switch (choice){
		case 1: // Tìm kiếm sách qua ISBN
			searchISBN();
			break;
		case 2: // Tìm kiếm sách qua tên sách.
			searchBookName();
			break;
		default:
			break;
		}
	} while (choice != 0);
}
void runBookManagementForManager(){
	int choice = 0;
	do {
		choice = getNumberPressKey(printfMenuBookManagementForManager(), 0);
		system(cls);
		switch (choice){
		case 1: // xem danh sách sách trong thư viện
			viewAllBook();
			break;
		case 2: // Thêm sách
			writeInfBookToFile();
			break;
		case 3: // Chỉnh sửa thông tin một quyển sách
			editBookToFile();
			break;
		case 4: // Xóa thông tin 1 quyển sách
			deleteBookToFile();
			break;
		case 5: // Tìm kiếm sách qua ISBN
			searchISBN();
			break;
		case 6: // Tìm kiếm sách qua tên sách.
			searchBookName();
			break;
		default:
			break;
		}
	} while (choice != 0);
}
void runBookManagement(int typeAccount)
{
	switch(typeAccount){
		case 1:
			runBookManagementForAdmin();
			break;
		case 2:
			runBookManagementForExpert();
			break;
		default:
			runBookManagementForManager();
			break;
	}
}
