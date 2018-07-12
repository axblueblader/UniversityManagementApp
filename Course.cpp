#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Course.h"
#include "MenuHandler.h"

void initClassList(ClassList* &cl)
{
	cl->studentIDList = NULL;
}

void initCourse(Course* &c)
{
	c->studentcount = 0;
	c->studenthead = NULL;
}

void initCourseList(CourseList* &cl)
{
	cl = NULL;
}

void outputCourseList(CourseList* cl)
{
	CourseList* p;
	p = cl;
	ofstream file;
	file.open("courselist.csv", ios::trunc);
	while (p != NULL)
	{
		file << p->data.CourseCode << "," << p->data.Year << "," << p->data.Semester << endl;
		p = p->pnext;
	}
	file.close();
}

// ADD TO LAST LIST
void addCourseList(CourseList* &cl, char code[], char year[], int sem)
{

		CourseList* q = new CourseList;
		strcpy(q->data.CourseCode, code);
		strcpy(q->data.Year, year);
		q->data.Semester = sem;
		q->pnext = cl;
		cl = q;
}

void addIDtoCourse(Course* &c, int studentid)
{
	bool exist = false;
	StudentIDList* q = c->studenthead;
	while (q !=NULL)
	{
		if (q->studentid == studentid)
		{
			exist = true;
		}
		q = q->next;
	}
	if (!exist)
	{
		StudentIDList* p = new StudentIDList;
		p->studentid = studentid;
		p->next = c->studenthead;
		c->studenthead = p;
		c->studentcount++;
	}
}

void howtoAdd(Course* &c,ClassList* &cl)
{
	int choice = -1, n,count;
	char class_name[20],tmp[10],s[30],buffer[20];
	bool exist;
	ClassList* p, *newclass;
	StudentIDList* q, *newstudent;
	ifstream file;
	cout << "ADD STUDENTS TO COURSE" << endl;
	Seperater();
	Padding("1.Choose an existing class");
	Padding("2.Add new class name");
	Padding("3.Add an existing student");
	Padding("0.Done");
	while (choice)
	{
		Seperater();
		cout << "Choice: ";
		cin >> choice; cin.get();
		switch (choice)
		{
		case 1:
			cout << "Input class name: ";
			cin.getline(class_name, 20, '\n');
			exist = false;
			p = cl;
			while (p != NULL)
			{
				if (strcmp(p->name, class_name) == 0)
				{
					exist = true;
					break;
				}
				p = p->next;
			}
			if (exist)
			{
				q = p->studentIDList;
				while (q != NULL)
				{
					n = q->studentid;
					addIDtoCourse(c, n);
					q = q->next;
				}
				Seperater();
				Padding("CLASS ADDED");
			}
			else
			{
				cout << "Class doesn't exist" << endl;
			}
			break;
		case 2:
			newclass = new ClassList;
			Padding("READ IDs FROM FILE [CLASSNAME]_list.csv");
			Seperater();
			cout << "Input new class name: ";
			cin.getline(class_name, 20, '\n');
			cout << "Input number of students: ";
			cin.getline(tmp, 4);		
			strcpy(s, class_name); strcat(s, "_list.csv");
			newclass->numberofstudents = atoi(tmp);
			newclass->studentIDList = NULL;
			strcpy(newclass->name, class_name);
			file.open(s);
			if (file.is_open())
			{
				for (int i = 0; i < newclass->numberofstudents - 1; i++)
				{

					file.getline(buffer, 10, ',');
					newstudent = new StudentIDList;
					newstudent->studentid = atoi(buffer);
					newstudent->next = newclass->studentIDList;
					newclass->studentIDList = newstudent;
				}
				file.getline(buffer, 10);
				newstudent = new StudentIDList;
				newstudent->studentid = atoi(buffer);
				newstudent->next = newclass->studentIDList;
				newclass->studentIDList = newstudent;
				newclass->next = cl;
				cl = newclass;
				file.close();
				q = cl->studentIDList;
				while (q != NULL)
				{
					n = q->studentid;
					addIDtoCourse(c, n);
					q = q->next;
				}
				Seperater();
				Padding("LIST IMPORTED");
			}
			else
			{
				Padding("CLASS ALREADY CREATED");
			}
			break;
		case 3:
			cout << "Enter student ID: ";
			cin >> n; cin.get();
			p = cl;
			exist = false;
			while (p != NULL)
			{
				q = p->studentIDList;
				while (q != NULL)
				{
					if (q->studentid == n)
					{
						addIDtoCourse(c, n);
						exist = true;
					}
					q = q->next;
				}
				p = p->next;
			}
			if (exist)
			{
				cout << "Student has been added" << endl;
			}
			else
			{
				cout << "Student not found" << endl;
			}
			break;
		case 0:
			cout << "Going back" << endl;
		}
	}
}

void addCourse(Course* &c, ClassList* &clsl,ofstream &file,int choice)
{
	char s[100];
	int n;	
	cout << "Enter course name: ";
	cin.getline(s, 100, '\n');
	strcpy(c->CourseName, s);
	//file << s << ",";
	fflush(stdin);
	cout << "Enter lecturer name: ";
	cin.getline(s, 100, '\n');
	strcpy(c->LecturerName, s);
	//file << s << ",";
	fflush(stdin);
	cout << "Enter start day (dd/mm/yyyy): ";
	cin.getline(s, 100, '\n');
	strcpy(c->StartDate, s);
	//file << s << ",";
	fflush(stdin);
	cout << "Enter end day (dd/mm/yyyy): ";
	cin.getline(s, 100, '\n');
	strcpy(c->EndDate, s);
	//file << s << ",";
	fflush(stdin);
	cout << "Enter start time (hh:mm): ";
	cin.getline(s, 100, '\n');
	strcpy(c->FromTime, s);
	//file << s << ",";
	fflush(stdin);
	cout << "Enter end time (hh:mm): ";
	cin.getline(s, 100, '\n');
	strcpy(c->ToTime, s);
	//file << s << ",";
	cout << "Enter day of week (1:Monday,2:Tuesday,...,6:Saturday) : ";
	cin.getline(s, 2);
	n = atoi(s); // 0 to check
	while (n < 1 || n > 6)
	{
		cout << "Invalid input, please reenter(1-6)" << endl;
		cin.getline(s, 2);
		n = atoi(s);
	}
	c->DateOfWeek = n;
	//file << n << ",";
	if (choice == -1)
	{
		Seperater();
		howtoAdd(c, clsl);
		Seperater();
	}
	file << c->CourseCode << ",";
	file << c->Year << ",";
	file << c->Semester << ",";
	file << c->CourseName << ",";
	file << c->LecturerName << ",";
	file << c->StartDate << ",";
	file << c->EndDate << ",";
	file << c->FromTime << ",";
	file << c->ToTime << ",";
	file << c->DateOfWeek << ",";
	file << c->studentcount << endl;
	StudentIDList *tmpS = c->studenthead;
	for (int i = 0; i < c->studentcount - 1; i++)
	{
		file << tmpS->studentid << ",";
		tmpS = tmpS->next;
	}
	file << tmpS->studentid << endl;

	
	
	cout << "Changes have been saved" << endl;
	system("PAUSE");
}


void importCoursefromfile(CourseList* &cl , ClassList* &clsl);
int importCourse(CourseList* &cl, ClassList* &clsl)
{
//	char code[50], year[50], 
	char title[50], s[50], sem[2];
	int n, choice, semester,count=0;
	ifstream file;
	Course* c;
	CourseList* cur;
	c = new Course;
	initCourse(c);
	cout << "Enter number of courses you want to add: ";
	cin >> n; cin.get();
	for (int i = 0; i<n; i++)
	{
		system("CLS");
		fflush(stdin);
		cout << "Enter course code: ";
		cin.getline(c->CourseCode, 10, '\n');
		fflush(stdin);
		cout << "Enter year(yyyy-yyyy): ";
		cin.getline(c->Year, 10, '\n');
		cout << "Enter semester (1-3): ";
		fflush(stdin);
		cin.getline(sem, 2);
		while (atoi(sem) == 0)
		{
			cout << "Invalid input, please reenter(1-3): " << endl;
			cin.getline(sem, 2);
		}
		c->Semester = atoi(sem);
		strcpy(s, "./Courses/");
		strcat(s, c->CourseCode);
		strcat(s, "_"); strcat(s, c->Year);
		_itoa(c->Semester, sem, 10);
		strcat(s, "_"); strcat(s, sem);
		strcat(s, ".csv");
		ifstream file;
		file.open(s);
		if (file.is_open())
		{
			cout << c->CourseCode << " already exists. Do you want to change its detail (0:No/1:Yes): ";
			cin >> choice; cin.get();
			if (choice == 1)
			{
				cur = cl;
				while (cur!= NULL)
				{
					if (strcmp(cur->data.CourseCode, c->CourseCode) == 0 && strcmp(cur->data.Year, c->Year) == 0 && cur->data.Semester == c->Semester)
					{
						*c = cur->data;
						break;
					}
					cur = cur->pnext;
				}
			}
		}
		else
		{
			choice = -1;
			//addCourseList(cl, c->CourseCode, c->Year, c->Semester);
			count++;
		}
		file.close();
		if (choice == -1 || choice == 1)
		{
			ofstream file;
			Seperater();
			Padding("MODIFYING COURSE:");
			strcpy(title, c->CourseCode);
			Padding(title);
			Padding(c->Year);
			Padding(sem);
			Seperater();
			file.open(s);
			addCourse(c, clsl, file,choice);	
			if (choice == 1)
			{
				cur->data = *c;
			}
			else
			{
				cur = new CourseList;
				cur->data = *c;
				cur->pnext = cl;
				cl = cur;
			}
			file.close();
		}
	}
	return count;
}

void importCoursefromfile(CourseList* &cl, ClassList* &clsl)
{
	char code[50], year[50];
	int semester,c,c2;
	bool exist;
	ifstream file;
	file.open("courselist.csv");
	CourseList* cur;
	
	while (!file.eof())
	{
		file.getline(code, sizeof(code), ',');
		if (strcmp(code, "") == 0 || strcmp(code,"\n")==0) break;
		file.getline(year, sizeof(year), ',');
		file >> semester; file.get();
		cur = cl;
		exist = false;
		while (cur != NULL )
		{
			if (strcmp(code,cur->data.CourseCode) == 0 && strcmp(year,cur->data.Year) == 0 && cur->data.Semester == semester)
			{
				//addCourseList(cl, code, year, semester);
				exist = true;
			}
			cur = cur->pnext;
		}
		if (!exist)
		{
			addCourseList(cl, code, year, semester);
		}
	}
	file.close();
	CourseList* p;
	StudentIDList *tmpS;
	p = cl;
	char s[100], sem[2],buffer[10];
	while (p != NULL)
	{
		strcpy(s, "./Courses/");
		strcat(s, p->data.CourseCode);
		strcat(s, "_"); strcat(s, p->data.Year);
		_itoa(p->data.Semester, sem, 10);
		strcat(s, "_"); strcat(s, sem);
		strcat(s, ".csv");
		file.open(s);
		if (file.is_open())
		{
			file.getline(buffer, 10, ',');
			file.getline(buffer, 10, ',');
			file.getline(buffer, 10, ',');
			file.getline(p->data.CourseName, 50, ',');
			file.getline(p->data.LecturerName, 50, ',');
			file.getline(p->data.StartDate, 12, ',');
			file.getline(p->data.EndDate, 12, ',');
			file.getline(p->data.FromTime, 10, ',');
			file.getline(p->data.ToTime, 10, ',');
			file.getline(buffer, 10, ',');
			p->data.DateOfWeek = atoi(buffer);
			file.getline(buffer, 10);
			p->data.studentcount = atoi(buffer);
			p->data.studenthead = NULL;
			for (int i = 0; i < p->data.studentcount-1; i++)
			{
				tmpS = new StudentIDList;
				file.getline(buffer, 10, ',');
				tmpS->studentid = atoi(buffer);
				tmpS->next = p->data.studenthead;
				p->data.studenthead = tmpS;
			}
			tmpS = new StudentIDList;
			file.getline(buffer, 10);
			tmpS->studentid = atoi(buffer);
			tmpS->next = p->data.studenthead;
			p->data.studenthead = tmpS;
			file.close();
		}
		p = p->pnext;
	}
}

void ExportCourse(CourseList* courselist)
{
	char s[100], sem[2];
	CourseList* c = courselist;
	StudentIDList* tmpS;
	ofstream file;
	while (c != NULL)
	{
		strcpy(s, "./Courses/");
		strcat(s, c->data.CourseCode);
		strcat(s, "_");
		strcat(s, c->data.Year);
		_itoa(c->data.Semester, sem, 10);
		strcat(s, "_");
		strcat(s, sem);
		strcat(s, ".csv");
		file.open(s);
		file << c->data.CourseCode << ",";
		file << c->data.Year << ",";
		file << c->data.Semester << ",";
		file << c->data.CourseName << ",";
		file << c->data.LecturerName << ",";
		file << c->data.StartDate << ",";
		file << c->data.EndDate << ",";
		file << c->data.FromTime << ",";
		file << c->data.ToTime << ",";
		file << c->data.DateOfWeek << ",";
		file << c->data.studentcount << endl;
		tmpS = c->data.studenthead;
		for (int i = 0; i < c->data.studentcount-1; i++)
		{
			file << tmpS->studentid << ",";
			tmpS = tmpS->next;
		}
		file << tmpS->studentid << endl;
		file.close();
		c = c->pnext;
	}
}

void outputCourse(CourseList* cl)
{
	CourseList* p;
	p = cl;
	cout << "COURSE LIST" << endl;
	Seperater();
	while (p != NULL)
	{
		cout << "Course code: " << p->data.CourseCode << endl;
		cout << "Year: " << p->data.Year << endl;
		cout << "Semester: " << p->data.Semester << endl;
		cout << "Course name: " << p->data.CourseName << endl;
		cout << "Lecturer name: " << p->data.LecturerName << endl;
		cout << "Start day: " << p->data.StartDate << endl;
		cout << "End day: " << p->data.EndDate << endl;
		cout << "Start time: " << p->data.FromTime << endl;
		cout << "End time: " << p->data.ToTime << endl;
		cout << "Date of week: " << p->data.DateOfWeek << endl;
		Seperater();
		p = p->pnext;
	}
	system("PAUSE");
}

void Schedule(ScheduleList &a, CourseList* &courselist){

	ifstream filecourse;
	ifstream fileschedule;
	ofstream outputfilecourse;
	fileschedule.open("schedule.txt");
	int n;
	char sem[2], dow[2], tmp[2];
	//	Course b;
	ScheduleNode* c;
	//--------------------------------------------------------
	fileschedule.getline(tmp, 2);
	n = atoi(tmp);
	for (int i = 0; i < n; i++){
		c = new ScheduleNode;
		fileschedule.getline(c->CourseCode, 10);
		fileschedule.getline(c->Year, 10);
		fileschedule.getline(sem, 2);
		c->Semester = atoi(sem);
		fileschedule.getline(c->StartDate, 12);
		fileschedule.getline(c->EndDate, 12);
		fileschedule.getline(c->FromTime, 10);
		fileschedule.getline(c->ToTime, 10);
		fileschedule.getline(dow, 2);
		c->Dateofweek = atoi(dow);
		c->next = NULL;
		a.head = c;
	}
	c = a.head;
	CourseList* clc = courselist;
	while (c != NULL){
		while (clc != NULL){
			if (!strcmp(c->CourseCode, clc->data.CourseCode) && !strcmp(c->Year, clc->data.Year) && c->Semester == clc->data.Semester)
			{
				strcpy(clc->data.StartDate, c->StartDate);
				strcpy(clc->data.EndDate, c->EndDate);
				strcpy(clc->data.FromTime, c->FromTime);
				strcpy(clc->data.ToTime, c->ToTime);
				clc->data.DateOfWeek = c->Dateofweek;
				break;
			}
			clc = clc->pnext;
		}
		c = c->next;
	}
}

void ExportClassList(ClassList* &classlist)
{
	ofstream file;
	ClassList* cur = classlist;
	StudentIDList* curS;
	file.open("classlist.csv");
	while (cur!=NULL)
	{
		file << cur->name << "," << cur->numberofstudents << endl;
		curS = cur->studentIDList;
		for (int i = 0; i < cur->numberofstudents-1; i++)
		{
			file << curS->studentid << ",";
			curS = curS->next;
		}
		file << curS->studentid << endl;
		cur = cur->next;
	}
	file.close();
}

void ImportClassList(ClassList* &classlist)
{
	ifstream file;
	ClassList* tmpC;
	StudentIDList* curS;
	classlist = NULL;
	char buffer[30];
	file.open("classlist.csv");
	while (!file.eof())
	{
		file.getline(buffer, 10, ',');
		if (strcmp(buffer,"") == 0||strcmp(buffer,"\n") == 0)
		{
			break;
		}
		tmpC = new ClassList;
		strcpy(tmpC->name, buffer);
		file.getline(buffer, 10);
		tmpC->numberofstudents = atoi(buffer);
		tmpC->studentIDList = NULL;
		for (int i = 0; i < tmpC->numberofstudents-1; i++)
		{
			curS = new StudentIDList;
			file.getline(buffer, 10, ',');
			curS->studentid = atoi(buffer);
			curS->next = tmpC->studentIDList;
			tmpC->studentIDList = curS;
		}
		curS = new StudentIDList;
		file.getline(buffer, 10);
		curS->studentid = atoi(buffer);
		curS->next = tmpC->studentIDList;
		tmpC->studentIDList = curS;
		tmpC->next = classlist;
		classlist = tmpC;
	}
	file.close();
}