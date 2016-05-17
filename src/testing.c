/*
 * screenshot.c
 *
 *  Created on: May 17, 2016
 *      Author: shapa
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "png.h"
#include "testing.h"

static void makeShot(uint8_t **buff, const uint32_t width, const uint32_t height, const char *fileName);

void Testing_shotSurface (gfxSurface_p srf, const char *fileName) {
	if (srf && fileName) {
		makeShot(srf->line, srf->width, srf->heigth, fileName);
	}
}

void Testing_dymmyFillSurface (gfxSurface_p srf) {

	if (srf && srf->line) {
		int i, j;
		for (i = 0; i < srf->heigth; i++) {
			for (j = 0; j < srf->width; j++) {
				float xDist = abs(srf->heigth/2 - i)/(float)(srf->heigth/2);
				float yDist = abs(srf->width/2 - j)/(float)(srf->width/2);
				int alpha = (int)(0x0F*xDist*yDist);
				if (j%2) {
					srf->line[i][j] |= alpha<<4;
				} else {
					srf->line[i][j] = alpha;
				}
			}
		}
	}
}

static void makeShot(uint8_t **buff, const uint32_t width, const uint32_t height, const char *fileName) {

    uint8_t pngBuff[height][width][4];
	unsigned char *rows[height];

    FILE *fp = NULL;
    png_structp pngWriter = NULL;
    png_infop pngInfo = NULL;

    int i, j;
    int buffCnt = 0;

    do {
    	if (!buff || !fileName)
    		break;

    	fp = fopen(fileName, "wb");
		if (!fp) {
			printf("[Err] Failed to open File <%s>", fileName);
			break;
		}

	    pngWriter = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	    if (!pngWriter) {
			printf("[Err] Failed to create png");
			break;
	    }
		if (setjmp(png_jmpbuf(pngWriter))) {
			goto destroy_write;
		}

	    pngInfo = png_create_info_struct(pngWriter);
		if (!pngInfo) {
			printf("[Err] Failed to create info struct");
			break;
		}
		for (i = 0; i < height; i++) {
	        rows[i] = pngBuff[i];
			for (j = 0; j < width; j++) {
//				float xDist = abs(height/2 - i)/(float)(height/2);
//				float yDist = abs(width/2 - j)/(float)(width/2);
//				int alpha = (int)(255*xDist*yDist);
				int alpha = 0;
				if (buffCnt %2) {
					alpha = 255 * ((buff[i][j]>>4)/(float)0x0F);
				} else {
					alpha = 255 * ((buff[i][j] & 0x0F)/(float)0x0F);
				}
				buffCnt++;
				*(uint32_t*)pngBuff[i][j] = 0xFFFFFFFF;
				pngBuff[i][j][0] = alpha;
				pngBuff[i][j][1] = alpha;
				pngBuff[i][j][2] = alpha;
			}
		}
		png_init_io(pngWriter, fp);
		png_set_IHDR(pngWriter, pngInfo, width, height, 8, PNG_COLOR_TYPE_RGB_ALPHA,
		        PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

	    png_set_rows(pngWriter, pngInfo, rows);
	    png_write_png(pngWriter, pngInfo, PNG_TRANSFORM_IDENTITY, NULL);
	    png_write_end(pngWriter, pngInfo);

    } while (0);
destroy_write: // hate it
    if (pngWriter)
    	png_destroy_write_struct(&pngWriter, NULL);
    if (fp)
        fclose(fp);
}

