#include <stdio.h>
#include <stdlib.h>

typedef struct question
{
	char question[500];
	char answers[4][50];
	int ans;
}QUESTION;

void initQuestions(){
	FILE* fisier = fopen("test.bin", "wb");
	QUESTION q[4] = { {
		.ans = 0,
		.answers[0] = "da",
		.answers[1] = "bine",
		.answers[2] = "ok",
		.answers[3] = "alr",
		.question = "0"
	}, {
		.ans = 2,
		.answers[0] = "da",
		.answers[1] = "bine",
		.answers[2] = "ok",
		.answers[3] = "alr",
		.question = "2"

	}, {
		.ans = 3,
		.answers[0] = "da",
		.answers[1] = "bine",
		.answers[2] = "ok",
		.answers[3] = "alr",
		.question = "3"

	}, {
		.ans = 1,
		.answers[0] = "da",
		.answers[1] = "bine",
		.answers[2] = "ok",
		.answers[3] = "alr",
		.question = "1"

	}};

	fwrite(q, sizeof(QUESTION), 4, fisier);

	fclose(fisier);
}

int LoadQuiz(QUESTION** questions, char file_name[100])
{
	FILE* QuizFile;
	if ((QuizFile = fopen(file_name, "rb")) == NULL) {
		printf("\n <!!!> Nu poate fi deschis fisierul  %s\n", file_name);
		return 1;
	}

	fseek(QuizFile, 0, SEEK_END);
	int questions_number = ftell(QuizFile) / sizeof(QUESTION);
	fseek(QuizFile, 0, SEEK_SET);

	questions = (QUESTION**)malloc(sizeof(QUESTION*) * questions_number);

	if (fread(questions, sizeof(QUESTION), questions_number, QuizFile) == 0) printf("Nu a putut fi citit\n");

	fclose(QuizFile);

	int scor = 0, asteapta = 0;

	printf("numar intrebari %d\n", questions_number);

	for (int i = 0; i < questions_number && asteapta; ++i) {
		printf("%d \n", questions[i]->ans);


		int test = Quiz(questions[i], i, questions_number);
		scor += test;
	}

	return questions_number;
}


int main() {
	FILE* fisier = fopen("test.bin", "wb");
	QUESTION q[4] = { {
		.ans = 0,
		.answers[0] = "da",
		.answers[1] = "bine",
		.answers[2] = "ok",
		.answers[3] = "alr",
		.question = "0"
	}, {
		.ans = 2,
		.answers[0] = "da",
		.answers[1] = "bine",
		.answers[2] = "ok",
		.answers[3] = "alr",
		.question = "2"

	}, {
		.ans = 3,
		.answers[0] = "da",
		.answers[1] = "bine",
		.answers[2] = "ok",
		.answers[3] = "alr",
		.question = "3"

	}, {
		.ans = 1,
		.answers[0] = "da",
		.answers[1] = "bine",
		.answers[2] = "ok",
		.answers[3] = "alr",
		.question = "1"

	}
	
	};

	fwrite(q, sizeof(QUESTION), 4, fisier);

	fclose(fisier);
	return 0;
}