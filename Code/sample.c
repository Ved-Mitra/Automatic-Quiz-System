#include<stdio.h>
int main()
{
    FILE *ptr,*quiz;
    quiz=fopen("Quiz.txt","w");
    ptr=fopen("IC\\Q9.txt","r");
    char ch;
    while((ch=fgetc(ptr))!=EOF)
    {
        fputc(ch,quiz);
    }
    fclose(ptr);
    fclose(quiz);
}