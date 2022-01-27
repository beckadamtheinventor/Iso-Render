/*
 *--------------------------------------
 * Program Name: ISO
 * Author: Michael2_3B
 * License: MIT
 * Description: Rendering isometric terrain in the C language on the TI-84+ CE.
 *--------------------------------------
*/

/* Keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

/* Standard headers (recommended) */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <graphx.h>
#include <keypadc.h>
#include <fileioc.h>

/* Include the sprite data */
#include "gfx/logo_gfx.h"

/* Put your function prototypes here */
void generateMap(void);

void drawMap(void);
void drawMap_C(void);
void SwapDraw(void);

/* Put all your globals here */


const gfx_sprite_t *blocks[15] = {
    /* 000 */ brick_stairs_east,
    /* 001 */ brick,
    /* 002 */ coal_ore,
    /* 003 */ dirt,
    /* 004 */ grass_block,
    /* 005 */ stone_brick_stairs_east,
    /* 006 */ stone_brick,
    /* 007 */ stone,
    /* 008 */ glass_pane,
    /* 009 */ glass_block,
    /* 010 */ water_surface,
    /* 011 */ water_full,
    /* 012 */ stone_brick_2,
    /* 013 */ stone_brick_stairs_east_2,
    /* 014 */ stone_stairs_east
    /* 015 */ 
    /* 016 */ 
    /* 017 */ 
    /* 018 */ 
    /* 019 */ 
    /* 020 */ 
    /* 021 */ 
    /* 022 */ 
    /* 023 */ 
    /* 024 */ 
    /* 025 */ 
    /* 026 */ 
    /* 027 */ 
    /* 028 */ 
    /* 029 */ 
    /* 030 */ 
    /* 031 */ 
};

int a, b, c, i, x, y;

const int midX = 160;
const int midY = 120;

const int sizeX = 10;
const int sizeZ = 10;
const int sizeY = 10;

#define RNG_ITERATIONS 5
// int scale1 = 13;
// int scale2 = 15;

uint8_t map[sizeX*sizeZ*sizeY];

int main(void) {
    /* Fill in the body of the main function here */
    // srand(rtc_Time(NULL));
	sk_key_t key;
	uint32_t time;
	uint8_t seed[8];

    gfx_Begin();
    gfx_SetPalette(logo_gfx_pal, sizeof_logo_gfx_pal, 0);
	gfx_SetTextTransparentColor(0);
	gfx_SetTextBGColor(0);
	gfx_SetTextFGColor(6);
	// gfx_SetDraw(1);
	restart_test:;
	memset(&seed, 0x66, sizeof(seed));
	gfx_ZeroScreen();
	gfx_PrintStringXY("press keys to add randomness.",0,0);
	gfx_PrintStringXY("press enter to continue",0,10);
	gfx_PrintStringXY("press clear to quit",0,20);
	do {
		uint8_t ch;
		for (int i=0; i<sizeof(seed); i++) {
			gfx_SetColor(seed[i]>>4);
			gfx_FillRectangle(i*8+0, 50, 4, 6);
			gfx_SetColor(seed[i]&15);
			gfx_FillRectangle(i*8+4, 50, 4, 6);
		}
		while (!(key=os_GetCSC()));
		ch = key;
		for (int j=0; j<RNG_ITERATIONS; j++) {
			for (int i=0; i<sizeof(seed); i++) {
				uint8_t nextch = seed[i];
				seed[i] = ((seed[i]<<2) ^ ch) * 3;
				ch = nextch;
			}
		}
		if (key == sk_Clear) goto end;
	} while (key != sk_Enter);
	memset(map, 0xFF, sizeof(map)); // air
	for (int i=0; i<sizeof(seed); i++) {
		int y = ((seed[i]>>3)&7)^(seed[i]&7);
		int z = (seed[i]>>3)&7;
		if (seed[i]&0x40) {
			//horizontal
			if (seed[i]&0x80) {
				// horizontal bar x
				for (int x=0; x<sizeX-(seed[i]&7); x++) {
					if (x&1) map[x + z*sizeX + y*sizeX*sizeZ] = 12;
					else     map[x + z*sizeX + y*sizeX*sizeZ] = 6;
				}
			} else {
				// horizontal bar z
				for (int x=0; x<sizeZ-(seed[i]&7); x++) {
					if (x&1) map[z + x*sizeX + y*sizeX*sizeZ] = 12;
					else     map[z + x*sizeX + y*sizeX*sizeZ] = 6;
				}
			}
		} else {
			if (seed[i]&0x80) {
				// column
				for (int x=0; x<sizeY; x++) {
					map[y + z*sizeX + x*sizeX*sizeZ] = 1;
				}
			}
			// nothing
		}
	}

	do {
		gfx_ZeroScreen();
		timer_Enable(1, TIMER_32K, TIMER_NOINT, TIMER_UP);
		timer_Set(1, 0);
		drawMap();
		time = timer_Get(1);
		timer_Disable(1);
		gfx_PrintStringXY("ASM:", 0, 0);
		gfx_PrintInt((time*1000)/32768, 6);
		gfx_PrintString("ms");
		// SwapDraw();
		while (!(key = os_GetCSC()));
		if (key == sk_Clear) goto end;
	} while (key != sk_Enter);

	// gfx_SetDraw(0);
    do {
		gfx_ZeroScreen();
		timer_Enable(1, TIMER_32K, TIMER_NOINT, TIMER_UP);
		timer_Set(1, 0);
		drawMap_C();
		time = timer_Get(1);
		timer_Disable(1);
		gfx_PrintStringXY("C:", 18, 0);
		gfx_PrintInt((time*1000)/32768, 6);
		gfx_PrintString("ms");
		while (!(key = os_GetCSC()));
		if (key == sk_Clear) goto end;
	} while (key != sk_Enter);
	goto restart_test;
	end:;
    gfx_End();
	return 0;
}

/* Put other functions here */

void generateMap(void){
    //does not generate dynamic terrain yet

    for(a=0; a<sizeX; a++){
        for(b=0; b<sizeZ; b++){
            for(c=0; c<sizeY; c++){
				int x = a+b*sizeX+c*sizeX*sizeZ;
                if(c<3){
                    i = rand()%8;
                    if(i==0){
                        map[x] = 2;
                    } else {
                        map[x] = 7;
                    }
                } else if(c==3){
                    map[x] = 3;
                } else if(c==4){
                    map[x] = 3;
                    if(!(a>0 && a<6 && b>0 && b<6)){
                        map[x] = 4;
                    }
                } else {
                    map[x] = 0xFF;
                }
            }
        }
    }

    //0 brick stairs east
    //1 brick
    //2 coal ore
    //3 dirt
    //4 grass
    //5 stone brick stairs east
    //6 stone brick
    //7 stone
    //8 glass pane
    //9 glass block
    //10 water surface
    //11 water full
    //12 stone brick (alternating block)
    //13 stone brick stairs east (alternating block)
    //14 stone stairs east

    //air blocks
    map[1+7*sizeX+4*sizeX*sizeZ] = -1;
    map[4+7*sizeX+4*sizeX*sizeZ] = -1;

    //water
    for(a=6; a<=7; a++){
        for(b=1; b<=7; b++){
            for(c=1; c<=4; c++){
				int x = a+b*sizeX+c*sizeX*sizeZ;
                if(c==4)
                    map[x] = 10;
				else
					map[x] = 11;
            }
        }
    }

    //floating water
    map[0+7*sizeX+8*sizeX*sizeZ] = 10;

    //floating glass block, glass pane
    map[7+0*sizeX+7*sizeX*sizeZ] = 9;
    map[7+0*sizeX+8*sizeX*sizeZ] = 8;


    //structure design

    //floor
    for(b=1; b<=5; b++){
        for(a=1; a<=5; a++){
			int x = a+b*sizeX+5*sizeX*sizeZ;
            if((a+b+5)%2==0){
                map[x] = 12;
            } else {
                map[x] = 6;
            }
        }
    }

    //stairs
    map[2+6*sizeX+5*sizeX*sizeZ] = 5;
    map[3+6*sizeX+5*sizeX*sizeZ] = 13;
    map[4+6*sizeX+5*sizeX*sizeZ] = 5;

    map[2+7*sizeX+4*sizeX*sizeZ] = 5;
    map[3+7*sizeX+4*sizeX*sizeZ] = 13;
    map[4+7*sizeX+4*sizeX*sizeZ] = 5;

    //pillars
    for(c=6; c<=9; c++){
        map[1+1*sizeX+c*sizeX*sizeZ] = 6;
        map[5+1*sizeX+c*sizeX*sizeZ] = 6;
        map[1+5*sizeX+c*sizeX*sizeZ] = 6;
    }

    //crossbeams
    map[4+1*sizeX+9*sizeX*sizeZ] = 12;
    map[3+1*sizeX+9*sizeX*sizeZ] = 6;
    map[2+1*sizeX+9*sizeX*sizeZ] = 12;
    map[1+2*sizeX+9*sizeX*sizeZ] = 12;
    map[1+3*sizeX+9*sizeX*sizeZ] = 6;
    map[1+4*sizeX+9*sizeX*sizeZ] = 12;

    //windows
    for(c=6; c<9; c++){
        map[4+1*sizeX+c*sizeX*sizeZ] = 9;
        map[3+1*sizeX+c*sizeX*sizeZ] = 9;
        map[2+1*sizeX+c*sizeX*sizeZ] = 9;

        map[1+2*sizeX+c*sizeX*sizeZ] = 8;
        map[1+3*sizeX+c*sizeX*sizeZ] = 8;
        map[1+4*sizeX+c*sizeX*sizeZ] = 8;
    }

    //stair on top of structure
    map[1+5*sizeX+9*sizeX*sizeZ] = 5;

	/* for(a=0; a<sizeX; a++) {
		map[a + sizeX*(sizeZ-1)] = 1;
	} */
	
}


void drawMap_C(void){
	int i = 0;
    for(c=0; c<sizeY; c++){
        for(a=0; a<sizeX; a++){
            for(b=0; b<sizeZ; b++){
                x = midX+(a*12)-(b*12);
                y = midY+(b*6)+(a*6)-(c*15)+c;
                if(map[i] != 0xFF) gfx_TransparentSprite(blocks[map[i]], x, y);
				i++;
                //while (!os_GetCSC());
            }

        }
    }
}
