#ifndef UTILS_H
#define UTILS_H

#include "raylib.h"
#include "config.h"

typedef enum Block Block;

typedef struct Text {

	const char* text;
	Color color;
	
	int size;
	int x, y;

} Text;

typedef struct Button {

	const char* text;
	int fontSize;
	Color textColorDefault, textColorHover;

	Rectangle rectangle;
	float roundness;
	Color rectColorDefault, rectColorHover;

} Button;



int MouseOver(Rectangle r);

Button MakeButton(Rectangle r, float roundness, const char* text, int fontSize);
int ButtonClicked(Button b);

void DrawTextS(Text t);
void DrawButton(Button b);
void DrawTextBox(Rectangle box, const char* text);

#endif