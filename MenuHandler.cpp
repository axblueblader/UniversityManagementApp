#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#pragma once
#include "MenuHandler.h";
// Formatting output
void Padding(char* s)
{
	int pad = (70-strlen(s)-2) / 2;
	int stop = strlen(s) + pad + 2;
	cout << "|";
	for (int i = 0; i < pad; i++)
	{
		cout << " ";
	}
	for (int i = 0; i < strlen(s); i++)
	{
		cout << s[i];
	}
	for (int i = 0; i <= pad; i++)
	{
		if (stop == 70)
		{
			break;
		}
		stop++;
		cout << " ";
	}
	cout << "|" << endl;
}

void Seperater()
{
	cout << "----------------------------------------------------------------------" << endl;
}
// ----------------

void PrintMenu(int x,char fullname[])
{
	switch (x)
	{
	case 0:
		Padding("*STUDENT MENU*");
		Padding(fullname);
		Seperater();
		Padding("1.CHECK ATTENDANCE");
		Padding("2.VIEW ATTENDANCE");
		Padding("0.LOGOUT");
		break;
	case 1:
		Padding("STAFF MENU");
		Padding(fullname);
		Seperater();
		Padding("1.IMPORT COURSES");
		Padding("2.IMPORT STUDENT LISTS");
		Padding("3.CREATE A USER");
		Padding("4.EXPORT SCORES OF EXAM IN COURSE");
		Padding("5.EXPORT SCORES OF A STUDENT");
		Padding("6.EXPORT STUDENT PRESENCES");
		Padding("7.VIEW STUDENT IN A CLASS");
		Padding("8.VIEW STUDENT IN A COURSE");
		Padding("0.LOGOUT");
		break;
	case 2:
		Padding("LECTURER MENU");
		Padding(fullname);
		Seperater();
		Padding("1.IMPORT SCORES OF EXAM IN COURSE");
		Padding("2.EDIT SCORES OF STUDENT IN EXAM");
		Padding("3.VIEW SCORES OF EXAM IN COURSE");
		Padding("4.EXPORT SCORES OF EXAM IN COURSE");
		Padding("5.EXPORT SCORES OF A STUDENT");
		Padding("0.LOGOUT");
		break;
	}
	Seperater();
	cout << "CHOICE: ";
}

