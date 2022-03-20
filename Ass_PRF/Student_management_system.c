#include "man.h"

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

typedef struct subject
{ 
    char id[10];
    char name[255];
} subject;

void clear_buffer (void);

long long getInt(char msg[], long long min, long long max);

void getString(char msg[], char arr[], int size);

void addNewSubject(void);

void addNewStudent(void);

void printstudent(char stuid[], char stuName[], int age);

int getmarks(mark markarr[]);

void writeNewSubjectToMark(char newID[]);

void addMark(void);

void printNewStudentMark(char id[], subject subjarr[], int subjcnt);

int getstudents(student stuarr[]);

int getsubject(subject subjarr[]);

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

int getsubject(subject subjarr[])
{
    FILE *Psubj = NULL;
    Psubj = fopen("subjects.txt", "r");
    if (Psubj != NULL)
    { 
        int subjcnt = 0;
        char data[100][255];
        do                                             // Get data sring
        {
            fgets(data[subjcnt], 255, Psubj);    
            data[subjcnt][strcspn(data[subjcnt], "\n")] = '\0';
            subjcnt++;
        } while (!feof(Psubj));
        
        for(int i = 0; i < subjcnt; i++)
        {
            int index;
            int tempind;
            index = strcspn (data[i], ";");
            tempind = index;
            data[i][index] = '\0';
            strncpy(subjarr[i].id, data[i], index + 1);
            data[i][index] = ' ';
            index = strcspn (data[i], ";");
            data[i][index] = '\0';
            strncpy(subjarr[i].name, data[i] + (tempind + 1), index - tempind);
        }
        fclose(Psubj);
        return subjcnt;
    }
    else printf("Failed to open subjects.txt");
}

void writetosubject(char id[], char name[])
{
    FILE *Psubj = fopen("subjects.txt", "a+");
    if (Psubj != NULL)
    {
        fprintf(Psubj, "\n%s;", id);
        fprintf(Psubj, "%s", name);
    } 
    else puts("Failed to open the file subjects.txt to write");
    fclose(Psubj);
}

int getstudents(student stuarr[])
{
    FILE *Pstudent = NULL;
    Pstudent = fopen("students.txt", "r");        // Pointer to student file.
    if(Pstudent != NULL)
    { 
        int stucount = 0;
        char data[100][255];
        do                                             // Get data sring
        {
            fgets(data[stucount], 255, Pstudent);    
            data[stucount][strcspn(data[stucount], "\n")] = '\0';
            stucount++;
        } while (!feof(Pstudent));
        int index;
        int tempind;

        for (int i = 0; i< stucount; i++)            // 0 to the ammount of students
        {
            index = strcspn(data[i], ";");       // Take the index of first apparing ';'
            tempind = index;                     // AUX index to be the first index
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
        }
        fclose(Pstudent);
        return stucount;
    }
    else puts("Failed to open students.txt");
}

void printstudent(char stuid[], char stuName[], int age)
{ 
    FILE *Pstudent = fopen("students.txt", "a+");
    if (Pstudent == NULL) printf("Failed to open students.txt when printing\n");
    else
    {
        fprintf(Pstudent, "\n%s;", stuid);
        fprintf(Pstudent, "%s;", stuName);
        fprintf(Pstudent, "%d", age);  
    }
    fclose(Pstudent);
}

int getmarks(mark markarr[])
{
    FILE *Pmark = NULL;
    Pmark = fopen("marks.txt", "r");             // Pointer to mark file. 
    if (Pmark != NULL)
    { 
        char data[100][255];
        int markcnt = 0;
        do
        {
            fgets(data[markcnt], 255, Pmark);
            data[markcnt][strcspn(data[markcnt], "\n")] = '\0';
            markcnt++;
        }while (!feof(Pmark));
        for( int i = 0; i < markcnt; i++)
        {
            int index;
            int tempind;
            index = strcspn(data[i], ";");
            data[i][index] = '\0';
            strncpy( markarr[i].id, data[i], index + 1);
            data[i][index] = ' ';
            tempind = index;
            index = strcspn(data[i], ";");
            data[i][index] = '\0';
            strncpy (markarr[i].subj, data[i] + (tempind + 1), index - tempind);
            data[i][index] = ' ';
            char tempmark[10];
            int markind = 0;
            for( int j = index + 1; j < strlen(data[i]); j++) 
            {
                if(47 < data[i][j] && data[i][j] < 58 || data[i][j] == '.')
                {
                    tempmark[markind++] = data[i][j];
                }
                tempmark[markind] = '\0';
            }
            char *tempvoid;
            markarr[i].Mark = strtod(tempmark, &tempvoid);
        } 
        fclose(Pmark);
        return markcnt;
    }
    else puts("Failed to open marks.txt");
}

void writeNewSubjectToMark(char newID[])
{ 
    FILE *Pmark = fopen("marks.txt", "a+");
    if (Pmark != NULL)
    {
        student stuarr[100];
        int stucnt = getstudents(stuarr);

        for(int i = 0; i < stucnt; i++)
        { 
            //fprintf(Pmark, )
        }
    } else puts("Failed to open marks.txt to write");
    fclose(Pmark);
}

void writeNewStudentMark(char id[], subject subjarr[], int subjcnt)
{
    FILE *Pmark = fopen("marks.txt", "a+");
    if (Pmark == NULL) puts("Failed to open marks.txt for printing");
    else
    {
        for(int i = 0; i < subjcnt; i++)
        {
            fprintf(Pmark, "\n%s;", id);
            fprintf(Pmark, "%s;", subjarr[i].id);
            fprintf(Pmark, "%lf", 0);
        }
    }
    fclose(Pmark);
}
// Part 3, work in progress...
void addMark(void)
{
    FILE *Pmark = NULL;
    Pmark = fopen("marks.txt", "a+");             // Pointer to markt file.   
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
        int index;
        int tempind;

        for (int i = 0; i< stucount; i++)            // 0 to the ammount of students
        {
            index = strcspn(data[i], ";");       // Take the index of first apparing ';'
            tempind = index;                     // AUX index to be the first index
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
        char stuID[255];
        int status = 1;
        do
        { 
            getString("Enter student ID in the list: ",stuID, 10); 
            for (int i = 0; i < stucount; i++)
            {
                if(strcmp(stuarr[i].id, stuID) == 0) status = 0;
            }
        } while (status == 1);
        status = 1;
        
        int markcnt = 0;
        do
        {
            fgets(data[markcnt], 255, Pmark);
            data[markcnt][strcspn(data[markcnt], "\n")] = '\0';
            markcnt++;
        }while (!feof(Pmark));
        mark markarr[markcnt];
        for( int i = 0; i < markcnt; i++)
        {
            index = strcspn(data[i], ";");
            data[i][index] = '\0';
            strncpy( markarr[i].id, data[i], index + 1);
            data[i][index] = ' ';
            tempind = index;
            index = strcspn(data[i], ";");
            data[i][index] = '\0';
            strncpy (markarr[i].subj, data[i] + (tempind + 1), index - tempind);
            data[i][index] = ' ';
            char tempmark[10];
            int markind = 0;
            for( int j = index + 1; j < strlen(data[i]); j++) 
            {
                if(47 < data[i][j] && data[i][j] < 58 || data[i][j] == '.')
                {
                    tempmark[markind++] = data[i][j];
                }
                tempmark[markind] = '\0';
            }
            char *tempvoid;
            markarr[i].Mark = strtod(tempmark, &tempvoid);
        } 
        printf ("List marks of student %s\n",stuID);
        puts("Subject		Marks");
        for (int i = 0; i < markcnt; i++)
        {
            if(strcmp(stuID, markarr[i].id) == 0)
            { 
                printf("%s\t\t%.2lf\n",markarr[i].subj, markarr[i].Mark);
            }
        }

        char subjID[8];
        do
        {
            getString("Enter subject ID in the list: ", subjID, 8);

        } while (status == 1);
        
        

    }
}
// Part 1, work in progress...
void addNewSubject(void)
{
    // Print the file
    subject subjarr[100];
    int subjcnt = getsubject(subjarr);
    puts("List of subjects:");     
    puts("ID    \t\tName");
    for(int i = 0; i < subjcnt; i++)
    {
        printf("%s",subjarr[i].id);
        printf("\t\t%s\n", subjarr[i].name);
    }
    // Get data
    char subjID[8];
    getString("Enter subject ID (not empty): ", subjID, 8);
    char subjName[255];
    getString("Enter subject name (not empty): ", subjName, 255);
    // Write to file
    writetosubject(subjID, subjName);
}



// Completed (Part 2)
void addNewStudent(void)
{
    // Add new student to new student file start from here
    // Print file
    student stuarr[100];
    int stucnt = getstudents(stuarr);
    puts("ID		Name			Age");
    for (int i = 0; i < stucnt; i++)
    {
        printf("%s\t%s", stuarr[i].id, stuarr[i].name);
        int space = 32 - strlen(stuarr[i].name) - strlen(stuarr[i].id);
        for(int i = 0; i <  space; i++) printf(" ");
        printf("%d\n", stuarr[i].age);
    }
    // Get new data
    char stuid[10];
    getString("Enter student ID (not empty): ", stuid, 10);
    char stuName[255];
    getString("Enter student name (not empty): ", stuName, 255);
    int age = getInt("Enter age (not empty): ", 18, 25);
    // Write to file
    printstudent(stuid, stuName, age);
    // Reprint file
    stucnt = getstudents(stuarr);
    puts("ID		Name			Age");
    for (int i = 0; i < stucnt; i++)
    {
        printf("%s\t%s", stuarr[i].id, stuarr[i].name);
        int space = 32 - strlen(stuarr[i].name) - strlen(stuarr[i].id);
        for(int i = 0; i <  space; i++) printf(" ");
        printf("%d\n", stuarr[i].age);
    }
    // Finished adding new students 

    // Add new students's makes into marks start here
    subject subjarr[100];
    int subjcnt = getsubject(subjarr);
    writeNewStudentMark(stuid, subjarr, subjcnt);
}



// Int Validator
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
// Sting Validator
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