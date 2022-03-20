#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
    char id[10];
    char name[255];
    int age;
} student;

typedef struct mark
{ 
    char id[10];
    char subj[8];
    double Mark;
} mark;

void clear_buffer (void);

long long getInt(char msg[], long long min, long long max);

void getString(char msg[], char arr[], int size);

void addNewSubject(void);

void addNewStudent(void);

void addMark(void);


int main()
{ 
    //system("cls");
    puts("Assignment: SMS Application, Group 1");
    puts("MENU");
    puts("1. Add a new subject\n2. Add a new student\n3. Enter a subjectddd's marks for the given student\n4. Exit");
    int choice = getInt("Please enter 1, 2, 3, or 4: ",1,4);
    if(choice == 1) 
    {
            addNewSubject();
    }
    else if(choice == 2)
    {
            addNewStudent();
    }
    else if(choice == 3)
    {
            addMark();
    }
    else puts("exiting...");
    system ("pause");
    return 0;
}

void addMark(void)
{
    FILE *Pmark = NULL;
    Pmark = fopen("mark.txt", "a+");             // Pointer to markt file.   
    FILE *Pstudent = NULL;
    Pstudent = fopen("students.txt", "r");        // Pointer to student file.
    if (Pmark == NULL || Pstudent == NULL) puts("Failed to open mark.txt"); // If can't open file.
    else
    {
        puts("List of students:");
        puts("ID		Name");
        char data[100][255];
        int stucount = 0;

        do                                             // Get data sring
        {
            fgets(data[stucount], 255, Pstudent);    
            data[stucount][strcspn(data[stucount], "\n")] = '\0';
            stucount++;
        } while (!feof(Pstudent));

        student stuarr[stucount];                    // Student struct declare as student arr 

        for (int i = 0; i< stucount; i++)            // 0 to the ammount of students
        {
            int index = strcspn(data[i], ";");       // Take the index of first apparing ';'
            int tempind = index;                     // AUX index to be the first index
            data[i][index] = '\0';                   // Set ';' to \0 for strcpy
            strncpy(stuarr[i].id, data[i], index +1); // strcpy
            data[i][index] = ' ';                     // Set ';' to ' ' for for the second ';' check
            index = strcspn(data[i], ";");            // Second ';' check
            data[i][index] = '\0';                    // This might not needed but the code doesn't work without this
            strncpy(stuarr[i].name, data[i] + (tempind + 1), index - tempind);     // Copy from the fist index to the second index
            for (int j = 0; j <= index; j++) data[i][j] = 'a';                     // Set the sting to 'a' from 0 to the second index
            stuarr[i].age = 0;                        // Set age to 0 for caculation
            for (int j = 0; j < strlen(data[i]); j++)  if(47 < data[i][j] && data[i][j] < 58) // Caculate age from string
            {
                stuarr[i].age *= 10;       
                stuarr[i].age += (data[i][j] - '0');
            }
            printf("%s\t%s\n", stuarr[i].id, stuarr[i]. name);        // Print the data
        }
        printf("Enter student ID in the list: ");
        char stdID[255];
        int status = 1;
        do
        { 
            getString("Enter student ID in the list: ",stdID, 10); 
            for (int i = 1; i < stucount; i++)
            { 
                if(strcmp(stuarr[i].id, stdID) == 0) status = 0;
            }
        } while (status == 1);
        
    }
}

void addNewSubject(void)
{

    FILE *Psubject = fopen("subjects.txt","a+");          // Pointer to subject file.
    if (Psubject == NULL) puts("Failed to open student.txt");  // If can't open file.
    else 
    {
    /* 
D BI202
Database systems
    */
        puts("List of subjects:");     
        puts("ID    \t\tName");
        char c;      // Char for printing.
        do
        {
            for(int i=0;i<6;i++) printf("%c", fgetc(Psubject));    // Print 6 digits of subjects
            printf("\t\t");
            fgetc(Psubject);
            do
            {
                c = fgetc(Psubject);                               // Print the rest of the string
                if(c != EOF) printf("%c",c);
                else printf("\n");                                 // If c = EOF, It's a \n 
            } while (c != EOF && c != '\n');
        } while (!feof(Psubject));  // until end of file

        char id[8];        getString("Enter subject ID (not empty): ",id, 8);      // GetID
        char sjname[256];  getString("Enter subject name (not empty): ", sjname, 256); // Get Subject name

        fprintf(Psubject,"\n%s;", id);                  // append new line and id and ;
        fprintf(Psubject,"%s", sjname);                 // append jubject name

        rewind(Psubject);                               // Read from the beginning of the file

        do
        {
            for(int i=0;i<6;i++) printf("%c", fgetc(Psubject));              // Same as the previos print
            printf("\t\t");
            fgetc(Psubject);
            do
            {
                c = fgetc(Psubject);
                if(c != EOF) printf("%c",c);
                else printf("\n");
            } while (c != EOF && c != '\n');
        } while (!feof(Psubject));
    }
}

void addNewStudent(void)
{
    FILE *Pstudent;
    Pstudent = fopen("students.txt", "a+");        // Pointer to student file.
    if (Pstudent == NULL) puts("Failed to open mark.txt"); // If can't open file.
    else
    {
        puts("List of students:");
        puts("ID		Name			Age");
        char data[100][255];
        int stucount = 0;

        do                                             // Get data sring
        {
            fgets(data[stucount], 255, Pstudent);    
            data[stucount][strcspn(data[stucount], "\n")] = '\0';
            stucount++;
        } while (!feof(Pstudent));

        student stuarr[stucount];                    // Student struct declare as student arr 

        for (int i = 0; i< stucount; i++)            // 0 to the ammount of students
        {
            int index = strcspn(data[i], ";");       // Take the index of first apparing ';'
            int tempind = index;                     // AUX index to be the first index
            data[i][index] = '\0';                   // Set ';' to \0 for strcpy
            strncpy(stuarr[i].id, data[i], index +1); // strcpy
            data[i][index] = ' ';                     // Set ';' to ' ' for for the second ';' check
            index = strcspn(data[i], ";");            // Second ';' check
            data[i][index] = '\0';                    // This might not needed but the code doesn't work without this
            strncpy(stuarr[i].name, data[i] + (tempind + 1), index - tempind);     // Copy from the fist index to the second index
            for (int j = 0; j <= index; j++) data[i][j] = 'a';                     // Set the sting to 'a' from 0 to the second index
            stuarr[i].age = 0;                        // Set age to 0 for caculation
            for (int j = 0; j < strlen(data[i]); j++)  if(47 < data[i][j] && data[i][j] < 58) // Caculate age from string
            {
                stuarr[i].age *= 10;       
                stuarr[i].age += (data[i][j] - '0');
            }
            printf("%s\t%s", stuarr[i].id, stuarr[i].name);        // Print the data
            int space = 32 - strlen(stuarr[i].name) - strlen(stuarr[i].id);
            for(int i = 0; i <  space; i++) printf(" ");
            printf("%d\n", stuarr[i].age);
        }
        char stuid[10];
        getString("Enter student ID (not empty): ", stuid, 10);
        char stuName[255];
        getString("Enter student name (not empty): ", stuName, 255);
        int age = getInt("Enter age (not empty): ", 18, 25);

        fprintf(Pstudent, "\n%s;", stuid);
        fprintf(Pstudent, "%s;", stuName);
        fprintf(Pstudent, "%d", age);

        rewind(Pstudent);
        stucount = 0;

        do                                             // Get data sring
        {
            fgets(data[stucount], 255, Pstudent);    
            data[stucount][strcspn(data[stucount], "\n")] = '\0';
            stucount++;
        } while (!feof(Pstudent));

        for (int i = 0; i< stucount; i++)            // 0 to the ammount of students
        {
            int index = strcspn(data[i], ";");       // Take the index of first apparing ';'
            int tempind = index;                     // AUX index to be the first index
            data[i][index] = '\0';                   // Set ';' to \0 for strcpy
            strncpy(stuarr[i].id, data[i], index +1); // strcpy
            data[i][index] = ' ';                     // Set ';' to ' ' for for the second ';' check
            index = strcspn(data[i], ";");            // Second ';' check
            data[i][index] = '\0';                    // This might not needed but the code doesn't work without this
            strncpy(stuarr[i].name, data[i] + (tempind + 1), index - tempind);     // Copy from the fist index to the second index
            for (int j = 0; j <= index; j++) data[i][j] = 'a';                     // Set the sting to 'a' from 0 to the second index
            stuarr[i].age = 0;                        // Set age to 0 for caculation
            for (int j = 0; j < strlen(data[i]); j++)  if(47 < data[i][j] && data[i][j] < 58) // Caculate age from string
            {
                stuarr[i].age *= 10;       
                stuarr[i].age += (data[i][j] - '0');
            }
            printf("%s\t%s", stuarr[i].id, stuarr[i].name);        // Print the data
            int space = 32 - strlen(stuarr[i].name) - strlen(stuarr[i].id);
            for(int i = 0; i <  space; i++) printf(" ");
            printf("%d\n", stuarr[i].age);
        }
        
    }
}

long long getInt(char msg[], long long min, long long max) 
{
     char val[20];           //input value
     long long intval;
     int count,rc;      //int value and count value
     while(1)
     {
         printf("%s", msg);
         count = 0;
         rc = 0;
         fgets(val,20,stdin);

         if(val[0]!='\n')
         {
             if(0<=max&&0>=min) if(val[0]=='0' && val[1] == '\n') return 0;
             for(int i=0; i< 20; i++) 
             {
                 if(val[i]=='\n') 
                 {
                     rc = 1;
                     i=20;
                 }
             } 
             if(rc==0) 
             {

                 clear_buffer();
             }
             val[strcspn(val,"\n")] = '\0';
             
             if(val[count]=='0') 
             {

                 while(val[count]=='0')
                 {
                     count++;
                 }
             }             
             char *ovf;
             intval = strtoll(val,&ovf,10);
             
             if(intval<=0) count++;

             long long intvaldup = intval;
 
             while(intvaldup!=0)
             {
                 intvaldup/=10;
                 count++;
             }
             if(min<=intval&&intval<=max)
             {
                 return intval;
             }
         }
    }
}

 /* clear empties input buffer */ 
 void clear_buffer (void)
 {
     char c;
     while ((c = getchar()) != '\n'&&c != EOF);
 }

  void getString(char msg[], char arr[],int size)
 {
     while (1)
     {
        printf ("%s",msg);
        fgets (arr, size, stdin);
        int rc = 1;
        for(int i = 0; i < size; i++)
        {
            if(arr[i] == '\n') 
            {
                rc = 0;
                //printf("i: %d\n",i);
                arr[i]= '\0';
                i=size;
            }
        }
        if(rc !=0) 
        {
            clear_buffer();
        }
        else
        { 
            if(arr[0]!='\0') break;
        }
     }
 }
