#include "menuandeditfunctions.h"
#include "maingameloop.h"
#include "gfx/dungeon_gfx.h"
#include "gfx/tiles_gfx.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <setjmp.h>
#include <fileioc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphx.h>
#include <keypadc.h>

extern int goup;
extern int godown;
extern int goleft;
extern int goright;




void collisionleft(void) {
	(goleft = 1);
}

void collisionright(void) {
	(goright = 1);
}

void collisionup(void) {
	(goup = 1);
}

void collisiondown(void) {
	(godown = 1);
}
