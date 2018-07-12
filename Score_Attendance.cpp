#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "Score_Attendance.h"

// SCORE

void ImportScoreOfExamFromFile(ScoreCourses* &scorelist)
{
	char courseid[10],year[10],semester[2],s[100],exch[2],buffer[10];
	bool found = false;
	int exam,studentid,score,n;
	ScoreCourses* curS = scorelist; // current node for ScoreCourses
	StudentScores* curN; // current node for StudentScores
	ifstream file;

	cout << "Input course ID: ";
	cin.getline(courseid, 10);
	cout << "Input year(yyyy-yyyy): ";
	cin.getline(year, 10);
	cout << "Input semester(1-3): ";
	cin.getline(semester, 2);
	while (curS != NULL)
	{
		found = !strcmp(courseid, curS->courseid)
			&& !strcmp(year, curS->year)
			&& !strcmp(semester, curS->semester);
		if (found)
		{
			cout << "Input exam type(0-mid,1-lab,2-final): ";
			cin >> exam; cin.get();
			strcpy(s, "./Scores/");
			strcat(s, courseid); strcat(s, "_");
			strcat(s, year); strcat(s, "_");
			strcat(s, semester); strcat(s,"_");
			_itoa(exam, exch, 10);
			strcat(s, exch); strcat(s, ".csv");
			file.open(s);
			if (!file.is_open())
			{
				Seperater();
				Padding(s);
				Padding("NOT FOUND IN FOLDER");
				Seperater();
				system("PAUSE");
				return;
			}
			file.getline(buffer, 10);
			n = atoi(buffer);
			for (int i = 0; i < n; i++)
			{
				file.getline(buffer, 10, ',');
				studentid = atoi(buffer);
				file.getline(buffer, 4);
				score = atoi(buffer);
				curN = curS->studentnode;
				while (curN != NULL)
				{
					if (curN->studentid == studentid)
					{
						switch (exam)
						{
						case 0: curN->midterm = score;
							break;
						case 1: curN->lab = score;
							break;
						case 2: curN->finals = score;
							break;
						}
						break;
					}
					curN = curN->next;
				}
			}
			file.close();
			if (!found)
			{
				cout << "Course not found!" << endl;
				system("PAUSE");
			}
			else
			{
				Seperater();
				Padding("IMPORT SUCCESSFUL");
				Seperater();
				system("PAUSE");
			}
			return;
		}
		curS = curS->next;
	}
}

/*	SCORE FILE FORMAT
	[courseid]_[year]_[semester]_[0,1,2].csv (0-mid,1-lab,2-final)
	n = number students
	IN FILE:
	n
	[studentid-1],[score-1]
	[studentid-2],[score-2]
	...
	[studentid-n],[score-n]
*/
void SaveScoresData(ScoreCourses* &scorelist)
{
	ScoreCourses* curS = scorelist;
	StudentScores* curN;
	ofstream file;
	file.open("scores.csv");
	while (curS != NULL)
	{
		file << curS->courseid << ",";
		file << curS->year << ",";
		file << curS->semester << ",";
		file << curS->studentcount << endl;
		curN = curS->studentnode;
		while (curN != NULL)
		{
			file << curN->studentid << ",";
			file << curN->midterm << "," << curN->lab << "," << curN->finals << endl;
			curN = curN->next;
		}
		curS = curS->next;
	}
	file.close();
}

void LoadScoresData(ScoreCourses* &scorelist)
{
	ScoreCourses* tmpS;
//	StudentScores* curN;
	StudentScores* tmpN;
	ifstream file;
	file.open("scores.csv");
	char numch[10];
	while (!file.eof())
	{
		tmpS = new ScoreCourses;
		file.getline(tmpS->courseid,10,',');
		if (file.fail() || !strcmp(tmpS->courseid, "\n"))
		{
			delete tmpS;
			break;
		}
		//if (strcmp(tmpS->courseid, "") == 0) break;
		file.getline(tmpS->year, 10, ',');
		file.getline(tmpS->semester, 2, ',');
		file.getline(numch, 3);
		tmpS->studentcount = atoi(numch);
		tmpS->studentnode = NULL;
		for (int i = 0; i < tmpS->studentcount; i++)
		{
			tmpN = new StudentScores;
			file.getline(numch, 10, ',');
			tmpN->studentid = atoi(numch);
			file.getline(numch, 3, ',');
			tmpN->midterm = atoi(numch);
			file.getline(numch, 3, ',');
			tmpN->lab = atoi(numch);
			file.getline(numch, 3);
			tmpN->finals = atoi(numch);
			tmpN->next = tmpS->studentnode;
			tmpS->studentnode = tmpN;
		}
		tmpS->next = scorelist;
		scorelist = tmpS;
	}
	file.close();
}

// INITIALIZE A SCORE NODE TO THE SCORELIST, USE WHEN A NEW COURSE IS ADDED
void AddScoreProfile(ScoreCourses* &scorelist, CourseList* coursenode)
{
	ScoreCourses* tmpS = new ScoreCourses;
	StudentScores* tmpN;
	strcpy(tmpS->courseid, coursenode->data.CourseCode);
	strcpy(tmpS->year, coursenode->data.Year);
	_itoa(coursenode->data.Semester,tmpS->semester,10);
	tmpS->studentcount = coursenode->data.studentcount;
	tmpS->next = scorelist;
	tmpS->studentnode = NULL;
	StudentIDList* tmpI = coursenode->data.studenthead;
	for (int i = 0; i < tmpS->studentcount; i++)
	{
		tmpN = new StudentScores;
		tmpN->next = tmpS->studentnode;
		tmpN->midterm = tmpN->lab = tmpN->finals = -1;
		tmpN->studentid = tmpI->studentid;
		tmpI = tmpI->next;
		tmpS->studentnode = tmpN;
	}
	scorelist = tmpS;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void EditScore(ScoreCourses* &scorelist)
{
	char courseid[10], year[10], semester[2];
	int studentid = 1,m,l,f,exam;
	bool found,foundc;
	ScoreCourses* curS = scorelist;
	StudentScores* curN;
	cout << "Input courseid: "; cin.getline(courseid, 10);
	cout << "Input year(yyyy-yyyy): "; cin.getline(year, 10);
	cout << "Input semster(1-3): "; cin.getline(semester, 2);
	foundc = false;
	while (curS != NULL)
	{
		if (!strcmp(courseid, curS->courseid)
			&& !strcmp(year, curS->year)
			&& !strcmp(semester, curS->semester))
		{
			foundc = true;
			break;
		}
		curS = curS->next;
	}
	if (!foundc)
	{
		Padding("COURSE NOT FOUND");
		system("PAUSE");
		return;
	}
	cout << "Input exam type(0-mid,1-lab,2-final): ";
	cin >> exam; cin.get();
	while (studentid)
	{
		system("CLS");
		Padding("MODIFYING SCORE FOR COURSE");
		Seperater();
		Padding(courseid);
		Padding(year);
		Padding(semester);
		Seperater();
		cout << "Input student ID(0 to go back): ";
		cin >> studentid; cin.get();
		curN = curS->studentnode;
		found = false;
		while (curN != NULL)
		{
			if (curN->studentid == studentid)
			{
				switch (exam)
				{
				case 0: cout << "Midterm score is : ";
					cin >> curN->midterm; cin.get();
					break;
				case 1: cout << "Lab score is: ";
					cin >> curN->lab; cin.get();
					break;
				case 2: cout << "Final score is: ";
					cin >> curN->finals; cin.get();
					break;
				default:
					break;
				}
				found = true;
				break;
			}
			curN = curN->next;
		}
		if (found)
		{
			Seperater();
			Padding("SCORES UPDATED");
			Seperater();
			system("PAUSE");
		}
		else
		{
			Seperater();
			Padding("STUDENT NOT IN COURSE");
			Seperater();
			system("PAUSE");
		}
		
	}
}

void ExportScoreForCourse(ScoreCourses* &scorelist)
{
	bool found = false,exported = false;
	char courseid[10], year[10], semester[2],s[50];
	int exam;
	ofstream fout;
	ScoreCourses* curS = scorelist;
	StudentScores* curN;
	cout << "Input course ID: ";
	cin.getline(courseid, 10);
	cout << "Input year(yyyy-yyyy): ";
	cin.getline(year, 10);
	cout << "Input semester(1-3): ";
	cin.getline(semester, 2);
	cout << "Input exam type(0-mid,1-lab,2-final): ";
	cin >> exam; cin.get();
	while (curS != NULL)
	{
		found = !strcmp(courseid, curS->courseid)
			&& !strcmp(year, curS->year)
			&& !strcmp(semester, curS->semester);
		if (found)
		{
			strcpy(s, "./Scores/");
			strcat(s, courseid);
			strcat(s, "_");
			strcat(s, year);
			strcat(s, "_");
			strcat(s, semester);
			strcat(s, "_");
			switch (exam)
			{
			case 0: strcat(s, "midterm");
				break;
			case 1: strcat(s, "lab");
				break;
			case 2: strcat(s, "final");
				break;
			}
			strcat(s, "_scores");
			strcat(s, ".csv");
			fout.open(s);
			cout << "Number of students: " << curS->studentcount << endl;
			curN = curS->studentnode;
			while (curN != NULL)
			{
				fout << curN->studentid << ",";
				switch (exam)
				{
				case 0: fout << curN->midterm << endl;
					break;
				case 1: fout << curN->lab << endl;
					break;
				case 2:fout << curN->finals << endl;
					break;
				}
				curN = curN->next;
			}
			exported = true;
			break;			
		}
		curS = curS->next;
	}
	fout.close();
	if (exported)
	{
		Seperater();
		Padding("EXPORT TO FILE SUCCESSFUL");
		Seperater();
	}
	else
	{
		Seperater();
		Padding("DATA FOR COURSE NOT FOUND");
		Seperater();
	}
}

void ViewScoreOfCourse(ScoreCourses* &scorelist)
{
	bool found = false, exported = false;
	char courseid[10], year[10], semester[2], s[50];
	int exam;
	ofstream fout;
	ScoreCourses* curS = scorelist;
	StudentScores* curN;
	cout << "Input course ID: ";
	cin.getline(courseid, 10);
	cout << "Input year(yyyy-yyyy): ";
	cin.getline(year, 10);
	cout << "Input semester(1-3): ";
	cin.getline(semester, 2);
	cout << "Input exam type(0-mid,1-lab,2-final): ";
	cin >> exam; cin.get();
	while (curS != NULL)
	{
		found = !strcmp(courseid, curS->courseid)
			&& !strcmp(year, curS->year)
			&& !strcmp(semester, curS->semester);
		if (found)
		{
			curN = curS->studentnode;
			while (curN!=NULL)
			{
				cout << curN->studentid << ",";
				switch (exam)
				{
				case 0: 
					cout << curN->midterm << endl;
					break;
				case 1: 
					cout << curN->lab << endl;
					break;
				case 2:
					cout << curN->finals << endl;
					break;
				}
				curN = curN->next;
			}
			exported = true;
		}
		curS = curS->next;
	}
	fout.close();
	if (exported)
	{
		Seperater();
		Padding("PRINT TO CONSOLE SUCCESSFUL");
		Seperater();
	}
	else
	{
		Seperater();
		Padding("DATA FOR COURSE NOT FOUND");
		Seperater();
	}
	system("PAUSE");
}

void ExportScoreForStudent(ScoreCourses* &scorelist)
{
	bool exported = false;
	char s[50],tmp[13];
	int sid;
	ofstream fout;
	ScoreCourses* curS = scorelist;
	StudentScores* curN;
	cout << "Please enter student ID: " << endl;
	cin.getline(tmp, 12);
	sid = atoi(tmp);
	strcpy(s, "./Scores/");
	strcat(s, tmp);
	strcat(s, "_");
	strcat(s, "Scores.csv");
	fout.open(s,ios::trunc);
	while (curS != NULL)
	{
		curN = curS->studentnode;
		while (curN != NULL)
		{
			if (sid == curN->studentid)
			{				
				fout << curS->courseid << "," << curS->year << "," << curS->semester << ",";
				fout << curN->midterm << "," << curN->lab << "," << curN->finals << endl;
				exported = true;
			}
			curN = curN->next;
		}

		curS = curS->next;
	}
	fout.close();
	if (exported)
	{
		Seperater();
		Padding("EXPORT TO FILE SUCCESSFUL");
		Seperater();
	}
	else
	{
		Seperater();
		Padding("DATA FOR STUDENT NOT FOUND");
		Seperater();
	}
}
//----------------------------------------------------------------------------

// ATTENDANCE
void AddAttProfile(AttendanceL* &attlist, CourseList* coursenode)
{
	AttendanceL* newL = new AttendanceL; // list for all course
	AttendanceN* newN;// list of student corresponding each course
	strcpy(newL->courseid, coursenode->data.CourseCode);
	strcpy(newL->year, coursenode->data.Year);
	_itoa(coursenode->data.Semester, newL->semester, 10);
	newL->numberofstudents = coursenode->data.studentcount;
	newL->next = attlist;
	newL->student = NULL;
	StudentIDList* tmpI = coursenode->data.studenthead;
	for (int i = 0; i < newL->numberofstudents; i++)
	{
		newN = new AttendanceN;
		_itoa(tmpI->studentid,newN->studentid,10);
		for (int i = 0; i < 10; i++)
		{
			newN->week[i] = 0;
		}
		newN->next = newL->student;
		newL->student = newN;
		tmpI = tmpI->next;
	}
	attlist = newL;
}

void SaveAttData(AttendanceL *& attlist)
{
	AttendanceL* curL = attlist;
	AttendanceN* curN;
	ofstream file;
	file.open("attendance.csv");
	while (curL != NULL)
	{
		file << curL->courseid << "," << curL->year << "," << curL->semester << "," << curL->numberofstudents;
		for (int i = 0; i < 7; i++)
		{
			file << ",";
		}
		file << endl;
		curN = curL->student;
		for (int i = 0; i < curL->numberofstudents; i++)
		{
			file << curN->studentid << ",";
			for (int j = 0; j < 9; j++)
			{
				file << curN->week[j] << ",";
			}
			file << curN->week[9] << endl;
			curN = curN->next;
		}
		curL = curL->next;
	}
	file.close();

}

void LoadAttData(AttendanceL *& attlist)
{
	AttendanceL* newL;
	AttendanceN* newN;
	ifstream file;
	file.open("attendance.csv");
	char buffer[10];
	while (!file.eof())
	{
		newL = new AttendanceL;
		file.getline(newL->courseid, 10, ',');
		if (file.fail() || strcmp(newL->courseid, "\n") == 0)
		{
			delete newL;
			break;
		}
		file.getline(newL->year, 10, ',');
		file.getline(newL->semester, 2, ',');
		file.getline(buffer, 4,',');
		newL->numberofstudents = atoi(buffer);
		newL->student = NULL;
		file.getline(buffer, 10);
		for (int i = 0; i < newL->numberofstudents; i++)
		{
			newN = new AttendanceN;
			file.getline(newN->studentid, 10, ',');
			for (int j = 0; j < 9; j++)
			{
				file.getline(buffer, 2, ',');
				newN->week[j] = atoi(buffer);
			}
			file.getline(buffer, 2);
			newN->week[9] = atoi(buffer);
			newN->next = newL->student;
			newL->student = newN;
		}
		newL->next = attlist;
		attlist = newL;
	}
}

bool CheckAttendance(User student, AttendanceL* atl, CourseList* cl)
{
	AttendanceL* curatl = atl;
	AttendanceN* curN;
	CourseList* curcl = cl;

	bool  intime = false, foundc;
	time_t     now = time(0);
	struct tm  tstruct;
	tstruct = *localtime(&now);

	char courseid[10],year[10],semester[2]; 

	int day, month, intyear, shour, sminute, ehour, eminute, week;
	double diff;
	//input
	cout << "Input course ID: ";
	cin.getline(courseid, 10);
	cout << "Input year(yyyy-yyyy): ";
	cin.getline(year, 10);
	cout << "Input semester(1-3): ";
	cin.getline(semester, 2);
	//-------------------------------------------------------------
	while (curcl != NULL)
	{
		if (!strcmp(courseid, curcl->data.CourseCode) && !strcmp(year, curcl->data.Year) && atoi(semester) == curcl->data.Semester)
		{
			sscanf(curcl->data.StartDate, "%2d/%2d/%4d", &day, &month, &intyear);
			sscanf(curcl->data.FromTime, "%2d:%2d", &shour, &sminute);
			sscanf(curcl->data.ToTime, "%2d:%2d", &ehour, &eminute);
			tm sdstruct = { 0,sminute,shour,day,month - 1,intyear - 1900 };
			time_t sdd = mktime(&sdstruct);
			if (now != (time_t)(-1) && sdd != (time_t)(-1))
			{
				diff = difftime(now, sdd);
			}
			week = (int)(diff / (60 * 60 * 24 * 7)) + 1; // in seconds?
			intime = (tstruct.tm_hour * 60 + tstruct.tm_min) >= (shour * 60 + sminute)
				&& (tstruct.tm_hour * 60 + tstruct.tm_min) <= (ehour * 60 + eminute)
				&& week <= 10
				&& tstruct.tm_wday == curcl->data.DateOfWeek;
		}
		curcl = curcl->pnext;
	}
	if (!intime)
	{
		return false;
	}
	else
	{
		while (curatl != NULL)
		{
			foundc = !strcmp(curatl->courseid, courseid)
				&& !strcmp(curatl->year, year)
				&& !strcmp(curatl->semester, semester);
			curN = curatl->student;
			while (foundc && curN !=- NULL)
			{
				if (!strcmp(curN->studentid,student.UserName))
				{
					if (curN->week[week-1] == 1)
					{
						cout << "You have already checked in" << endl;
						system("PAUSE");
					}
					else
					{
						curN->week[week - 1] = 1;
						//---------------------------------------------------------
						char       buf[80];
						strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
						//---------------------------------------------------------

						cout << "Checked in: " << courseid << " " << year << " semester " << semester << " week " << week << " today at " << buf << endl;
						system("PAUSE");
					}
					return true;
				}
				curN = curN->next;
			}
			curatl = curatl->next;
		}
	}
	return false;
}
//----------------------------------------------------------------------------

/*	FILE OUTPUT PRESENT/ABSENT FORMAT
	filename = [courseid]_[year]_Present.csv
			 = [courseid]_[year]_Absent.csv
	
	[studentid1],{week number that student present(absent)}
	example 1, present:
	1651001,1,3,5,7,8,10
	1651002,1
	1651003,4,6,7,9,10
	1651010,1,2,3,4,5,6,7,8,9,10
	~
	example 2, absent:
	1651001,2,4,6,9
	1651002,2,3,4,5,6,7,8,9,10
	1651003,1,2,3,5,8
	1651010
	~
*/
	
void Present(AttendanceL *&c)
{
	char courseid[10], year[10], semester[2], s[50];
	int k = 0;
	bool found = false;
	ifstream fin;
	ofstream fout;
	AttendanceN* b; // student list in course
	AttendanceL* a = c;
	system("CLS");
	Seperater();
	Padding("EXPORT LIST OF STUDENT PRESENT IN COURSE");
	Seperater();
	cout << "Input course ID: ";
	cin.getline(courseid, 10);
	_strupr(courseid);
	cout << "Input year(yyyy-yyyy): ";
	cin.getline(year, 10);
	cout << "Input semester(1-3): ";
	cin.getline(semester, 2);
	while (a != NULL)
	{
		if (strcmp(a->courseid, courseid) == 0 && strcmp(a->year, year) == 0 && strcmp(a->semester, semester) == 0)
		{
			found = true;
			strcpy(s, "./Attendances/");
			strcat(s, courseid);
			strcat(s, "_");
			strcat(s, year);
			strcat(s, "_");
			strcat(s, semester);
			strcat(s, "_Present.csv");
			fout.open(s);
			b = a->student;
			while (b != NULL)
			{
				fout << b->studentid;
				for (int i = 0; i < 10; i++)
				{
					if (b->week[i] == 1)
						fout << "," << i+1;
				}
				fout << endl;
				b = b->next;
			}
		}	
		a = a->next;
	}
	if (found)
	{
		Seperater();
		Padding("DATA EXPORTED TO FILE");
		Padding(s);
		Seperater();
	}
	else
	{
		Seperater();
		Padding("COURSE DATA NOT FOUND");
		Seperater();
	}
	system("PAUSE");
}

void Absent(AttendanceL *&c){
	char courseid[10], year[10], semester[2], s[50];
	int k = 0;
	bool found = false;
	ifstream fin;
	ofstream fout;
	AttendanceN* b; // student list in course
	AttendanceL* a = c;
	system("CLS");
	Seperater();
	Padding("EXPORT LIST OF STUDENT ABSENT IN COURSE");
	Seperater();
	cout << "Input course ID: ";
	cin.getline(courseid, 10);
	_strupr(courseid);
	cout << "Input year(yyyy-yyyy): ";
	cin.getline(year, 10);
	cout << "Input semester(1-3): ";
	cin.getline(semester, 2);
	while (a != NULL)
	{
		if (strcmp(a->courseid,courseid) == 0 && strcmp(a->year,year) == 0 && strcmp(a->semester,semester) == 0)
		{
			found = true;
			strcpy(s, "./Attendances/");
			strcat(s, courseid);
			strcat(s, "_");
			strcat(s, year);
			strcat(s, "_");
			strcat(s, semester);
			strcat(s, "_Absent.csv");
			fout.open(s);
			b = a->student;
			while (b != NULL)
			{
				fout << b->studentid;
				for (int i = 0; i < 10; i++)
				{
					if (b->week[i] == 0)
						fout << "," << i+1;
				}
				fout << endl;
				b = b->next;
			}
		}
		a = a->next;
	}
	if (found)
	{
		Seperater();
		Padding("DATA EXPORTED TO FILE");
		Padding(s);
		Seperater();
	}
	else
	{
		Seperater();
		Padding("COURSE DATA NOT FOUND");
		Seperater();
	}
	system("PAUSE");
}

bool ViewAttendance(AttendanceL *a, int studentid)
{
	char courseid[30], semester[2], year[12];
	cout << "Input course ID: ";
	cin.getline(courseid, 10);
	cout << "Input year(yyyy-yyyy): ";
	cin.getline(year, 10);
	cout << "Input semester(1-3): ";
	cin.getline(semester, 2);
	AttendanceL* c = a;
	AttendanceN* n;
	while (c != NULL)
	{
		if (strcmp(c->courseid, courseid) == 0 && strcmp(c->year, year) == 0 && strcmp(c->semester,semester) == 0)
		{
			n = c->student;
			for (int i = 0; i < c->numberofstudents; i++)
			{
				if (atoi(n->studentid) == studentid)
				{
					Seperater();
					Padding(c->courseid);
					Padding(n->studentid);
					Seperater();
					for (int i = 0; i < 10; i++)
					{
						cout << "Week " << i + 1 << ": " << n->week[i] << endl;
					}
					return true;
				}
				n = n->next;
			}
		}
		c = c->next;
	}
	return false;
}

//---------------------------------------------------------------------------


