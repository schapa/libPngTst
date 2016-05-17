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

void makeShot(uint8_t *buff, const uint32_t width, const uint32_t height, const char *fileName);

int main(void) {
	uint8_t buff[8192];
    const uint32_t width = 256;
    const uint32_t height = 64;

    int i, j;
    for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			float xDist = abs(height/2 - i)/(float)(height/2);
			float yDist = abs(width/2 - j)/(float)(width/2);
			int alpha = (int)(0x0F*xDist*yDist);
			if (j%2) {
				buff[i*width/2 + j/2] |= alpha<<4;
			} else {
				buff[i*width/2 + j/2] = alpha;
			}
		}
	}

	makeShot(buff, width, height, "fff.png");

	return EXIT_SUCCESS;
}
