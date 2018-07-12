#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#pragma once
#include "MasterHeader.h"

struct StudentIDList
{
	int studentid;
	StudentIDList* next;
};

struct ClassList
{
	char name[10];
	int numberofstudents;
	StudentIDList* studentIDList;
	ClassList* next;
};

struct Course
{
	char CourseCode[10];
	char Year[10];
	int Semester;
	char CourseName[50];
	char LecturerName[50];
	char StartDate[12];
	char EndDate[12];
	char FromTime[10];
	char ToTime[10];
	int DateOfWeek;
	int studentcount;
	StudentIDList* studenthead;
};

struct CourseList
{
	Course data;
	CourseList* pnext;
};


struct ScheduleNode
{
	char CourseCode[10];
	char Year[10];
	int Semester;
	char StartDate[12];
	char EndDate[12];
	char FromTime[10];
	char ToTime[10];
	int Dateofweek;
	ScheduleNode *next;
};

struct ScheduleList
{
	ScheduleNode *head;
};

void initCourseList(CourseList* &cl);
int importCourse(CourseList* &cl, ClassList* &clsl);
void ExportCourse(CourseList * courselist);
void outputCourse(CourseList * cl);
//void importCourseFunction(CourseList *& cl, ClassList * &clsl);
void Schedule(ScheduleList & a, CourseList *& courselist);
void ExportClassList(ClassList *& classlist);
void ImportClassList(ClassList *& classlist);
void addCourse(Course* &c, ClassList* &clsl,ofstream &file,int choice);
void addCourseList(CourseList* &cl, char code[],char year[], int sem);
void outputCourseList(CourseList* cl);
void importCoursefromfile(CourseList* &cl, ClassList* &clsl);
