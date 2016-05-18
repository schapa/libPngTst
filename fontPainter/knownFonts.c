/*
 * knownFonts.c
 *
 *  Created on: May 18, 2016
 *      Author: shapa
 */

#include <stdint.h>

#include "fontPainter.h"
//#include "century_schoolbook_l_bold_8_font.h"
#include "century_schoolbook_l_bold_12_font.h"
//#include "creampuff_regular_12_font.h"
#include "digital_7_regular_12_font.h"
#include "digital_7_regular_18_font.h"


typedef struct {
	const FontType type;
	const fontItem_p *fonts;
	const size_t count;
} fontSizeMap_t, *fontSizeMap_p;


static const fontItem_p s_digital_7_regular_font[] = {
		&digital_7_regular_12_font,
		&digital_7_regular_18_font,
};
static const fontItem_p s_century_schoolbook_bold_font[] = {
		&century_schoolbook_l_bold_12_font,
};

static const fontSizeMap_t s_knownFonts[] = {
		{ FONT_DIGITAL_7SEGMENT, s_digital_7_regular_font, sizeof(s_digital_7_regular_font)/sizeof(*s_digital_7_regular_font) },
		{ FONT_CENTURY_SCOOLBOOK, s_century_schoolbook_bold_font, sizeof(s_century_schoolbook_bold_font)/sizeof(*s_century_schoolbook_bold_font) },
};


fontItem_p FontPainter_SizeLookup(FontType type, uint8_t size) {
	fontItem_p font = NULL;
	if (type < FONT_LAST) {
		size_t i;
		for (i = 0; i < s_knownFonts[type].count; i++) {
			font = s_knownFonts[type].fonts[i];
			if (font && font->size == size)
				break;
		}
	}
	return font;
}
