#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void AddSet() //create new set file (title.txt) and add title to set_list
{
    char file_name[50];
    char title[50];

    printf("Enter title (or type 'cancel' to go back): ");
    gets(title);

    sprintf(file_name,"%s.txt",title);

    FILE *fp = fopen(file_name,"w");
    FILE *master = fopen("set_list.txt","w");
    if(fp == NULL||master == NULL)
    {
        printf("<<Error open file>>");
        return 101;
    }

    fprintf(master,"%s\n",title);

    fclose(fp);
    fclose(master);
}
void SetList() //print all list
{
    char str[100];
    FILE *fp = fopen("set_list.txt","r");
    if(fp == NULL)
    {
        printf("<<Error open file>>");
        return 101;
    }
    while(fgets(str,100,fp)!= NULL)
    {
        printf("%s\n",str);
    }
    fclose(fp);
}
int main()
{
    AddSet();
    SetList();
    return 0;
}
