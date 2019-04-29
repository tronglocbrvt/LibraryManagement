#pragma once
#include "LibraryManagement.h"

bool checkUsername(char *Username);

void getUsername(Users &A);

void getBirthday(Users &A);

void getNationalID(Users &A);

void getSex(Users &A);

void getStatus(Users &A);

void getTypeAccount(Users &A);

Users addUser();

void writeFile();

void getUser(int typeAccount);
