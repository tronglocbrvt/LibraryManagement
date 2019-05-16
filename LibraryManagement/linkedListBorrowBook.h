#pragma once
#include "LibraryManagement.h"

//======================================================
// << Hàm khởi tạo danh sách và node

void Init(LLNodeBorrowBook &ls);

NodeBorrowBook* makeNode(BorrowBooks data);
//======================================================

NodeBorrowBook* addAtTail(LLNodeBorrowBook &ls, BorrowBooks data); // Thêm vào cuối danh sách một struct >> BorrowBook

void freeLinkListBorrowBook(LLNodeBorrowBook &ls);

//=============================================================================================
//=============================================================================================

