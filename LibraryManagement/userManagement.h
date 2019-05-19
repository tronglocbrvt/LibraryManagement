#pragma once
#include "LibraryManagement.h"

int checkLogin(char *Username, char *Password);

int Logout();

int Login();

bool checkUsername(char *Username);

Users addUser();

void writeInfUsertoFile();

void getUser(int typeAccount);

void updateFile(Users curUser);

void ChangePassword();

void viewProfile();

void editProfile();

void inforDecentraliseUser();

void decentraliseUser(int typeAccount);

void inforStatusUser();

void changeStatusUser(int typeAccount);

void runMenuUser(int typeAccount);