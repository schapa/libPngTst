/*
 * testing.h
 *
 *  Created on: May 17, 2016
 *      Author: shapa
 */

#ifndef TESTING_H_
#define TESTING_H_

#include <stdlib.h>
#include <stdint.h>
#include "gfx.h"

void Testing_shotSurface (gfxSurface_p srf, const char *fileName);
void Testing_dymmyFillSurface (gfxSurface_p srf);

void Testing_SquareTest (void);
void Testing_SimpleText (void);

#endif /* TESTING_H_ */
