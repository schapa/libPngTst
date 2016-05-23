/*
 ============================================================================
 Name        : libpngTst.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "png.h"
#include "gfx.h"
#include "widgets.h"

#include "testing.h"
extern void TextWidget_Render(textWidget_p wdg) ;
int main(void) {
    const uint32_t width = 256;
    const uint32_t height = 64;

    Surface_Init(width, height);

//    Testing_SquareTest();
    Testing_SimpleText();

    textWidget_t text;
    text.shape.surface = Surface_GetGenericSurface();
    text.textSize = 12;
    text.textType = FONT_CENTURY_SCOOLBOOK;
    text.text = "Hello my someone 1111";

    TextWidget_Render(&text);
	Testing_shotSurface(Surface_GetGenericSurface(), "text3.png");

	return EXIT_SUCCESS;
}
