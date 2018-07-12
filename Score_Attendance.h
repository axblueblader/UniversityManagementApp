#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#pragma once
#include "MenuHandler.h"
#include "function.h"
// ATTENDANCE STRUCTURE

struct AttendanceN
{
	char studentid[10];
	int week[10];
	AttendanceN* next;
};

struct AttendanceL
{
	char courseid[10];
	char year[10];
	char semester[2];
	int numberofstudents;
	AttendanceN* student;
	AttendanceL* next;
};

struct StudentScores
{
	int studentid;
	int midterm;
	int lab;
	int finals;
	StudentScores* next;
};

struct ScoreCourses
{
	char courseid[10];
	char year[10];
	char semester[2];
	int studentcount;
	StudentScores* studentnode;
	ScoreCourses* next;
};

void ImportScoreOfExamFromFile(ScoreCourses* &scorelist);

void SaveScoresData(ScoreCourses *& scorelist);

void LoadScoresData(ScoreCourses *& scorelist);

void AddScoreProfile(ScoreCourses *& scorelist, CourseList * coursenode);

void EditScore(ScoreCourses *& scorelist);

void ExportScoreForCourse(ScoreCourses *& scorelist);

void ViewScoreOfCourse(ScoreCourses *& scorelist);

void ExportScoreForStudent(ScoreCourses* &scorelist);

void AddAttProfile(AttendanceL* &attlist, CourseList* coursenode);

void SaveAttData(AttendanceL* &attlist);

void LoadAttData(AttendanceL* &attlist);

bool CheckAttendance(User student, AttendanceL * atl, CourseList * cl);

void Present(AttendanceL *& c);

void Absent(AttendanceL *& c);

bool ViewAttendance(AttendanceL * a, int studentid);


/*	FILE FORMAT PRESENCE
	[courseid],[year],[semester],[studentcount],,,,,,,
	[studentid1],0,1,2,3,4,5,6,7,8,9
	[studentidn],0,1,2,3,4,5,6,7,8,9
*/

/* FILE FORMAT SCORES
	[courseid],[year],[semester],[studentcount]
	[studentid1],[mid],[lab],[final]
	[studentidn],[mid],[lab],[final]

*/