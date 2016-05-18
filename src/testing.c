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
#include "fontPainter.h"

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

void Testing_SquareTest (void) {

    gfxSurface_p genericSurface = Surface_GetGenericSurface();

	Testing_dymmyFillSurface(genericSurface);
	Testing_shotSurface(genericSurface, "fff.png");

    gfxSurface_p one = Surface_New(10, 10);
    gfxSurface_p two = Surface_New(20, 20);
    gfxSurface_p three = Surface_New(30, 30);

    Surface_Fill(one, 0);
    Surface_Fill(two, 7);
    Surface_Fill(three, 15);

	Testing_shotSurface(one, "1.png");
	Testing_shotSurface(two, "2.png");
	Testing_shotSurface(three, "3.png");

    one->x = 10;
    one->y = 10;
    two->x = 30;
    two->y = 15;
    three->x = 70;
    three->y = 20;

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

	Surface_Delete(one);
	Surface_Delete(two);
	Surface_Delete(three);
    Surface_Fill(genericSurface, 0);
}

void Testing_SimpleText (void) {
    gfxSurface_p genericSurface = Surface_GetGenericSurface();
    Surface_Fill(genericSurface, 1);

    gfxSurface_p firstLine = Surface_New(255, 19);
    gfxSurface_p secondLine = Surface_New(255, 19);

    fontItem_p font = FontPainter_SizeLookup(FONT_DIGITAL_7SEGMENT, 12);
    fontItem_p fontBig = FontPainter_SizeLookup(FONT_CENTURY_SCOOLBOOK, 12);

    firstLine->x = 0;
    firstLine->y = 0;
    secondLine->x = 0;
    secondLine->y = firstLine->heigth;

    firstLine->next = secondLine;

    Surface_Fill(firstLine, 1);
    Surface_Fill(secondLine, 1);
    FontPainter_RenderText(firstLine, font, "Oil temp 11.0 C");
    FontPainter_RenderText(secondLine, fontBig, "10: 30");

    Surface_Fill(genericSurface, 1);
    Surface_BlendLayers(&firstLine, 1);
	Testing_shotSurface(genericSurface, "text.png");

    Surface_Fill(firstLine, 3);
    Surface_Fill(secondLine, 3);
    FontPainter_RenderText(firstLine, font, "The quick brown fox jumps over the lazy dog");
    FontPainter_RenderText(secondLine, fontBig, "The quick brown fox jumps over the lazy dog");
    Surface_Fill(genericSurface, 1);
    Surface_BlendLayers(&firstLine, 1);
	Testing_shotSurface(genericSurface, "text2.png");

	Surface_Delete(firstLine);
	Surface_Delete(secondLine);
    Surface_Fill(genericSurface, 0);

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


