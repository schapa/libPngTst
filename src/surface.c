/*
 * surface.c
 *
 *  Created on: May 17, 2016
 *      Author: shapa
 */


#include <string.h>
#include "gfx.h"

gfxSurface_p s_genericSurface = NULL;

void Surface_Init(uint16_t width, uint16_t heigth) {
	Surface_SetGenericSurface(Surface_New(width, heigth));
}

gfxSurface_p Surface_New(uint16_t width, uint16_t heigth) {

	const uint8_t bitsDepth = 4;
	uint16_t i;
	gfxSurface_p surface = malloc(sizeof(gfxSurface_t));

	if (surface) {
		memset(surface, 0, sizeof(gfxSurface_t));
		surface->bytesPerLine = width*8/bitsDepth + width%2;
		surface->line = malloc(heigth*sizeof(*surface->line));
		if (surface->line) {
			memset(surface->line, 0, heigth*sizeof(*surface->line));
			for (i = 0; i < heigth; i++) {
				surface->line[i] = malloc(surface->bytesPerLine);
				if (!surface->line[i])
					break;
			}
			if (i != heigth) {
				Surface_Delete(surface);
				return NULL;
			}
			surface->width = width;
			surface->heigth = heigth;
		} else {
			free(surface);
			surface = NULL;
		}
	}
	return surface;
}

void Surface_Delete(gfxSurface_p surface) {
	uint16_t i;
	if (surface) {
		if (surface->line) {
			for (i = 0; i < surface->heigth; i++) {
				free(surface->line[i]);
			}
			free(surface->line);
		}
		free(surface);
	}
}

void Surface_Fill(gfxSurface_p srf, uint8_t val) {

	uint16_t i;
	if (srf) {
		val &= 0x0F;
		val |= val<<4;
		for (i = 0; i < srf->heigth; i++) {
			memset(srf->line[i], val, srf->bytesPerLine);
		}
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

void Surface_BlendLayers(gfxSurface_p *layers, uint8_t count) {
	uint8_t i;
	uint16_t y;
	if (layers && count) {
		for (i = 0; i < count; i++) {
			gfxSurface_p surf = layers[i];
			while (surf) {
				for (y = 0; (y < surf->heigth) && (surf->y + y < s_genericSurface->heigth); y++) {
					uint8_t *start = &s_genericSurface->line[surf->y + y][surf->x];
					uint16_t len = surf->x + surf->width < s_genericSurface->width ? surf->width :
							surf->x < s_genericSurface->width ? s_genericSurface->width - surf->x : 0;
					memcpy(start, surf->line[y], len);
				}
				surf = surf->next;
			}
		}
	}
}
