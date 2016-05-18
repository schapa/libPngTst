/*
 * textRender.c
 *
 *  Created on: May 17, 2016
 *      Author: shapa
 */

#include <string.h>
#include "fontPainter.h"

void FontPainter_RenderText(gfxSurface_p srf, fontItem_p font, const char *text) {
	if (!srf || !font || !text)
		return;
	uint16_t xPos = 0;
	fontLookupItem_p lookup = font->lookup;
	const uint8_t *pixel = font->pixelData;
	while (*text) {
		fontLookupItem_t character = lookup[(size_t)*text];
	    uint16_t x, y;
	    for (y = 0; (y < character.heigth) && (y < srf->heigth); ++y) {
	    	for (x = 0; (x < character.width) && (x < srf->width); ++x) {
	    		uint8_t pix = pixel[character.offset + x + y * character.width]>>4;
    			srf->line[y + character.top][x + xPos + character.left] = pix<<4 | pix;
	    	}
	    }
	    xPos += character.advance + 1;
	    text++;
	}
}

uint16_t FontPainter_GetTextWidth(fontItem_p font, const char *text) {
	uint16_t width = 0;
	if (!font || !text)
		return width;
	fontLookupItem_p lookup = font->lookup;
	while (*text) {
		width += lookup[(size_t)*text++].advance;
	}
	return width;
}


