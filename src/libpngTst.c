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

    Surface_Init(width, height);

    gfxSurface_p genericSurface = Surface_GetGenericSurface();
		Testing_dymmyFillSurface(genericSurface);
		Testing_shotSurface(genericSurface, "fff.png");

    gfxSurface_p one = Surface_New(10, 10);
    gfxSurface_p two = Surface_New(20, 20);
    gfxSurface_p three = Surface_New(30, 30);

    Surface_Fill(one, 0);
    Surface_Fill(two, 7);
    Surface_Fill(three, 15);

	Testing_shotSurface(one, "1");
	Testing_shotSurface(two, "2.png");
	Testing_shotSurface(three, "3.png");

    one->x = 10;
    one->y = 10;
    two->x = 50;
    two->y = 10;
    three->x = 100;
    three->y = 10;

    one->next = two;
    two->next = three;

    Surface_BlendLayers(&one, 1);
	Testing_shotSurface(genericSurface, "aaa.png");

    gfxSurface_p layers[] = { three, two, one };

    one->x = 10;
    one->y = 10;
    two->x = 10;
    two->y = 10;
    three->x = 10;
    three->y = 10;

    one->next = NULL;
    two->next = NULL;

    Surface_Fill(genericSurface, 0);
    Surface_BlendLayers(layers, 3);
	Testing_shotSurface(genericSurface, "bbb.png");

    textWidget_t wdg = { { genericSurface, 15 }, "testText" };

	return EXIT_SUCCESS;
}
