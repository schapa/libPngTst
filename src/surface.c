/*
 * surface.c
 *
 *  Created on: May 17, 2016
 *      Author: shapa
 */


#include <string.h>
#include "gfx.h"

gfxSurface_p s_genericSurface = NULL;

gfxSurface_p Surface_New(uint16_t width, uint16_t heigth) {

	const uint8_t bitsDepth = 4;
	uint16_t i;
	gfxSurface_p surface = malloc(sizeof(gfxSurface_t));

	if (surface) {
		memset(surface, 0, sizeof(gfxSurface_t));
		surface->bytesPerLine = width*8/bitsDepth;
		surface->line = malloc(heigth*sizeof(*surface->line));
		if (surface->line) {
			for (i = 0; i < heigth; i++) {
				surface->line[i] = malloc(surface->bytesPerLine);
				if (!surface->line[i])
					break;
			}
			surface->width = 256;
			surface->heigth = 64;
		} else {
			free(surface);
			surface = NULL;
		}
	}
	return surface;
}

void Surface_Delete(gfxSurface_p surface) {
	if (surface) {
		if (surface->line) {
			free(surface->line);
		}
		free(surface);
	}
}

void Surface_SetGenericSurface(gfxSurface_p srf) {
	if (s_genericSurface)
		Surface_Delete(s_genericSurface);
	s_genericSurface = srf;
}

gfxSurface_p Surface_GetGenericSurface(void) {
	return s_genericSurface;
}

void Surface_BlendLayers(gfxSurface_p layers, uint8_t count) {
	uint8_t i;
	if (layers && count) {
		for (i = 0; i < count; i++) {
			gfxSurface_p surf = &layers[i];
			while (surf) {

				surf = surf->next;
			}
		}
	}
}
