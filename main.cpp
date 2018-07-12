#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#pragma once
#include "MenuHandler.h"
#include "Score_Attendance.h"
using namespace std;

int main()
{
	
	//INTIALIZE
	ClassList* classlist;
	classlist = NULL;
	ImportClassList(classlist);
	ScoreCourses* scorelist;
	scorelist = NULL;
	LoadScoresData(scorelist);
	CourseList* courselist;
	CourseList* tmpcl;
	initCourseList(courselist);
	importCoursefromfile(courselist,classlist);
	UserList l, l2;
	initUserList(l);
	initUserList(l2);
	User curuser;	
	AttendanceL* attlist;
	attlist = NULL;
	LoadAttData(attlist);
	ifstream fin, fin2;

	int choice, type, x, n;
	char cname[10], cyear[10];
	int csem, cweek, sid;
	char chsem[2], chweek[2];
	int semester, week;
	char courseid[10], sem[2];
	bool looping;
	//--------------------------------------------
	//LOGIN SCREEN
	while (true)
	{
		system("CLS");
		Seperater();
		LogInMenu(l, l2, fin, fin2, curuser);
		type = curuser.Type;
		//AFTER LOGIN

		switch (type)
		{
		#pragma region StudentCase
		case 0:
			choice = -1;
			while (choice)
			{
				system("CLS");
				PrintMenu(type, curuser.FullName);
				while (!(cin >> choice)) {
					cin.clear();
					cin.ignore(256, '\n');
					cout << "Invalid input!" << endl;
					cout << "CHOICE: ";

				}
				cin.get();
				switch (choice)
				{
				case 1:				
					looping = true;
					while (looping)
					{
						system("CLS");
						Padding("CHECKING ATTENDANCE");
						Seperater();
						/*cout << endl << "Please input Course ID: ";
						cin.getline(courseid, 10);
						cout << "Please input Year: "; 
						cin.getline(cyear, 10);
						cout << "Please input Semester(1-3): ";
						cin.getline(sem, 2);
						semester = atoi(sem);
						if (semester > 3 || semester < 1)
						{
							cout << "Invalid input, please reenter(1-3): ";
							cin.getline(sem, 2);
							semester = atoi(sem);
						}
						cout << "Please input Week: ";
						cin.getline(chweek, 2);
						week = atoi(chweek);
						if (week > 10 || week < 1)
						{
							cout << "Invalid input, please reenter(1-10): ";
							cin.getline(chweek, 2);
							week = atoi(chweek);
						}
						Seperater();*/
						if (!CheckAttendance(curuser,attlist,courselist))
						{
							cout << "Failed to check in,input 1 to retry or 0 to go back to previous menu" << endl;
							cout << "INPUT: ";
							char exiter;
							cin >> exiter; cin.get();
							if (exiter == '0')
							{
								break;
							}
						}
						else looping = false;
					}
					SaveAttData(attlist);
					break;
				case 2: // VIEW ATTENDANCE
					if (!ViewAttendance(attlist, atoi(curuser.UserName)))
					{
						Seperater();
						Padding("YOU HAVENT REGISTER INTO THIS COURSE YET");
						
					}
					Seperater();
					system("PAUSE");
					break;
				case 0: cout << "Logging out" << endl;
					break;
				default: cout << "Invalid choice" << endl;
					break;
				}
			}			
			break;
#pragma endregion

		#pragma region StaffCase
		case 1:
			choice = -1;
			 
			while (choice)
			{
				system("CLS");
				PrintMenu(type, curuser.FullName);
				while (!(cin >> choice)) {
					cin.clear();
					cin.ignore(256, '\n');
					cout << "Invalid input!" << endl;
					cout << "CHOICE: ";
					
				}
				cin.get();
				switch (choice)
				{
				case 1:
					system("CLS");
					Padding("IMPORT COURSES");
					Seperater();
					Padding("1.ADD COURSES");
					Padding("2.IMPORT COURSES FORM CSV");
					Padding("3.VIEW LIST OF COURSES");
					Padding("0.BACK");
					Seperater();
					cout << "CHOICE: ";
					cin >> x; cin.get();
					switch (x)
					{
					case 1:
						n = importCourse(courselist, classlist);
						tmpcl = courselist;
						ExportClassList(classlist);
						outputCourseList(courselist);
						for (int i = 0; i < n; i++)
						{
							AddAttProfile(attlist, tmpcl);
							AddScoreProfile(scorelist, tmpcl);
							tmpcl = tmpcl->pnext;
						}
						SaveAttData(attlist);
						SaveScoresData(scorelist);
						
						break;
					case 2:
						system("CLS");
						Seperater();
						Padding("PLEASE PUT THE NEW COURSE CSV FILE IN THE COURSES FOLDER");
						Padding("ALSO ADD THE COURSEID,YEAR,SEMESTER TO THE COURSELIST.CSV");
						Seperater();
						Padding("1. START IMPORT PROCESS");
						Padding("0. BACK");
						Seperater();
						cout << "CHOICE: "; cin >> x; cin.get();
						if (x==1)
						{
							importCoursefromfile(courselist, classlist);
							outputCourse(courselist);
							outputCourseList(courselist);
							Seperater();
							Padding("IMPORT SUCCESSFUL");
							Seperater();
						}
						break;
					case 3:
						outputCourse(courselist);
						break;
					}
					break; 
				case 2: //IMPORT CLASSES
					CreateAccount(l, l2, 1, classlist);
					ExportClassList(classlist);
					break;
				case 3: 
					CreateAccount(l, l2, 2,classlist);
					break;
				case 4: //SCORE OF AN EXAM IN COURSE
					ExportScoreForCourse(scorelist);
					system("PAUSE");
					break;
				case 5: 
					ExportScoreForStudent(scorelist);
					system("PAUSE");
					break;
				case 6: 
					Present(attlist);
					Absent(attlist);
					break;
				case 7: // VIEW STUDENT IN CLASS
					ViewStudentClass(classlist);
					break;
				case 8: // VIEW STUDENT IN COURSE
					ViewStudentCourse(courselist);
					break;
				case 0: cout << "Logging out" << endl;
					break;
				default: cout << "Invalid choice" << endl;
					break;
				}
			}
			break;
#pragma endregion

		#pragma region LecturerCase
		case 2:
			choice = -1;
			while (choice)
			{
				system("CLS");
				PrintMenu(type, curuser.FullName);
				while (!(cin >> choice)) {
					cin.clear();
					cin.ignore(256, '\n');
					cout << "Invalid input!" << endl;
					cout << "CHOICE: ";

				}
				cin.get();
				switch (choice)
				{
				case 1: // IMPORT SCORES FOR EXAM
					ImportScoreOfExamFromFile(scorelist);
					SaveScoresData(scorelist);
					break;
				case 2: // EDIT
					EditScore(scorelist);
					SaveScoresData(scorelist);
					break;
				case 3: // VIEW
					ViewScoreOfCourse(scorelist);
					break;
				case 4: // EXPORT EXAM
					ExportScoreForCourse(scorelist);
					system("PAUSE");
					break;
				case 5: // EXPORT STUDENT
					ExportScoreForStudent(scorelist);
					system("PAUSE");
					break;
				case 0: cout << "Logging out" << endl;
					break;
				default: cout << "Invalid choice" << endl;
					break;
				}
			}
			break;
#pragma endregion
		}
	}
}



