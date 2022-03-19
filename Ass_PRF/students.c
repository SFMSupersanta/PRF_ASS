#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *input_student_file;
FILE *input_subjects_file;
FILE *input_marks_file;

struct Student_Info
{
   char  ID[10];
   char  name[50];
   int   age;
   
};

void open_file_students()
{
    
    input_student_file = fopen("students.txt", "a+");
    if(input_student_file == NULL)
        {
            printf ("unable to open file");
        }
}

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
            if(arr[0]=='\n')printf("");
            else break;
        }
     }
}

long long getInt(char msg[], long long min, long long max) 
{
     char val[20];
     long long intval;
     int count,rc;
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
             if (val[count] != '\0')  printf("");
             else if(min<=intval&&intval<=max)
             {
                 return intval;
             }else printf("");
         } else printf("");
     }
 }

void getStudent()
{   
    open_file_students();
    char name[256], ID[10];
    getString("Enter student ID (not empty) : ", ID, 10);
    getString("Enter student name (not empty) : ", name, 256);
    struct Student_Info student1;
    strcpy(student1.ID, ID);
    strcpy(student1.name, name);
    student1.age = getInt("Enter age (18 - 25) : ", 18, 25);
    fprintf(input_student_file, "\n%s", student1.ID);
    fprintf(input_student_file, ";%s", student1.name);
    fprintf(input_student_file, ";%d", student1.age);
    fclose(input_student_file);
}

void cat_students()
{
    open_file_students();
    char list;
    printf ("\n********** List of students **********\n");
    do
    {
        list = fgetc(input_student_file);
        if(list!=EOF) printf ("%c",list);
    }
    while(!feof(input_student_file));
    fclose (input_student_file);
}

int main()
{   
    getStudent();
    cat_students();
    return 0;
}