#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#pragma once
#include "Course.h"
struct User
{
    char UserName[50], FullName[100], Email[50], Password[100], Class[50], Phone[15];
    int Type;
};
struct Node
{
    User data;
    Node* next;
};
struct UserList
{
    Node* head;
};

void initUserList(UserList &l);
void Import(UserList &l, ifstream &fin);
void CreateAccount(UserList &l, UserList &l2, int choose,ClassList* &classlist);
int login(UserList &l , User &tmp);
void ImportStudent(UserList &l, UserList &l2,ClassList* &classlist);
void ViewStudentClass(ClassList* classlist);
void ViewStudentCourse(CourseList * courselist);
void LogInMenu(UserList &l, UserList &l2, ifstream &fin, ifstream &fin2,User &user);