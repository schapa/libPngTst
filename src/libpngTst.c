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


int main(void) {
    const uint32_t width = 256;
    const uint32_t height = 64;

    gfxSurface_p genericSurface = Surface_New(width, height);
    if (genericSurface) {
    	Surface_SetGenericSurface(genericSurface);
			Testing_dymmyFillSurface(genericSurface);
			Testing_shotSurface(genericSurface, "fff.png");
    }

    textWidget_t wdg = { { genericSurface, 15 }, "testText" };

	return EXIT_SUCCESS;
}
