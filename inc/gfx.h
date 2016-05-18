/*
 * gfx.h
 *
 *  Created on: May 17, 2016
 *      Author: shapa
 */

#ifndef GFX_H_
#define GFX_H_

#include <stdlib.h>
#include <stdint.h>

typedef struct surface {
	struct surface *next;
	uint8_t **line;
	uint16_t bytesPerLine;
	uint16_t x;
	uint16_t y;
	uint16_t width;
	uint16_t heigth;
	uint8_t depth;
} gfxSurface_t, *gfxSurface_p;

typedef struct {
	gfxSurface_p surface;

	uint8_t grayscale;
} shape_t, *shape_p;

void Surface_Init(uint16_t width, uint16_t heigth);

gfxSurface_p Surface_New(uint16_t width, uint16_t heigth);
void Surface_Delete(gfxSurface_p surface);

void Surface_SetGenericSurface(gfxSurface_p srf);
gfxSurface_p Surface_GetGenericSurface(void);

void Surface_Fill(gfxSurface_p srf, uint8_t val);

void Surface_BlendLayers(gfxSurface_p *layers, uint8_t count);

#endif /* GFX_H_ */
