#pragma once
#include "LibraryManagement.h"

//======================================================
// << Hàm khởi tạo danh sách và node

void Init(LLNodeBook &ls);

NodeBook *makeNode(Books data);
//======================================================

NodeBook* addAtTail(LLNodeBook &ls, Books data); // Thêm vào cuối danh sách một struct >> Books

void freeLinkListBook(LLNodeBook &ls);

//=============================================================================================
//=============================================================================================

