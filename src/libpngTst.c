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

#include "testing.h"

void Render_Text(gfxSurface_p srf, const char *text);

int main(void) {
    const uint32_t width = 256;
    const uint32_t height = 64;

    Surface_Init(width, height);

//    Testing_SquareTest();

    gfxSurface_p genericSurface = Surface_GetGenericSurface();
    Surface_Fill(genericSurface, 1);

    gfxSurface_p firstLine = Surface_New(127, 19);
    gfxSurface_p secondLine = Surface_New(127, 19);

    firstLine->x = 0;
    firstLine->y = 0;
    secondLine->x = 0;
    secondLine->y = firstLine->heigth;

    firstLine->next = secondLine;

    Surface_Fill(firstLine, 0);
    Surface_Fill(secondLine, 0);
    Render_Text(firstLine, "Oil temp 110 C");
    Render_Text(secondLine, "Boost 15 PSI");

    Surface_Fill(genericSurface, 1);
    Surface_BlendLayers(&firstLine, 1);
	Testing_shotSurface(genericSurface, "text.png");

    Surface_Fill(firstLine, 0);
    Render_Text(firstLine, "HELLO TESTING!");
    Surface_Fill(genericSurface, 1);
    Surface_BlendLayers(&firstLine, 1);
	Testing_shotSurface(genericSurface, "text2.png");

	return EXIT_SUCCESS;
}
