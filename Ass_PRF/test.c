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

typedef struct subject
{ 
    char id[10];
    char name[255];
} subject;


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
        return subjcnt;
    }
    else printf("Failed to open subjects.txt");
}


int main()
{ 
    subject subjarr[100];
    int k = getsubject(subjarr);
    for(int i = 0; i< k; i++)
    {
        printf("%s\t%s\n",subjarr[i].id,subjarr[i]. name);
    }
    return 0;
}