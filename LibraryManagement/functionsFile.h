#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define _NAME_FILE_READER_ "databaseReader.bin"

#if defined(_WIN32) || defined(_WIN64)

	#define _DIR_DATA_FOLDER_READER "Release/Reader/databaseReader.bin"
	#define _DIR_DATA_FOLDER_READER_TEMP "Release/Reader/readerTemp.bin"

	#define _DIR_DATA_FOLDER_USER_CUR "Release/Current/currentUser.bin"
	#define _DIR_DATA_FOLDER_USER_TEMP "Release/Users/userTemp.bin"
	#define _DIR_DATA_FOLDER_USER "Release/Users/Users.bin"

	#define _DIR_DATA_FOLDER_BOOK "Release/Book/databaseBook.bin"
	#define _DIR_DATA_FOLDER_BOOK_TEMP "Release/Book/bookTemp.bin" 

	#define _DIR_DATA_FOLDER_BOOK_BORROW "Release/BorrowBook/databaseBorrowBook.bin"
	#define _DIR_DATA_FOLDER_BOOK_BORROW_TEMP "Release/BorrowBook/databaseBorrowBookTemp.bin"

#else

	#define _DIR_DATA_FOLDER_READER "Documents/Github/LibraryManagement/LibraryManagement/Release/Reader/databaseReader.bin"
	#define _DIR_DATA_FOLDER_READER_TEMP "Documents/Github/LibraryManagement/LibraryManagement/Release/Reader/readerTemp.bin"

	#define _DIR_DATA_FOLDER_USER_CUR "Documents/Github/LibraryManagement/LibraryManagement/Release/Current/currentUser.bin"
	#define _DIR_DATA_FOLDER_USER_TEMP "Documents/Github/LibraryManagement/LibraryManagement/Release/Users/userTemp.bin"
	#define _DIR_DATA_FOLDER_USER "Documents/Github/LibraryManagement/LibraryManagement/Release/Users/Users.bin"

	#define _DIR_DATA_FOLDER_BOOK "Documents/Github/LibraryManagement/LibraryManagement/Release/Book/databaseBook.bin"
	#define _DIR_DATA_FOLDER_BOOK_TEMP "Documents/Github/LibraryManagement/LibraryManagement/Release/Book/bookTemp.bin"

	#define _DIR_DATA_FOLDER_BOOK_BORROW "Documents/Github/LibraryManagement/LibraryManagement/Release/BorrowBook/databaseBorrowBook.bin"
	#define _DIR_DATA_FOLDER_BOOK_BORROW_TEMP "Documents/Github/LibraryManagement/LibraryManagement/Release/BorrowBook/databaseBorrowBookTemp.bin"

#endif

// #define _NAME_FILE_VIEW "CurAccount.txt"
// #define _MAX_CHAR_OF_INF_ 32
// #define _END_LINE_MACOS_ 2
// #define _STRING_LOREM ""

FILE *openFile(char* dir, char *nameFile, char *mode);