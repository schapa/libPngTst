/*
 * textRender.c
 *
 *  Created on: May 17, 2016
 *      Author: shapa
 */


#include "gfx.h"
#include <string.h>

#include "century_schoolbook_l_bold_12_font.h"

const static struct font_char *s_fontLookup = century_schoolbook_l_bold_12_font_lookup;
const static uint8_t *s_fontPixels = century_schoolbook_l_bold_12_font_pixels;

static uint16_t textWidth(const char *text);

void Render_Text(gfxSurface_p srf, const char *text) {
	if (!srf || !text)
		return;
	uint16_t xPos = 0;
	while (*text) {
	    struct font_char fontChar = s_fontLookup[*text];
	    uint16_t x, y;
	    for (y = 0; (y < fontChar.h) && (y < srf->heigth); ++y) {
	    	for (x = 0; (x < fontChar.w) && (x < srf->width); ++x) {
	    		uint8_t pix = s_fontPixels[fontChar.offset + x + y * fontChar.w]>>4;
    			srf->line[y + fontChar.top][x + xPos + fontChar.left] = pix<<4 | pix;
	    	}
	    }
	    xPos += fontChar.advance;
	    text++;
	}
}

static uint16_t textWidth(const char *text) {
	uint16_t width = 0;
	while (*text) {
		const struct font_char font_c = s_fontLookup[*text++];
		width += font_c.advance;
	}
	return width;
}


