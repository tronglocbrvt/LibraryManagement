#include "bookManagement.h"
#include "commonFunction.h"
#include "linkedListBooks.h"

Books *findBookWithISBN(char *ISBN)	// Tìm kiếm sách theo ISBN
{
	Books *book = new Books;

	FILE* fileBook = fopen("Release/Book/databaseBook.bin", "rb");

	if (fileBook == NULL)
	{
		return NULL;
	}

	while (fread(book, sizeof(Books), 1, fileBook) != NULL){
		if (strcmp(book->ISBN, ISBN) == 0)
		{
			fclose(fileBook);
			return book;
		}
	}

	fclose(fileBook);
	return NULL;
}

bool findListBookWithName(char *nameBook, LLNodeBook &lsBook){	// Tìm kiếm đọc giả theo họ tên trả về danh sách
	Books *book = new Books;

	if (book == NULL)
		return 0;

	FILE* fileBook = fopen("Release/Book/databaseBook.bin", "rb");

	if (fileBook == NULL)
	{
		return 0;
	}

	while (fread(book, sizeof(Books), 1, fileBook) != NULL){
		if (strcmp(book->nameBook, nameBook) == 0)
		{
			// thêm vào danh sách
			addAtTail(lsBook, *book);
		}
	}

	delete book;
	fclose(fileBook);
	return true;
}

void viewAllBook()	// đọc toàn bộ thông tin độc giả từ file và in ra
{
	Books *book = new Books;

	FILE* fileBook = fopen("Release/Book/databaseBook.bin", "rb");

	if (fileBook == NULL || book == NULL)
	{
		return;
	}

	while (fread(book, sizeof(Books), 1, fileBook) != NULL){
		viewInfABook(*book);
	}

	fclose(fileBook);
	delete book;
}

bool printBookFromLL(LLNodeBook ls){ // in ra thông tin độc giả từ Linked List
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
		printf("Nhap ISBN: ");
		gets(book.ISBN);

		int i;
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

	flushall();
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
	printf("Ban co chan muon cap nhat khong\n");
	printf("1. Co\n");
	printf("2. Khong\n");

	return (getNumberPressKey(2, 1));
}

bool writeInfBookToFile() // thêm sách vào database
{
	Books	book = addBook();

	Books *temp = findBookWithISBN(book.ISBN);

	switch (askToUpdateBookToFile()){
	case 1:
		if (temp != NULL)
		{
			printf("ISBN nay da ton tai.\n");
			Sleep(1000); // ngưng màn hình 1 giây cho người dùng đọc
			delete temp;
			return 0;
		}
		else
		{
			FILE *f = fopen("Release/Book/databaseBook.bin", "ab");

			if (f == NULL)
				return 0;

			fwrite(&book, sizeof(Books), 1, f);
			fclose(f);
			printf("Them thong tin sach thanh cong.\n");
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
	printf("--------------------------------------------------------\n");
	printf("Thong tin sach voi ma ISBN: %s\n", book.ISBN);
	printf("Ten sach: %s\n", book.nameBook);
	printf("Ten tac gia: %s\n", book.Author);
	printf("Nha xuat ban: %s\n", book.publishCompany);
	printf("Nam xuat ban: %d\n", book.yearPublish);
	printf("The loai sach: %s\n", book.Category);
	printf("Gia 1 quyen sach: %ld\n", book.priceBook);
	printf("So luong sach: %d\n", book.numBook);
	printf("--------------------------------------------------------\n");
}

void editBook(Books &book){ // sửa thông tin sách

	int edit;
	bool end = false;
	do
	{
		switch (getNumberPressKey(editInfBookMenu(), 0)){
		case 1: // Sửa tên sách
			flushall();
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
			return;
		}
	} while (end == false);
}

void editBookToFile()
{
	FILE *fo = fopen("Release/Book/databaseBook.bin", "rb");
	FILE *ftemp = fopen("Release/Book/bookTemp.bin", "wb");

	if (fo == NULL || ftemp == NULL)
		return;

	Books temp;
	Books *book = new Books;
	if (book == NULL)
		return;

	flushall();
	printf("Nhap vao ISBN cua sach muon chinh sua: ");
	gets(book->ISBN);

	book = findBookWithISBN(book->ISBN);
	if (book == NULL)
	{
		printf("Sach khong ton tai.\n");
		Sleep(1000);
		delete book;
		return;
	}

	viewInfABook(*book);
	while (fread(&temp, sizeof(Books), 1, fo) != NULL)
	{
		if (strcmp(book->ISBN, temp.ISBN) != 0)
			fwrite(&temp, sizeof(Books), 1, ftemp);
		else
		{
			editBook(*book);
			fwrite(book, sizeof(Books), 1, ftemp);
		}
	}
	textBgColor(RED, BLACK);
	printf("Chinh sua thanh cong.\n");
	textBgColor(WHITE, BLACK);
	viewInfABook(*book);
	fclose(fo);
	fclose(ftemp);
	delete book;
	remove((char*)"Release/Book/databaseBook.bin");
	rename((char*)"Release/Book/bookTemp.bin", (char*)"Release/Book/databaseBook.bin");
}

void deleteBookToFile()
{

	FILE *fo = fopen("Release/Book/databaseBook.bin", "rb");
	FILE *ftemp = fopen("Release/Book/bookTemp.bin", "wb");

	if (fo == NULL || ftemp == NULL)
		return;

	Books temp;
	Books *book = new Books;
	if (book == NULL)
		return;

	flushall();
	printf("Nhap vao ISBN cua sach muon chinh sua: ");
	gets(book->ISBN);

	book = findBookWithISBN(book->ISBN);
	if (book == NULL)
	{
		printf("Sach khong ton tai.\n");
		Sleep(1000);
		delete book;
		return;
	}

	while (fread(&temp, sizeof(Books), 1, fo) != NULL)
	{
		if (strcmp(book->ISBN, temp.ISBN) != 0)
			fwrite(&temp, sizeof(Books), 1, ftemp);
	}
	textBgColor(RED, BLACK);
	printf("Xoa thanh cong.\n");
	textBgColor(WHITE, BLACK);

	fclose(fo);
	fclose(ftemp);
	delete book;
	remove((char*)"Release/Book/databaseBook.bin");
	rename((char*)"Release/Book/bookTemp.bin", (char*)"Release/Book/databaseBook.bin");
}

void searchISBN()
{
	Books *book = new Books;

	flushall();
	printf("Nhap vao ISBN: ");
	gets(book->ISBN);

	book = findBookWithISBN(book->ISBN);
	if (book == NULL)
	{
		printf("Sach khong ton tai.\n");
		Sleep(1000);
	}
	else
		viewInfABook(*book);

	delete book;
}

void searchBookName()
{
	Books *book = new Books;

	flushall();
	printf("Nhap ten sach: ");
	gets(book->nameBook);

	LLNodeBook lsBook;
	Init(lsBook);

	if (!(findListBookWithName(book->nameBook, lsBook)))
	{
		printf("Sach khong ton tai.\n");
		Sleep(1000);
	}

	else
		printBookFromLL(lsBook);

	freeLinkListBook(lsBook);
	delete book;
}

void runBookManagement()
{
	int choice = 0;
	do {
		choice = getNumberPressKey(printfMenuBookManagement(), 0);
		system("cls");
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