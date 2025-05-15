#ifndef QUESTION_H
#define QUESTION_H

typedef struct question
{
    char question[500];
    char answers[4][50];
    int ans;
} QUESTION;

int Quiz(QUESTION question);
QUESTION* LoadQuiz(char file_name[100], int *questions_number);
void InitQuestions();


#endif