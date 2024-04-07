#pragma once
typedef struct course {
	char Name[5];
	int ID;
	int Section;
};
typedef struct student {
	char FirstName[100];
	char LastName[100];
	char SSN[15];
	int Number;
	course Courses[10];
	student* next;
}student,*StudentLink;

void ReadInputFile(const char* filename, StudentLink& head)
{
	void AddToList(StudentLink &addStudent, StudentLink & head);
	FILE* fp = fopen(filename, "rt");
	if (!fp)
	{
		printf("Error:can not open the file %s!", filename);
		return;
	}
	while (!feof(fp))
	{  
		StudentLink tmp=new student;
		fscanf(fp, "%s", &tmp->FirstName);
		if (strcmp(tmp->FirstName,"*****")==0)
		{
			break;
		}	
		fscanf(fp, "%s", &tmp->LastName);
		fscanf(fp, "%s", &tmp->SSN);
		fscanf(fp, "%d\n", &tmp->Number);
		for (int i = 0; i < tmp->Number; i++)
		{

			fgets(tmp->Courses[i].Name, 5, fp);
			fscanf(fp, "%d", &tmp->Courses[i].ID);
			fscanf(fp, "%d\n", &tmp->Courses[i].Section);
		}
		AddToList(tmp,head);
		delete tmp;
    }
	fclose(fp);
}

void AddToList(StudentLink&addStudent, StudentLink&head)
{
	StudentLink prev, p, L;
	p = new student;
	p->next = NULL;
	strcpy(p->FirstName, addStudent->FirstName);
	strcpy(p->LastName, addStudent->LastName);
	strcpy(p->SSN, addStudent->SSN);
	p->Number = addStudent->Number;
	for (int i = 0; i < p->Number; i++)
	{
		strcpy(p->Courses[i].Name, addStudent->Courses[i].Name);
		p->Courses[i].ID = addStudent->Courses[i].ID;
		p->Courses[i].Section = addStudent->Courses[i].Section;
	}
	if (head == NULL)
	{
		head = new student;
		head->next = p;
		return;
	}
	prev = head;
	L = head->next;
	while (L != NULL)
	{
		if (strcmp(p->LastName, L->LastName) < 0)
		{
			p->next = L;
			prev->next = p;
			return;
		}
		prev = prev->next;
		L = L->next;
	}
	if (L == NULL)
	{
		prev->next = p;
	}
}

void PrintToFile(const char* filename, StudentLink& head)
{
	FILE* fp = fopen(filename, "wt");
	if (!fp)
	{
		printf("Error:can not open the file %s", filename);
		return;
	}
	StudentLink p = head->next;
	while (p!=NULL)
	{	
		fprintf(fp, "SSN: %s\n",p->SSN);
		fprintf(fp, "NAME: %s, %s\n", p->LastName, p->FirstName);
		fprintf(fp, "Registered For %d Classes\n", p->Number);
		for (int i = 0; i < p->Number; i++)
		{
			fprintf(fp, "  - "); fputs(p->Courses[i].Name, fp); 
			fprintf(fp, "%04d-%04d\n", p->Courses[i].ID,p->Courses[i].Section); 
		}
		fprintf(fp, "\n");
		p = p->next;
	}
	fclose(fp);
}

void ProcessDeleteFile(const char* filename, StudentLink& head)
{
	char SSN[15];
	FILE* fp = fopen(filename, "rt");
	if (!fp)
	{
		printf("Error:can not open the file %s", filename);
		return;
	}	
	StudentLink prev = head;
	StudentLink p = prev->next;
	while (!feof(fp))
	{
		fscanf(fp, "%s", SSN);
		if (strcmp(SSN, "*****") == 0)
		{
			break;
		}
		while (p != NULL)
		{
			if (strcmp(p->SSN, SSN) == 0)
			{
				prev->next = p->next;
				delete p;
				prev = head;
				p = prev->next;
				break;
			}
			prev = prev->next;
			p = p->next;
		}
	}
}

void DeleteList(StudentLink& head)
{
	StudentLink L = head;
	StudentLink p = L->next;
	while (!p)
	{
		L = p->next;
		delete p;
		p = L;
	}
}