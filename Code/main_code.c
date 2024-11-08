#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <locale.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//printf(ANSI_COLOR_CYAN    "This text is CYAN!"    ANSI_COLOR_RESET "\n");

void createQuiz();//to create a quiz from predefined set of questions
void inputQuiz();//to create a quiz from the questions inputted by the instructor
void takeQuiz();//for the student to take the quiz
void ICQuiz(int);//for IC quiz
void IBQuiz(int);//for IB quiz
void IEQuiz(int);//for IE quiz
void MQuiz(int);//for Mathematics quiz
int main()//DONE
{
    //setlocale(LC_ALL, "en_US.UTF-8");//Set locale to UTF-8 to ensure correct handling of UTF-8 encoded files
    char position;
    printf("\n\n!!!!!!!!\tWELCOME TO THE AUTOMATIC QUIZ SYSTEM\t!!!!!!!!\n\n");
    printf("\nAre you a STUDENT or INSTRUCTOR, enter your position:\nS for student\nI for instructor\n");
    scanf("%c",&position);
    if(tolower(position)=='i')
    {
        char choice[3];
        printf("\nYou would like to create the QUIZ, USER-INPUTED OR PRE-DEFINED:\nEnter your choice\nUD for USER-DEFINED\nPD for PRE-DEFINED\n");
        scanf("%2s",choice);
        for(int i=0;i<strlen(choice);i++)//converting all letters of choice into lowercase
            choice[i]=tolower(choice[i]);
        if(strcmp(choice,"ud")==0)
            inputQuiz();
        else if (strcmp(choice,"pd")==0)
            createQuiz();
        else
            printf("Invalid Output");
    }
    else if(tolower(position)=='s')
        takeQuiz();
    else
        printf("Invalid Output");
    return 0;
}
void takeQuiz()
{
    FILE *quiz;
    quiz=fopen("Quiz.txt","r");
    if(fgetc(quiz)==EOF)
        printf("Contact Instructor\nNO QUIZ IS PRESENT");
    printf("Enter the number of students taking the Quiz: ");
    int n;
    scanf("%d",&n);







    /*char old_name[] = "geeks.txt";
 
    // Any string
    char new_name[] = "geeksforgeeks.txt";
    int value;
 
    // File name is changed here
    value = rename(old_name, new_name);*/
    fclose(quiz);
    return ;
}
void inputQuiz()
{
    FILE *quiz;
    quiz=fopen("Quiz.txt","w");


    fclose(quiz);
    return ;
}
void createQuiz()//DONE
{
    char subject[2];
    printf("\nEnter the number of questions(not more than 25) you want in the QUIZ: ");
    int n;
    scanf("%d",&n);
    if(n>25 || n<1)
    {
        printf("Wrong Number of Questions");
        return ;
    }
    printf("\nEnter the Subject whose Quiz you want to be generated: \nIE for Electrical\nIC for Computer Science\nM for Mathematics\nIB for Biotechnology\n");
    scanf("%2s",subject);
    if (strcmp(subject,"IE")==0)
        IEQuiz(n);
    else if(strcmp(subject,"IC")==0)
        ICQuiz(n);
    else if(strcmp(subject,"IB")==0)
        IBQuiz(n);
    else if(strcmp(subject,"M")==0)
        MQuiz(n);
    else
        printf("Invalid Subject");
    return ;
}
void ICQuiz(int n)//DONE
{
    FILE *quiz,*ans;
    quiz=fopen("Quiz.txt","w");
    ans=fopen("Answers.txt","w");
    if (quiz == NULL || ans == NULL)//Checking if files opened successfully 
    {
        printf("Error opening quiz or answer file.\n");
        return ;
    }
    FILE *questions[25];
    for(int i=0;i<n;i++)//assigning file pointers for questions
    {
        char filename[20];
        snprintf(filename, sizeof(filename), "IC\\Q%d.txt", i + 1);  // Generate filename for Q1.txt to Q25.txt
        questions[i]=fopen(filename,"r");
        if (questions[i] == NULL)//Checking if files opened successfully
        {
            printf("Error opening question file %s\n", filename);
            return ;
        }
    }
    int q_no[n];//to store question numnber which get randomly selected
    srand(time(NULL));//Seed the random number generator
    for(int i=0;i<n;)//Storing random Question numbers out of 25 questions
    {
        int found=0;
        int random_number = rand() % 25 ;//generating random numbers between 0 and 24
        for(int j=0;j<i;j++)//Checking whether that q_no has not already being stored
        {
            if(q_no[j]==random_number)
            {
                found=1;
                break;
            }
        }
        if(!found)
            q_no[i++]=random_number;
    }
    for(int i=0;i<n;i++)//to store the questions into Quiz.txt
    {
        char ch;
        fprintf(quiz,"Q%d. ",i+1);
        //fprintf(quiz,"%d",q_no[i]);// used for decoding some error
        while ((ch=fgetc(questions[q_no[i]]))!='$')
        {
            fprintf(quiz,"%c",ch);
        }
        fprintf(quiz,"\n\n\n",0);
    }
    /*
    int q=q_no[0];
    char ch=fgetc(questions[q]);
    fprintf(quiz,"Q%d. ",1);
    fprintf(quiz,"%d",q_no[0]);// used for decoding some error
    while (ch!='$')
    {
        fprintf(quiz,"%c",ch);
        ch=fgetc(questions[q]);
    }*/
    for(int i=0;i<n;i++)//to store the answers into Answers.txt
    {
        char ch=fgetc(questions[q_no[i]]);
        fputc(ch,ans);
        fprintf(ans,"%d",i+1);
        while ((ch=fgetc(questions[q_no[i]]))!=EOF)
            fprintf(ans,"%c",ch);
        fputc('\n',ans);
    }
    for(int i=0;i<25;i++)//closing all file pointers for question
        fclose(questions[i]);
    fclose(quiz);
    fclose(ans);
    return ;
}
void IBQuiz(int n)
{
    FILE *quiz;
    quiz=fopen("Quiz.txt","w");
    FILE *questions[25];
    for(int i=0;i<n;i++)//assigning file pointers for questions
    {
        char filename[10];
        snprintf(filename, sizeof(filename), "IB\\Q%d.txt", i + 1);  // Generate filename for Q1.txt to Q25.txt
        questions[i]=fopen(filename,"r");
    }




    for(int i=0;i<n;i++)//closing all file pointers for question
        fclose(questions[i]);
    fclose(quiz);
    return ;
}
void IEQuiz(int n)
{
    FILE *quiz;
    quiz=fopen("Quiz.txt","w");
    FILE *questions[25];
    for(int i=0;i<n;i++)//assigning file pointers for questions
    {
        char filename[10];
        snprintf(filename, sizeof(filename), "IE\\Q%d.txt", i + 1);  // Generate filename for Q1.txt to Q25.txt
        questions[i]=fopen(filename,"r");
    }




    for(int i=0;i<n;i++)//closing all file pointers for question
        fclose(questions[i]);
    fclose(quiz);
    return ;
}
void MQuiz(int n)
{
    FILE *quiz;
    quiz=fopen("Quiz.txt","w");
    FILE *questions[25];
    for(int i=0;i<n;i++)//assigning file pointers for questions
    {
        char filename[10];
        snprintf(filename, sizeof(filename), "M\\Q%d.txt", i + 1);  // Generate filename for Q1.txt to Q25.txt
        questions[i]=fopen(filename,"r");
    }




    for(int i=0;i<n;i++)//closing all file pointers for question
        fclose(questions[i]);
    fclose(quiz);
    return ;
}
