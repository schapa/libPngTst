/*
 * textWidget.c
 *
 *  Created on: May 17, 2016
 *      Author: shapa
 */

#include <stdbool.h>
#include <string.h>
#include "widgets.h"

static _Bool simpleRender(textWidget_p wdg);

void TextWidget_Render(textWidget_p wdg) {
	if (!wdg)
		return;
	simpleRender(wdg);
}

static _Bool simpleRender(textWidget_p wdg) {
	if (!wdg || !wdg->text || !wdg->textSize)
		return false;

	_Bool result = false;
	gfxSurface_p srf = wdg->shape.surface;
	fontItem_p font = FontPainter_SizeLookup(wdg->textType, wdg->textSize);

	if (!font) {
		// no such font
		return result;
	}
	FontPainter_RenderText(srf, font, wdg->text);

	return result;
}
