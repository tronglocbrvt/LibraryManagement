#pragma once
#include "LibraryManagement.h"

//======================================================
// << Hàm khởi tạo danh sách và node

void Init(LLNodeReader &ls);

NodeReader *makeNode(Readers data);
//======================================================

NodeReader* addAtTail(LLNodeReader &ls, Readers data); // Thêm vào cuối danh sách một struct >> Readers

//Readers *findReaderAtNumberic(LLNodeReader *lsReader, int numberic);

void freeLinkListReader(LLNodeReader &ls);

//=============================================================================================
//=============================================================================================

