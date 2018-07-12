#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#pragma once
#include"function.h"
#include "MenuHandler.h"

void initUserList(UserList &l)
{
    l.head=NULL;
}

void Import(UserList &l, ifstream &fin)
{
	Node* cur;
	int type;
	char username[50], fullname[100], email[50], password[100], clas[50], phone[15], none[10];
	while (!fin.fail())
	{
		fin >> type;
		if (fin.fail()) break;
		fin.get();
		fin.getline(username, 50, ',');
		fin.getline(fullname, 100, ',');
		fin.getline(email, 50, ',');
		fin.getline(phone, 15, ',');
		fin.getline(password, 100, ',');
		fin.getline(clas, 50);
		if (l.head == NULL)
		{
			l.head = new Node;
			l.head->data.Type = type;
			strcpy(l.head->data.UserName, username);
			strcpy(l.head->data.FullName, fullname);
			strcpy(l.head->data.Email, email);
			strcpy(l.head->data.Phone, phone);
			strcpy(l.head->data.Password, password);
			strcpy(l.head->data.Class, clas);
			l.head->next = NULL;
			cur = l.head;
		}
		else
		{
			cur->next = new Node;
			cur = cur->next;
			cur->data.Type = type;
			strcpy(cur->data.UserName, username);
			strcpy(cur->data.FullName, fullname);
			strcpy(cur->data.Email, email);
			strcpy(cur->data.Phone, phone);
			strcpy(cur->data.Password, password);
			strcpy(cur->data.Class, clas);
			cur->next = NULL;
		}
	}
}

void CreateAccount(UserList &l, UserList &l2, int choose,ClassList* &classlist)
{
    ofstream fout;
    fout.open("user_info.csv", ios::app);
	ifstream fin;
    int type, k = 0;
    char fullname[100], email[50], password[100], phone[12];
	char username[100];
    if(choose==2)
    {
        //fout<<endl;
        cout<<"Enter type: (enter 1 if a staff, enter 2 if a lecturer) : ";
        cin>>type;
        fout<<type<<",";
        cout<<"Enter the full name: ";
        cin.ignore();
        cin.getline(fullname, 100);
		char tmp;
        int m;
		if (fullname[0] >= 65 && fullname[0] <= 90)
		{
			tmp = char(int(fullname[0]) + 32);
			fout << char(int(fullname[0]) + 32);
			username[k] = tmp;
			k++;
		}
		else
		{
			fout << fullname[0];
			username[k] = fullname[0];
			k++;
		}
        for(int i=0; i<strlen(fullname);i++)
        {
            if(fullname[i]==32)
            {
                if(fullname[i+1]>=65 && fullname[i+1]<=90)
                    {
						tmp = char(int(fullname[i + 1]) + 32);
                        fout<<char(int(fullname[i+1])+32);
						username[k] = tmp;
						k++;
                    }
				else
				{
					fout << fullname[i + 1];
					username[k] = fullname[i + 1];
					k++;
				}
                m=i+2;
            }
        }
        for (int i = m; i < strlen(fullname); i++)
        {
            if(fullname[i]>=65 && fullname[i]<=90)
            {
				tmp = char(int(fullname[i]) + 32);
				username[k] = tmp;
				k++;
                fout<<char(int(fullname[i])+32);
            }
			else
			{
				fout << fullname[i];
				username[k] = fullname[i];
				k++;
			}
        }
		username[k] = '\0';
		fout << "," <<  fullname << ", ";

        cout<<"Enter email: "; cin.getline(email, 50);
        cout<<"Enter phone: "; cin.getline(phone, 12);
        cout<<"Enter password: "; cin.getline(password, 100);
		fout << email << ", " << phone << "," << password << ",";
		fout << "none" << endl;
        fout.close();
		fin.open("user_info.csv");
		initUserList(l);
		Import(l, fin);
		fin.close();
		Seperater();
		Padding("ACCOUNT CREATED:");
		Padding("USERNAME:");
		Padding(username);
		Padding("PASSWORD:");
		Padding(password);
		Seperater();
		system("PAUSE");
    }
    if (choose==1)
    {
		char classname[30];
		ifstream fin;
		cout << "Enter the class: ";
		fflush(stdin);
		cin.getline(classname, 10);
		strcat(classname, ".csv");

		fin.open(classname);
		if (!fin.is_open())
		{
			Seperater();
			Padding(classname);
			Padding("NOT FOUND IN FOLDER");
			Seperater();
			system("PAUSE");
		}
		else
		{
			initUserList(l2);
			Import(l2, fin);
			ImportStudent(l, l2, classlist);
			fin.close();
		}
    }
	
}

int login(UserList &l,User &tmp)
{
    char name[100], pass[100];
	Seperater();
    cout<<"Enter your user name: ";
    fflush(stdin);
    cin.getline(name, 100);
    cout<<"Enter your password: ";
    fflush(stdin);
    cin.getline(pass, 100);
	Seperater();
    if (l.head == NULL)
    {
		return -1;
    }
    else
    {
        Node* cur = l.head;
        while (cur != NULL)
        {
            if(strcmp(name, cur->data.UserName)==0 && strcmp(pass, cur->data.Password)==0)
            {
				tmp = cur->data;
				if (cur->data.Type == 1)
				{
					return 1;
				}
				else if (cur->data.Type == 2)
					return 2;
                else return 0;
            }
            else
                cur=cur->next;
        }
        return -1;
    }
}

void ImportStudent(UserList &l, UserList &l2,ClassList* &classlist)
{
	int mrk = 0,k =0,m=0;
	bool exist = false;
	Node* p2 = l2.head; //student list
	Node* tmp;
	char password[50],fullname2[100],tmpch;
	ClassList* classnode = classlist;
	while (classnode != NULL)
	{
		if (strcmp(classnode->name,p2->data.Class) == 0)
		{
			exist = true;
		}
		classnode = classnode->next;
	}
	if (!exist)
	{
		ClassList* newclass = new ClassList;
		strcpy(newclass->name, p2->data.Class);
		newclass->next = classlist;
		newclass->numberofstudents = 0;
		newclass->studentIDList = NULL;
		newclass->numberofstudents = 0;
		StudentIDList* tmpS;

		while (p2 != NULL)
		{
			tmpS = new StudentIDList;
			tmpS->studentid = atoi(p2->data.UserName);
			tmpS->next = newclass->studentIDList;
			newclass->studentIDList = tmpS;
			newclass->numberofstudents++;
			p2 = p2->next;
		}
		classlist = newclass;


		p2 = l2.head;
		while (p2 != NULL)
		{
			Node* p1 = l.head;//user list
			while (p1 != NULL)
			{
				if (p2->data.UserName == p1->data.UserName)
				{
					mrk = 1;
					break;
				}
				else
				{
					mrk = 0;
					p1 = p1->next;
				}
			}
			if (mrk == 0)
			{
				ofstream fout;
				fout.open("user_info.csv", ios::app);
				fout << p2->data.Type << ",";
				fout << p2->data.UserName << ",";
				fout << p2->data.FullName << ",";
				strcpy(fullname2, p2->data.FullName);
				fout << p2->data.Email << ",";
				fout << p2->data.Phone << ",";
				//GENERATE PASSWORD
				k = 0;
				if (fullname2[0] >= 65 && fullname2[0] <= 90)
				{
					tmpch = char(int(fullname2[0]) + 32);
					password[k] = tmpch;
					k++;
				}
				else
				{
					password[k] = fullname2[0];
					k++;
				}
				for (int i = 0; i < strlen(fullname2); i++)
				{
					if (fullname2[i] == 32)
					{
						if (fullname2[i + 1] >= 65 && fullname2[i + 1] <= 90)
						{
							tmpch = char(int(fullname2[i + 1]) + 32);
							password[k] = tmpch;
							k++;
						}
						else
						{
							password[k] = fullname2[i + 1];
							k++;
						}
						m = i + 2;
					}
				}
				for (int i = m; i < strlen(fullname2); i++)
				{
					if (fullname2[i] >= 65 && fullname2[i] <= 90)
					{
						tmpch = char(int(fullname2[i]) + 32);
						password[k] = tmpch;
						k++;
					}
					else
					{
						password[k] = fullname2[i];
						k++;
					}
				}
				password[k] = '\0';
				strcpy(p2->data.Password, password);
				//-----------------------------------
				fout << p2->data.Password << ",";
				fout << p2->data.Class << endl;
				fout.close();

				tmp = new Node;
				tmp->next = NULL;
				strcpy(tmp->data.UserName, p2->data.UserName);
				l.head = tmp;
			}
			p2 = p2->next;
		}
		initUserList(l);
		ifstream fin;
		fin.open("user_info.csv");
		Import(l, fin);
		fin.close();
		Seperater();
		Padding("IMPORT SUCCESSFUL");
		Seperater();
		system("PAUSE");
	}
	else
	{
		cout << "Class already existed" << endl;
		system("PAUSE");
	}
	
}

void LogInMenu(UserList &l, UserList &l2,ifstream &fin,ifstream &fin2,User &user)
{
	initUserList(l);
	initUserList(l2);

	fin.open("user_info.csv");
	Import(l, fin);
	fin.close();
	Padding("WELCOME TO THE PROGRAM");
	Padding("LOG IN");
	Padding("ALT+F4 TO EXIT");
	int choose;
	User tmp;
	int c = login(l,tmp);
	while (c == -1)
	{
		cout << "User not found" << endl;
		c = login(l, tmp);
	}
	user = tmp;
}

void ViewStudentClass(ClassList* classlist)
{
	char classname[30];
	bool exist = false;
	cout << "Input class name: ";
	cin.getline(classname, 30);
	ClassList* curClass = classlist;
	StudentIDList* s;
	while (curClass != NULL)
	{
		if (strcmp(curClass->name,classname) == 0)
		{
			exist = true;
			Seperater();
			Padding("STUDENTS IN CLASS");
			Padding(classname);
			Seperater();
			s = curClass->studentIDList;
			for (int i = 0; i < curClass->numberofstudents; i++)
			{
				cout << s->studentid << endl;
				s = s->next;
			}
		}

		curClass = curClass->next;
	}
	if (!exist)
	{
		Seperater();
		Padding("CLASS NOT FOUND");
		Seperater();
	}
	system("PAUSE");
}

void ViewStudentCourse(CourseList* courselist)
{
	char courseid[30],year[12],semester[2];
	bool exist = false;
	cout << "Input course ID: ";
	cin.getline(courseid, 30);
	cout << "Input year(yyyy-yyyy): ";
	cin.getline(year, 12);
	cout << "Input semester(1-3): ";
	cin.getline(semester, 2);
	CourseList* curC = courselist;
	StudentIDList* s;
	while (curC != NULL)
	{
		if (strcmp(curC->data.CourseCode,courseid) == 0 && strcmp(curC->data.Year,year) == 0 && curC->data.Semester == atoi(semester))
		{
			exist = true;
			Seperater();
			Padding("STUDENTS IN COURSE");
			Padding(courseid);
			Padding(year);
			Padding(semester);
			Seperater();
			s = curC->data.studenthead;
			for (int i = 0; i < curC->data.studentcount; i++)
			{
				cout << s->studentid << endl;
				s = s->next;
			}
		}

		curC = curC->pnext;
	}
	if (!exist)
	{
		Seperater();
		Padding("COURSE NOT FOUND");
		Seperater();
	}
	system("PAUSE");
}
