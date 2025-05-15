#include <stdio.h>
#include "question.h"
#include <stdlib.h>
#include "game.h"
#include "raylib.h"

int Quiz(QUESTION question) {

	int originX = GetRenderWidth() / 10;
	int originY = GetRenderHeight() / 25;
	int width = GetRenderWidth() / 5 * 4;
	int height = GetRenderHeight() / 5 * 4;

	DrawTextBox((Rectangle) {
		.x = originX,
		.y = originY,
		.width = width,
		.height = height,
	}, question.question);
	Button raspuns_1 = MakeButton((Rectangle) { .x = originX + 20, originY + 100, width - 40, 100 }, 0.3, question.answers[0], 30);
	Button raspuns_2 = MakeButton((Rectangle) { .x = originX + 20, originY + 220, width - 40, 100 }, 0.3, question.answers[1], 30);
	Button raspuns_3 = MakeButton((Rectangle) { .x = originX + 20, originY + 340, width - 40, 100 }, 0.3, question.answers[2], 30);
	Button raspuns_4 = MakeButton((Rectangle) { .x = originX + 20, originY + 460, width - 40, 100 }, 0.3, question.answers[3], 30);

	if (ButtonClicked(raspuns_1)) {
		if (question.ans == 0) {
			return 1; //raspuns corect
		}
		else {
			return 2; //raspuns gresit
		}
	}
	if (ButtonClicked(raspuns_2)) {
		if (question.ans == 1) {
			return 1; //raspuns corect
		}
		else {
			return 2; //raspuns gresit
		}
	}
	if (ButtonClicked(raspuns_3)) {
		if (question.ans == 2) {
			return 1; //raspuns corect
		}
		else {
			return 2; //raspuns gresit
		}
	}
	if (ButtonClicked(raspuns_4)) {
		if (question.ans == 3) {
			return 1; //raspuns corect
		}
		else {
			return 2; //raspuns gresit
		}
	}
	DrawButton(raspuns_1);
	DrawButton(raspuns_2);
	DrawButton(raspuns_3);
	DrawButton(raspuns_4);

	return 0; // daca nu raspunde in acel frame
}

QUESTION* LoadQuiz(char file_name[100], int *questions_number)
{
	FILE* quizFile;
	if ((quizFile = fopen(file_name, "rb")) == NULL) {
		printf("\n <!!!> Nu poate fi deschis fisierul  %s\n", file_name);
		return -1;
	}

	fseek(quizFile, 0, SEEK_END);
	*questions_number = ftell(quizFile) / sizeof(QUESTION);
	fseek(quizFile, 0, SEEK_SET);

	QUESTION* questions = (QUESTION*)malloc(sizeof(QUESTION) * (*questions_number));

	if (fread(questions, sizeof(QUESTION), *questions_number, quizFile) == 0) 
		printf("<!!!> Nu a putut fi citit fisierul \"%s\" !!!>\n", file_name);

	fclose(quizFile);

	return questions;
}

void InitQuestions() {
	FILE* fisier = fopen("test.bin", "wb");
	QUESTION q[4] = { {
		.ans = 0,
		.answers[0] = "da",
		.answers[1] = "bine",
		.answers[2] = "ok",
		.answers[3] = "alr",
		.question = "cine este marcel ciolacu",
	}, {
		.ans = 2,
		.answers[0] = "da",
		.answers[1] = "bine",
		.answers[2] = "ok",
		.answers[3] = "alr",
		.question = "100 nefori vs 1 old money",

	}, {
		.ans = 3,
		.answers[0] = "da",
		.answers[1] = "bine",
		.answers[2] = "ok",
		.answers[3] = "alr",
		.question = "alb sau negru",

	}, {
		.ans = 1,
		.answers[0] = "da",
		.answers[1] = "bine",
		.answers[2] = "ok",
		.answers[3] = "alr",
		.question = "nota 10 sau nota 11",

	} };

	fwrite(q, sizeof(QUESTION), 4, fisier);

	fclose(fisier);
}

void timer() {
	float currentTime = GetTime();

	float endTime = currentTime + 15.0; // ten second timer;
}