#include "analyzingLibrary.h"

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool askToPrintAllBook(LLNodeBook lsbook){ //>> ll book
	NodeBook *pNow = lsbook.pHead;
	if (pNow == NULL)
		return 0;
	char *stringMoneyPayement;
	textBgColor(YELLOW, BLACK);
	switch(getNumberPressKey(askYesNoQuestion((char*)"Ban co muon hien danh sach cac sach trong thu vien khong"), 0)){
		textBgColor(WHITE, BLACK);
		case 1:
			system(cls);
			showTitleListBook();
			
			while(pNow != NULL){
				stringMoneyPayement = intMoneyToStringMoney(pNow->book.priceBook);
				printf("|>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>|\n");
				printf("|^   ISBN:  %-14s  Ten Sach:  %-43sv|\n", pNow->book.ISBN, pNow->book.nameBook);
				printf("|^   Ten tac gia:           %-51s   v|\n", pNow->book.Author);
				printf("|^   The loai:              %-51s   v|\n", pNow->book.Category);
				printf("|^   Nha xuat ban:  %-40sNam xuat ban:  %4d   v|\n", pNow->book.publishCompany, pNow->book.yearPublish);
				printf("|^   So luong sach hien co:  %6d   |  Gia tien:  %18s VND        v|\n", pNow->book.numBook, stringMoneyPayement);
				printf("|<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<|\n");
				pNow = pNow->pNext;
			}
			showFooter();
			stopSceen();
			return true;
		default:
			return false;
	}
	return true;
}
void analyzingBook(){
	showTitleAnalyzingBooks();

	FILE *fileBook = fopen(_DIR_DATA_FOLDER_BOOK, "rb");
	if (fileBook == NULL)
	{
		return;
	}

	LLNodeBook lsbook;
	Init(lsbook);

	Books book;
	while (fread(&book, sizeof(Books), 1, fileBook) != 0){
		addAtTail(lsbook, book);
	}

	printf("So luong sach trong thu vien hien co la: %d\n", lsbook.total);
	if (lsbook.total != 0)
	{
		askToPrintAllBook(lsbook);
	}
	fclose(fileBook);
	freeLinkListBook(lsbook);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool askToPrintAllCato(LLNodeCategory lsCate){ // ll catogory
	NodeCategory *pNow = lsCate.pHead;
	if (pNow == NULL)
		return 0;
	textBgColor(YELLOW, BLACK);
	switch (getNumberPressKey(askYesNoQuestion((char*)"Ban co muon hien danh sach the loai sach trong thu vien khong"), 0)){
		textBgColor(WHITE, BLACK);
		case 1:
			system(cls);
			showTitleCategory();
			printf("|----------------------------------------------------------------------------------|\n");
			while(pNow != NULL){
				printf("|\t%-41s\t|\t%6d quyen\t    |\n", pNow->Category, pNow->numBookPerCategory);
				pNow = pNow->pNext;
				printf("|----------------------------------------------------------------------------------|\n");
			}
			stopSceen();
			return true;
		default:
			return false;
	}

	return true;
}
void analyzingCatoBook(){
	showTitleAnalyzingCato();
	FILE *fileBook = fopen(_DIR_DATA_FOLDER_BOOK, "rb");
	if (fileBook == NULL)
	{
		return;
	}

	LLNodeCategory lsCate;
	Init(lsCate);

	Books book;
	while (fread(&book, sizeof(Books), 1, fileBook) != 0){
		if (!addBooksToExistCategory(lsCate, book.Category, book.numBook)) // đã thêm vào danh sách nhưng thể loại đó chưa được lưu vào danh sách
		{
			addAtTail(lsCate, book.Category, book.numBook);
		}
	}

	printf("Cac the loai sach trong thu vien hien co la %d The loai.\n", lsCate.total);
	if (lsCate.total != 0)
	{
		askToPrintAllCato(lsCate);
	}

	fclose(fileBook);
	freeLinkListBook(lsCate);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool askToPrintAllReader(LLNodeReader lsreader){ // ll reader
	NodeReader *pNow = lsreader.pHead;
	if (pNow == NULL)
		return 0;
	textBgColor(YELLOW, BLACK);
	switch (getNumberPressKey(askYesNoQuestion((char*)"Ban co muon hien danh sach doc gia trong thu vien khong"), 0)){
		textBgColor(WHITE, BLACK);
		case 1:
			system(cls);
			showTitleListReader();
			while(pNow != NULL){
				printf("|<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<|\n");
				printf("|^   ID:\t%-63s   v|\n", pNow->reader.ID);
				printf("|^   Ten:\t%-31s CMND:\t%-23s   v|\n", pNow->reader.Fullname, pNow->reader.NationID);
				printf("|^   Ngay sinh:\t\t%2d . %2d . %4d\t|  \tGioi tinh:\t%-15s   v|\n", pNow->reader.Birthday.Date, pNow->reader.Birthday.Month, pNow->reader.Birthday.Year, (pNow->reader.Sex == 1 ? (char*)"Nam" : (char*)"Nu"));
				printf("|^   Email:\t%-63s   v|\n", pNow->reader.Email);
				printf("|^   Dia chi:\t%-63s   v|\n", pNow->reader.Address);
				printf("|^   Ngay lap the:\t%2d . %2d . %4d  |\tNgay het han:\t%2d . %2d . %4d    v|\n", pNow->reader.creatCard.Date, pNow->reader.creatCard.Month, pNow->reader.creatCard.Year, pNow->reader.expireCard.Date, pNow->reader.expireCard.Month, pNow->reader.expireCard.Year);
				printf("|>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>|\n");
				pNow = pNow->pNext;
			}
			stopSceen();
			return true;
		default:
			return false;
	}

	return true;
}
void analyzingReader(){
	showTitleAnalyzingReaders();
	FILE *fileReader = fopen(_DIR_DATA_FOLDER_READER, "rb");
	if (fileReader == NULL)
	{
		return;
	}

	LLNodeReader lsreader;
	Init(lsreader);

	Readers reader;
	while (fread(&reader, sizeof(Readers), 1, fileReader) != 0){
		addAtTail(lsreader, reader);
	}

	printf("So luong doc gia dang dang ky voi Thu vien la: %d\n", lsreader.total);
	if (lsreader.total != 0)
	{
		askToPrintAllReader(lsreader);
	}
	fclose(fileReader);
	freeLinkListReader(lsreader);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool askToPrintAllSexReader(LLNodeReader lsMaleReader, LLNodeReader lsFemaleReader){ // 2 ll sex
	NodeReader *pNow = lsMaleReader.pHead;
	textBgColor(YELLOW, BLACK);
	switch (getNumberPressKey(askYesNoQuestion((char*)"Ban co muon hien danh sach doc gia trong gioi tinh khong"), 0)){
		textBgColor(WHITE, BLACK);
		case 1:
			system(cls);
			showTitleMaleReader();
			while(pNow != NULL){
				printf("|<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<|\n");
				printf("|^   ID:\t%-63s   v|\n", pNow->reader.ID);
				printf("|^   Ten:\t%-31s CMND:\t%-23s   v|\n", pNow->reader.Fullname, pNow->reader.NationID);
				printf("|^   Ngay sinh:\t\t%2d . %2d . %4d\t|  \tGioi tinh:\t%-15s   v|\n", pNow->reader.Birthday.Date, pNow->reader.Birthday.Month, pNow->reader.Birthday.Year, (pNow->reader.Sex == 1 ? (char*)"Nam" : (char*)"Nu"));
				printf("|^   Email:\t%-63s   v|\n", pNow->reader.Email);
				printf("|^   Dia chi:\t%-63s   v|\n", pNow->reader.Address);
				printf("|^   Ngay lap the:\t%2d . %2d . %4d  |\tNgay het han:\t%2d . %2d . %4d    v|\n", pNow->reader.creatCard.Date, pNow->reader.creatCard.Month, pNow->reader.creatCard.Year, pNow->reader.expireCard.Date, pNow->reader.expireCard.Month, pNow->reader.expireCard.Year);
				printf("|>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>|\n");
				pNow = pNow->pNext;
			}
			stopSceen();
			system(cls);
			showTitleFemaleReader();
			pNow = lsFemaleReader.pHead;
			while(pNow != NULL){
				printf("|<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<|\n");
				printf("|^   ID:\t%-63s   v|\n", pNow->reader.ID);
				printf("|^   Ten:\t%-31s CMND:\t%-23s   v|\n", pNow->reader.Fullname, pNow->reader.NationID);
				printf("|^   Ngay sinh:\t\t%2d . %2d . %4d\t|  \tGioi tinh:\t%-15s   v|\n", pNow->reader.Birthday.Date, pNow->reader.Birthday.Month, pNow->reader.Birthday.Year, (pNow->reader.Sex == 1 ? (char*)"Nam" : (char*)"Nu"));
				printf("|^   Email:\t%-63s   v|\n", pNow->reader.Email);
				printf("|^   Dia chi:\t%-63s   v|\n", pNow->reader.Address);
				printf("|^   Ngay lap the:\t%2d . %2d . %4d  |\tNgay het han:\t%2d . %2d . %4d    v|\n", pNow->reader.creatCard.Date, pNow->reader.creatCard.Month, pNow->reader.creatCard.Year, pNow->reader.expireCard.Date, pNow->reader.expireCard.Month, pNow->reader.expireCard.Year);
				printf("|>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>|\n");
				pNow = pNow->pNext;
			}
			stopSceen();
			return true;
		default:
			return false;
	}

	return true;
}
void analyzingSexReader(){
	showTitleAnalyzingSex();
	FILE *fileReader = fopen(_DIR_DATA_FOLDER_READER, "rb");
	if (fileReader == NULL)
	{
		return;
	}

	LLNodeReader lsMaleReader;
	LLNodeReader lsFemaleReader;
	Init(lsMaleReader);
	Init(lsFemaleReader);

	Readers reader;
	while (fread(&reader, sizeof(Readers), 1, fileReader) != 0){
		if (reader.Sex == 1)
		{
			addAtTail(lsMaleReader, reader);	
		}
		else
		{
			addAtTail(lsFemaleReader, reader);	
		}
	}

	printf("Thu vien co %d doc gia nam va co %d doc gia nu.\n", lsMaleReader.total, lsFemaleReader.total);
	if (lsMaleReader.total != 0 || lsFemaleReader.total != 0)
	{
		askToPrintAllSexReader(lsMaleReader, lsFemaleReader);
	}
	fclose(fileReader);
	freeLinkListReader(lsMaleReader);
	freeLinkListReader(lsFemaleReader);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool askToPrintAllBorrowingBook(LLNodeBorrowBook lsBorBook){ // ll borrowbook
	NodeBorrowBook *pNow = lsBorBook.pHead;;
	textBgColor(YELLOW, BLACK);
	switch (getNumberPressKey(askYesNoQuestion((char*)"Ban co muon hien danh sach cac sach dang duoc muon khong"), 0)){
		textBgColor(WHITE, BLACK);
		case 1:
			system(cls);
			showTitleListBorrowing();
			while(pNow != NULL){
				printf("|<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<|\n");
				printf("|^   ID:     %-14s |   Ten doc gia:\t%-31s   v|\n", pNow->brBook.ID, pNow->brBook.Fullname);
				printf("|^   ISBN:   %-14s |   Ten cuon sach:\t%-31s   v|\n", pNow->brBook.ISBN, pNow->brBook.nameBook);
				printf("|^   So luong sach da muon:\t\t\t%-30d    v|\n", pNow->brBook.numBook);
				printf("|^   Ngay muon sach:\t%2d . %2d . %4d   |   Ngay tra sach:\t%2d . %2d . %4d    v|\n", pNow->brBook.borrowBookDay.Date, pNow->brBook.borrowBookDay.Month, pNow->brBook.borrowBookDay.Year, pNow->brBook.returnBookDay.Date, pNow->brBook.returnBookDay.Month, pNow->brBook.returnBookDay.Year);
				printf("|>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>|\n");
				pNow = pNow->pNext;
			}
			return true;
		default:
			return false;
	}
	return true;
}
void analyzingBorrowingBook(){
	showTitleAnalyzingBorrowBook();
	FILE *fileBorBook = fopen(_DIR_DATA_FOLDER_BOOK_BORROW, "rb");
	if (fileBorBook == NULL)
	{
		return;
	}

	LLNodeBorrowBook lsBorBook;
	Init(lsBorBook);

	BorrowBooks borBook;
	while (fread(&borBook, sizeof(BorrowBooks), 1, fileBorBook) != 0){
		addAtTail(lsBorBook, borBook);
	}

	printf("So luong sach ma doc gia dang muon trong thu vien hien co la:\t%d\n", lsBorBook.total);
	if (lsBorBook.total != 0)
	{
		askToPrintAllBorrowingBook(lsBorBook);
	}
	fclose(fileBorBook);
	freeLinkListBorrowBook(lsBorBook);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool askToPrintAllOverdueReader(LLNodeBorrowBook lsBorBook){ // ll borrowbook
	NodeBorrowBook *pNow = lsBorBook.pHead;
	textBgColor(YELLOW, BLACK);
	switch (getNumberPressKey(askYesNoQuestion((char*)"Ban co muon hien danh sach cac doc gia bi tre han tra sach khong"), 0)){
		textBgColor(WHITE, BLACK);
		case 1:
			system(cls);
			showTitleOverdue();
			while(pNow != NULL){
				printf("|<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<|\n");
				printf("|^   ID:     %-14s |   Ten doc gia:\t%-31s   v|\n", pNow->brBook.ID, pNow->brBook.Fullname);
				printf("|^   ISBN:   %-14s |   Ten cuon sach:\t%-31s   v|\n", pNow->brBook.ISBN, pNow->brBook.nameBook);
				printf("|^   So luong sach da muon:\t\t\t%-30d    v|\n", pNow->brBook.numBook);
				printf("|^   Ngay muon sach:\t%2d . %2d . %4d   |   Ngay tra sach:\t%2d . %2d . %4d    v|\n", pNow->brBook.borrowBookDay.Date, pNow->brBook.borrowBookDay.Month, pNow->brBook.borrowBookDay.Year, pNow->brBook.returnBookDay.Date, pNow->brBook.returnBookDay.Month, pNow->brBook.returnBookDay.Year);
				printf("|>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>|\n");
				pNow = pNow->pNext;
			}
			return true;
		default:
			return false;
	}

	return true;
}
void analyzingOverdueReader(){
	showTitleAnalyzingOverdue();
	FILE *fileBorBook = fopen(_DIR_DATA_FOLDER_BOOK_BORROW, "rb");
	if (fileBorBook == NULL)
	{
		return;
	}

	LLNodeBorrowBook lsBorBook;
	Init(lsBorBook);

	BorrowBooks borBook;
	Day today = getToday();
	while (fread(&borBook, sizeof(BorrowBooks), 1, fileBorBook) != 0){
		if (today - borBook.returnBookDay > 0)
		{
			addAtTail(lsBorBook, borBook);
		}
	}
	printf("So luong doc gia trong thu vien dang bi tre han tra sach:\t%d\n", lsBorBook.total);
	if (lsBorBook.total != 0)
	{
		askToPrintAllOverdueReader(lsBorBook);
	}
	fclose(fileBorBook);
	freeLinkListBorrowBook(lsBorBook);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void runningAnalyzingForAdmin(){
	int choice = 0;
	do {
		choice = getNumberPressKey(analyzingMenuForAdmin(), 0);
		system(cls);
		switch (choice){
			case 1: // Thống kê số lượng sách trong thư viện
				analyzingBook();
				break;
			case 2: // Thống kê số lượng sách theo thể loại
				analyzingCatoBook();
				break;
			case 3: // Thống kê số lượng độc giả
				analyzingReader();
				break;
			case 4: // Thống kê số lượng độc giả theo giới tính
				analyzingSexReader();
				break;
			case 5: // Thống kê số sách đang được mượn
				analyzingBorrowingBook();
				break;
			case 6: // Thống kê danh sách độc giả bị trễ hạn
				analyzingOverdueReader();
				break;
			default:
				break;
		}
	} while (choice != 0);
}
void runningAnalyzingForExpert(){
	int choice = 0;
	do {
		choice = getNumberPressKey(analyzingMenuForExpert(), 0);
		system(cls);
		switch (choice){
			case 1: // Thống kê số sách đang được mượn
				analyzingBorrowingBook();
				break;
			case 2: // Thống kê danh sách độc giả bị trễ hạn
				analyzingOverdueReader();
				break;
			default:
				break;
		}
	} while (choice != 0);
}
void runningAnalyzingForManager(){
	int choice = 0;
	do {
		choice = getNumberPressKey(analyzingMenuManager(), 0);
		system(cls);
		switch (choice){
			case 1: // Thống kê số lượng sách trong thư viện
				analyzingBook();
				break;
			case 2: // Thống kê số lượng sách theo thể loại
				analyzingCatoBook();
				break;
			case 3: // Thống kê số lượng độc giả
				analyzingReader();
				break;
			case 4: // Thống kê số lượng độc giả theo giới tính
				analyzingSexReader();
				break;
			case 5: // Thống kê số sách đang được mượn
				analyzingBorrowingBook();
				break;
			case 6: // Thống kê danh sách độc giả bị trễ hạn
				analyzingOverdueReader();
				break;
			default:
				break;
		}
	} while (choice != 0);
}

void runningAnalyzing(int typeAccount){
	switch(typeAccount){
		case 1: // admin
			runningAnalyzingForAdmin();
			break;
		case 2: // chuyên viên
			runningAnalyzingForExpert();
			break;
		default: // quản lý
			runningAnalyzingForManager();
			break;
	}

}