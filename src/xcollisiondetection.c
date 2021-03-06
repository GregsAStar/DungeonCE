#include "menuandeditfunctions.h"
#include "maingameloop.h"
#include "gfx/tiles_gfx.h"
#include "xcollisiondetection.h"
#include "structs.h"

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
#include "gfx/Dungeon.h"
//#include "gfx/dungeon2.h"

int playerdamage;
extern int i;
extern uint24_t player_setup[];
extern int playerface;
extern int goup;
extern int godown;
extern int goleft;
extern int goright;
extern gfx_tilemap_t tilemap;
int replacex;
int replacey;
int hit;
extern int dmgmultiplier;
extern int player;

extern enemy_t enemy[];
extern pots_t pots[];
extern money_t money[];
int enemytilemapx;
int enemytilemapy;
int pottilemapx;
int pottilemapy;
extern int playertilex;
extern int playertiley;
extern int playertilemapx;
extern int playertilemapy;
extern int *inputx;
extern int *inputy;
extern unsigned int x_offset;
extern unsigned int y_offset;

int healthincrement = 10;

void collisionleft(void) {
	goleft = 1;
	if (player == 1) {
	if (((gfx_GetTile(&tilemap,playertilex-32,playertiley)) >= 18)) {
	goleft = 0;
	}
	}
	for (i = 0; i < NUM_ENEMIES; i++) {
		enemytilemapx = (enemy[i].x/32);
		enemytilemapy = (enemy[i].y/32);
		if (x_offset <= (enemy[i].x)){
			if ((enemy[i].x) <= (x_offset + 288)){
				if (y_offset <= (enemy[i].y)) {
					if  ((enemy[i].y) <= (y_offset + 192)) {
						if (((*inputx-1) == enemytilemapx) & (*inputy == enemytilemapy)){
							if (enemy[i].dead == 0) {
								goleft = 0;
							}
						}
					}
				}
			}
		}
	}
	for (i = 0; i < NUM_POTS; i++) {
		pottilemapx = (pots[i].p_x/32);
		pottilemapy = (pots[i].p_y/32);
		if (x_offset <= (pots[i].p_x)){
			if ((pots[i].p_x) <= (x_offset + 288)){
				if (y_offset <= (pots[i].p_y)) {
					if  ((pots[i].p_y) <= (y_offset + 192)) {
						if (((*inputx-1) == pottilemapx) & (*inputy == pottilemapy)){
							if (pots[i].potdead == 0) {
								goleft = 0;
							}
						}
					}
				}
			}
		}
	}
}
void collisionright(void) {
	goright = 1;
	if (player == 1) {
	if (((gfx_GetTile(&tilemap,playertilex+32,playertiley)) >= 18)) {
		goright = 0;
	}
	}
	for (i = 0; i < NUM_ENEMIES; i++) {
		enemytilemapx = (enemy[i].x/32);
		enemytilemapy = (enemy[i].y/32);
		if (x_offset <= (enemy[i].x)){
			if ((enemy[i].x) <= (x_offset + 288)){
				if (y_offset <= (enemy[i].y)) {
					if  ((enemy[i].y) <= (y_offset + 192)) {
						if (((*inputx+1) == enemytilemapx) & (*inputy == enemytilemapy)){
							if (enemy[i].dead == 0) {
								goright = 0;
							}
						}
					}
				}
			}
		}
		
	}
	for (i = 0; i < NUM_POTS; i++) {
		pottilemapx = (pots[i].p_x/32);
		pottilemapy = (pots[i].p_y/32);
		if (x_offset <= (pots[i].p_x)){
			if ((pots[i].p_x) <= (x_offset + 288)){
				if (y_offset <= (pots[i].p_y)) {
					if  ((pots[i].p_y) <= (y_offset + 192)) {
						if (((*inputx+1) == pottilemapx) & (*inputy == pottilemapy)){
							if (pots[i].potdead == 0) {
								goright = 0;
							}
						}
					}
				}
			}
		}
	}
}
void collisionup(void) {
	goup = 1;
	if (player == 1) {
	if (((gfx_GetTile(&tilemap,playertilex,playertiley-32)) >= 18)) {
	goup = 0;
	}
	}
	for (i = 0; i < NUM_ENEMIES; i++) {
		enemytilemapx = (enemy[i].x/32);
		enemytilemapy = (enemy[i].y/32);
		if (x_offset <= (enemy[i].x)){
			if ((enemy[i].x) <= (x_offset + 288)){
				if (y_offset <= (enemy[i].y)) {
					if  ((enemy[i].y) <= (y_offset + 192)) {
						if ((*inputx == enemytilemapx) & ((*inputy-1) == enemytilemapy)){
							if (enemy[i].dead == 0) {
								goup = 0;
							}
						}
					}
				}
			}
		}
	}
	for (i = 0; i < NUM_POTS; i++) {
		pottilemapx = (pots[i].p_x/32);
		pottilemapy = (pots[i].p_y/32);
		if (x_offset <= (pots[i].p_x)){
			if ((pots[i].p_x) <= (x_offset + 288)){
				if (y_offset <= (pots[i].p_y)) {
					if  ((pots[i].p_y) <= (y_offset + 192)) {
						if ((*inputx == pottilemapx) & ((*inputy-1) == pottilemapy)){
							if (pots[i].potdead == 0) {
								goup = 0;
							}
						}
					}
				}
			}
		}
	}
}
void collisiondown(void) {
	godown = 1;
	if (player == 1) {
	if (((gfx_GetTile(&tilemap,playertilex,playertiley+32)) >= 18)) {
	godown = 0;
	}
	}
	for (i = 0; i < NUM_ENEMIES; i++) {
		enemytilemapx = (enemy[i].x/32);
		enemytilemapy = (enemy[i].y/32);
		if (x_offset <= (enemy[i].x)){
			if ((enemy[i].x) <= (x_offset + 288)){
				if (y_offset <= (enemy[i].y)) {
					if  ((enemy[i].y) <= (y_offset + 192)) {
						if ((*inputx == enemytilemapx) & ((*inputy+1) == enemytilemapy)){
							if (enemy[i].dead == 0) {
								godown = 0;
							}
						}
					}
				}
			}
		}
	}
	for (i = 0; i < NUM_POTS; i++) {
		pottilemapx = (pots[i].p_x/32);
		pottilemapy = (pots[i].p_y/32);
		if (x_offset <= (pots[i].p_x)){
			if ((pots[i].p_x) <= (x_offset + 288)){
				if (y_offset <= (pots[i].p_y)) {
					if  ((pots[i].p_y) <= (y_offset + 192)) {
						if ((*inputx == pottilemapx) & ((*inputy+1) == pottilemapy)){
							if (pots[i].potdead == 0) {
								godown = 0;
							}
						}
					}
				}
			}
		}	
	}
}
void playerattackhitcheck(void) {
int moneytilemapx;
int moneytilemapy;
int randcheck = 1;
///*money
	for (i = 0; i < NUM_POTS; i++) {
		moneytilemapx = (money[i].m_x/32);
		moneytilemapy = (money[i].m_y/32);
		hit = 0;
		if (playerface == 1){
			if (((playertilemapx-1) == moneytilemapx) & (playertilemapy == moneytilemapy)){
				hit = 1;
			}
		}
		if (playerface == 2){
			if ((playertilemapx == moneytilemapx) & ((playertilemapy-1) == moneytilemapy)){
				hit = 1;
			}
		}
		if (playerface == 3){
			if (((playertilemapx+1) == moneytilemapx) & (playertilemapy == moneytilemapy)){
				hit = 1;
			}
		}
		if (playerface == 4){
			if ((playertilemapx == moneytilemapx) & ((playertilemapy+1) == moneytilemapy)){
				hit = 1;
			}
		}
		
		if (hit == 1) {
			if (money[i].moneydead == 0){
					player_setup[7] = (player_setup[7] + money[i].moneyvalue);
					if (player_setup[7] > 99999){player_setup[7] = 99999;}
			}
			money[i].moneydead = 1;
		}
	}
//*/
//enemies
	for (i = 0; i < NUM_ENEMIES; i++) {
		enemytilemapx = (enemy[i].x/32);
		enemytilemapy = (enemy[i].y/32);
		hit = 0;
		if (playerface == 1){
			if (((playertilemapx-1) == enemytilemapx) & (playertilemapy == enemytilemapy)){
				hit = 1;
			}
		}
		if (playerface == 2){
			if ((playertilemapx == enemytilemapx) & ((playertilemapy-1) == enemytilemapy)){
				hit = 1;
			}
		}
		if (playerface == 3){
			if (((playertilemapx+1) == enemytilemapx) & (playertilemapy == enemytilemapy)){
				hit = 1;
			}
		}
		if (playerface == 4){
			if ((playertilemapx == enemytilemapx) & ((playertilemapy+1) == enemytilemapy)){
				hit = 1;
			}
		}
		if (hit == 1) {
			(enemy[i].health) = ((enemy[i].health ) - (playerdamage * dmgmultiplier));
		}
	}	
//pots
	for (i = 0; i < NUM_POTS; i++) {
		pottilemapx = (pots[i].p_x/32);
		pottilemapy = (pots[i].p_y/32);
		hit = 0;
		if (playerface == 1){
			if (((playertilemapx-1) == pottilemapx) & (playertilemapy == pottilemapy)){
				hit = 1;
			}
		}
		if (playerface == 2){
			if ((playertilemapx == pottilemapx) & ((playertilemapy-1) == pottilemapy)){
				hit = 1;
			}
		}
		if (playerface == 3){
			if (((playertilemapx+1) == pottilemapx) & (playertilemapy == pottilemapy)){
				hit = 1;
			}
		}
		if (playerface == 4){
			if ((playertilemapx == pottilemapx) & ((playertilemapy+1) == pottilemapy)){
				hit = 1;
			}
		}
		if (hit == 1) {
			if (pots[i].potdead == 0){
				if (pots[i].pottype == 1){
					player_setup[6] = (player_setup[6] + healthincrement);
				}
				money[i].m_x = pots[i].p_x;
				money[i].m_y = pots[i].p_y;
				money[i].moneydead = 0;
				money[i].moneyvalue = 1;
				randcheck = 30;
					if (randcheck >= randInt(0,100)) {
						money[i].moneyvalue = 5;
					}
				randcheck = 20;
					if (randcheck >= randInt(0,100)) {
						money[i].moneyvalue = 10;
					}
				randcheck = 10;
					if (randcheck >= randInt(0,100)) {
						money[i].moneyvalue = 20;
					}
				randcheck = 1;
					if (randcheck >= randInt(0,100)) {
						money[i].moneyvalue = 100;
					}
			}
			pots[i].potdead = 1;
		}
	}
}