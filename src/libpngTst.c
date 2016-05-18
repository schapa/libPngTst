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

//    Testing_SquareTest();
    Testing_SimpleText();

	return EXIT_SUCCESS;
}
