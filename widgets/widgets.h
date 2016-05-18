/*
 * widgets.h
 *
 *  Created on: May 18, 2016
 *      Author: shapa
 */


#include "gfx.h"
#include "fontPainter.h"

typedef struct {
	shape_t shape;
	const char *text;
	uint8_t textSize;
	FontType textType;
} textWidget_t, *textWidget_p;
