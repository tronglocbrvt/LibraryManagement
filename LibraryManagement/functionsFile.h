#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define _NAME_FILE_READER_ "databaseReader.bin"

#if defined(_WIN32) || defined(_WIN64)

	#define _DIR_DATA_FOLDER_READER "Database/Reader/databaseReader.bin"
	#define _DIR_DATA_FOLDER_READER_TEMP "Database/Reader/readerTemp.bin"

	#define _DIR_DATA_FOLDER_USER_CUR "Database/Current/currentUser.bin"
	#define _DIR_DATA_FOLDER_USER_TEMP "Database/Users/userTemp.bin"
	#define _DIR_DATA_FOLDER_USER "Database/Users//Users.bin"

	#define _DIR_DATA_FOLDER_BOOK "Database/Book/databaseBook.bin"
	#define _DIR_DATA_FOLDER_BOOK_TEMP "Database/Book/bookTemp.bin" 

	#define _DIR_DATA_FOLDER_BOOK_BORROW "Database/BorrowBook/databaseBorrowBook.bin"
	#define _DIR_DATA_FOLDER_BOOK_BORROW_TEMP "Database/BorrowBook/databaseBorrowBookTemp.bin"

#else

	#define _DIR_DATA_FOLDER_READER "Documents/Github/LibraryManagement/LibraryManagement/Database/Reader/databaseReader.bin"
	#define _DIR_DATA_FOLDER_READER_TEMP "Documents/Github/LibraryManagement/LibraryManagement/Database/Reader/readerTemp.bin"

	#define _DIR_DATA_FOLDER_USER_CUR "Documents/Github/LibraryManagement/LibraryManagement/Database/Current/currentUser.bin"
	#define _DIR_DATA_FOLDER_USER_TEMP "Documents/Github/LibraryManagement/LibraryManagement/Database/Users/userTemp.bin"
	#define _DIR_DATA_FOLDER_USER "Documents/Github/LibraryManagement/LibraryManagement/Database/Users/Users.bin"

	#define _DIR_DATA_FOLDER_BOOK "Documents/Github/LibraryManagement/LibraryManagement/Database/Book/databaseBook.bin"
	#define _DIR_DATA_FOLDER_BOOK_TEMP "Documents/Github/LibraryManagement/LibraryManagement/Database/Book/bookTemp.bin"

	#define _DIR_DATA_FOLDER_BOOK_BORROW "Documents/Github/LibraryManagement/LibraryManagement/Database/BorrowBook/databaseBorrowBook.bin"
	#define _DIR_DATA_FOLDER_BOOK_BORROW_TEMP "Documents/Github/LibraryManagement/LibraryManagement/Database/BorrowBook/databaseBorrowBookTemp.bin"

#endif
