#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

}

void addNewSubject(void)
{
    //FILE *Pstudent = fopen("students.txt","r+");
    FILE *Psubject = fopen("subjects.txt","a+");          // Pointer to subject file.
    if (Psubject == NULL) puts("Failed to open student.txt");  // If can't open file.
    else 
    {
/* 
DBI202
Database systems
*/
        puts("List of subjects:");
        puts("ID    \t\tName");
        char c;
        do
        {
            for(int i=0;i<6;i++) printf("%c", fgetc(Psubject));
            printf("\t\t");
            fgetc(Psubject);
            do
            {
                c = fgetc(Psubject);
                if(c != EOF) printf("%c",c);
                else printf("\n");
            } while (c != EOF && c != '\n');
        } while (!feof(Psubject));

        char id[8];        getString("Enter subject ID (not empty): ",id, 8);
        char sjname[256];  getString("Enter subject name (not empty): ", sjname, 256);

        fprintf(Psubject,"\n%s;", id);
        fprintf(Psubject,"%s", sjname); 

        rewind(Psubject);

        do
        {
            for(int i=0;i<6;i++) printf("%c", fgetc(Psubject));
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
