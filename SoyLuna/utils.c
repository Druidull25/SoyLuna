#include "utils.h"
#include <math.h>
#include <stdio.h>
#include "string.h"

void DrawTextS(Text t)
{
	DrawText(t.text, t.x, t.y, t.size, t.color);
}

int MouseOver(Rectangle r)
{
	int distX = GetMouseX() - r.x;
	int distY = GetMouseY() - r.y;

	return ((distX < r.width) && (distX > 0) &&
		    (distY < r.height) && (distY > 0));
}

void DrawButton(Button b)
{
	Color rectColor = b.rectColorDefault;
	Color textColor = b.textColorDefault;

	Vector2 textDimension = MeasureTextEx(GetFontDefault(), b.text, b.fontSize, b.fontSize / 10);
	int textX = b.rectangle.x + b.rectangle.width / 2 - textDimension.x / 2;
	int textY = b.rectangle.y + b.rectangle.height / 2 - textDimension.y / 2;

	if (MouseOver(b.rectangle))
	{
		rectColor = b.rectColorHover;
		textColor = b.textColorHover;
	}

	DrawRectangleRounded(b.rectangle, b.roundness, 10, rectColor);
	DrawText(b.text, textX, textY, b.fontSize, textColor);
}

Button MakeButton(Rectangle r, float roundness, const char* text, int fontSize)
{
	Button b;

	b.text = text;
	b.fontSize = fontSize;
	b.textColorDefault = DARKGRAY;
	b.textColorHover = RAYWHITE;

	b.rectangle = r;
	b.rectColorDefault = LIGHTGRAY;
	b.rectColorHover = DARKGRAY;
	b.roundness = roundness;

	return b;
}

int ButtonClicked(Button b)
{
	if (IsMouseButtonReleased(0) && MouseOver(b.rectangle))
		return 1;

	return 0;
}

void DrawTextBox(Rectangle box, const char* text)
{
	int padding = 20;
	int wordCount = 0;
	int fontSize = 30;
	const char** words = TextSplit(text, ' ', &wordCount);

	Vector2 pos = { box.x + padding, box.y + padding };

	Color color = { 0, 0, 0, 100 };
	DrawRectangleRec(box, color);

	for (int i = 0; i < wordCount; ++i)
	{
		if (pos.x + MeasureText(TextFormat(" %s", words[i]), fontSize) + padding
			<= box.x + box.width)
		{
			DrawText(words[i], pos.x, pos.y, fontSize, WHITE);
			pos.x += MeasureText(TextFormat(" %s", words[i]), fontSize);
		}
		else
		{
			pos.x = box.x + padding;
			pos.y += fontSize + padding;
		}
	}
}