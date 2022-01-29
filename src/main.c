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
#include "isolibce.h"

/* Put your function prototypes here */
void generateMap(void);

/* Put all your globals here */


const gfx_sprite_t *blocks[] = {
    /* 000 */ NULL,
    /* 001 */ water_full,
    /* 002 */ water_surface,
    /* 003 */ glass_block,
    /* 004 */ glass_pane_east,
    /* 005 */ glass_pane_west,
    /* 006 */ NULL,
    /* 007 */ NULL,
    /* 008 */ NULL,
    /* 009 */ NULL,
    /* 010 */ NULL,
    /* 011 */ NULL,
    /* 012 */ NULL,
    /* 013 */ NULL,
    /* 014 */ NULL,
    /* 015 */ NULL,
    /* 016 */ stone_brick_stairs_east,
    /* 017 */ stone_brick_stairs_east_2,
    /* 018 */ stone_stairs_east,
    /* 019 */ brick_stairs_east,
    /* 020 */ NULL,
    /* 021 */ NULL,
    /* 022 */ NULL,
    /* 023 */ NULL,
    /* 024 */ NULL,
    /* 025 */ NULL,
    /* 026 */ NULL,
    /* 027 */ NULL,
    /* 028 */ NULL,
    /* 029 */ NULL,
    /* 030 */ NULL,
    /* 031 */ NULL,
    /* 032 */ stone_brick_stairs_west,
    /* 033 */ stone_brick_stairs_west_2,
    /* 034 */ stone_stairs_west,
    /* 035 */ brick_stairs_west,
    /* 036 */ NULL,
    /* 037 */ NULL,
    /* 038 */ NULL,
    /* 039 */ NULL,
    /* 040 */ NULL,
    /* 041 */ NULL,
    /* 042 */ NULL,
    /* 043 */ NULL,
    /* 044 */ NULL,
    /* 045 */ NULL,
    /* 046 */ NULL,
    /* 047 */ NULL,
    /* 048 */ NULL,
    /* 049 */ NULL,
    /* 050 */ NULL,
    /* 051 */ NULL,
    /* 052 */ NULL,
    /* 053 */ NULL,
    /* 054 */ NULL,
    /* 055 */ NULL,
    /* 056 */ NULL,
    /* 057 */ NULL,
    /* 058 */ NULL,
    /* 059 */ NULL,
    /* 060 */ NULL,
    /* 061 */ NULL,
    /* 062 */ NULL,
    /* 063 */ NULL,
    /* 064 */ stone,
    /* 065 */ grass_block,
    /* 066 */ coal_ore,
    /* 067 */ stone_brick,
    /* 068 */ stone_brick_2,
    /* 069 */ dirt, // haha funny number
    /* 070 */ brick,
};

#define AIR 0
#define WATER_FULL 1
#define WATER_SURFACE 2
#define GLASS_BLOCK 3
#define GLASS_PANE_EAST 4
#define GLASS_PANE_WEST 5

#define STONE_BRICK_STAIRS_EAST 16
#define STONE_BRICK_STAIRS_EAST_2 17
#define STONE_STAIRS_EAST 18
#define BRICK_STAIRS_EAST 19

#define STONE_BRICK_STAIRS_WEST 32
#define STONE_BRICK_STAIRS_WEST_2 33
#define STONE_STAIRS_WEST 34
#define BRICK_STAIRS_WEST 35

#define STONE 64
#define GRASS_BLOCK 65
#define COAL_ORE 66
#define STONE_BRICK 67
#define STONE_BRICK_2 68
#define DIRT 69
#define BRICK 70

int a, b, c, i, x, y;

const int midX = 160;
const int midY = 128;

const int sizeX = 8;
const int sizeZ = 8;
const int sizeY = 10;

const iso_config_t iso_config = {
	&blocks,  0,16, 16,16, 32,16
};

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

	iso_Init(&iso_config);

	// gfx_SetDraw(1);
	do {
		/* memset(&seed, 0x66, sizeof(seed));
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

		memset(map, 0, sizeof(map)); // air
		for (int i=0; i<sizeof(seed); i++) {
			int y = ((seed[i]>>3)&7)^(seed[i]&7);
			int z = (seed[i]>>3)&7;
			if (seed[i]&0x40) {
				//horizontal
				if (seed[i]&0x80) {
					// horizontal bar x
					for (int x=0; x<sizeX-(seed[i]&7); x++) {
						if (x&1) map[x + z*sizeX + y*sizeX*sizeZ] = STONE_BRICK;
						else     map[x + z*sizeX + y*sizeX*sizeZ] = STONE_BRICK_2;
					}
				} else {
					// horizontal bar z
					for (int x=0; x<sizeZ-(seed[i]&7); x++) {
						if (x&1) map[z + x*sizeX + y*sizeX*sizeZ] = STONE_BRICK;
						else     map[z + x*sizeX + y*sizeX*sizeZ] = STONE_BRICK_2;
					}
				}
			} else {
				if (seed[i]&0x80) {
					// column
					for (int x=0; x<sizeY; x++) {
						map[y + z*sizeX + x*sizeX*sizeZ] = BRICK;
					}
				}
				// nothing
			}
		} */

		memset(map, 0, sizeof(map)); // air
		generateMap();

		do {
			gfx_ZeroScreen();
			timer_Enable(1, TIMER_32K, TIMER_NOINT, TIMER_UP);
			timer_Set(1, 0);
			iso_DrawMap(map);
			time = timer_Get(1);
			timer_Disable(1);
			gfx_SetTextXY(0, 0);
			gfx_PrintInt(32768/time, 3);
			gfx_PrintString("fps");
			gfx_SwapDraw();
			iso_SwapDraw();
			key = os_GetCSC();
			gfx_Wait();
			if (key == sk_Enter) break;
		} while (key != sk_Clear);
	} while (key != sk_Clear);

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
                        map[x] = COAL_ORE; //coal ore
                    } else {
                        map[x] = STONE; //stone
                    }
                } else if(c==3){
                    map[x] = DIRT;
                } else if(c==4){
                    map[x] = DIRT;
                    if(!(a>0 && a<6 && b>0 && b<6)){
                        map[x] = GRASS_BLOCK;
                    }
                } else {
                    map[x] = AIR;
                }
            }
        }
    }

    //air blocks
    map[1+7*sizeX+4*sizeX*sizeZ] = AIR;
    map[4+7*sizeX+4*sizeX*sizeZ] = AIR;

    //water
    for(a=6; a<=7; a++){
        for(b=1; b<=7; b++){
            for(c=1; c<=4; c++){
				int x = a+b*sizeX+c*sizeX*sizeZ;
                if(c==4)
                    map[x] = WATER_SURFACE;
				else
					map[x] = WATER_FULL;
            }
        }
    }

    //floating water
    map[0+7*sizeX+8*sizeX*sizeZ] = WATER_FULL;

    //floating glass block, glass pane east, glass pane west
    map[7+0*sizeX+7*sizeX*sizeZ] = GLASS_BLOCK;
    map[7+0*sizeX+8*sizeX*sizeZ] = GLASS_PANE_EAST;
    map[7+0*sizeX+9*sizeX*sizeZ] = GLASS_PANE_WEST;


    //structure design

    //floor
    for(b=1; b<=5; b++){
        for(a=1; a<=5; a++){
			int x = a+b*sizeX+5*sizeX*sizeZ;
            if((a+b+5)%2==0){
                map[x] = STONE_BRICK_2;
            } else {
                map[x] = STONE_BRICK;
            }
        }
    }

    //stairs
    map[2+6*sizeX+5*sizeX*sizeZ] = STONE_BRICK_STAIRS_EAST;
    map[3+6*sizeX+5*sizeX*sizeZ] = STONE_BRICK_STAIRS_EAST_2;
    map[4+6*sizeX+5*sizeX*sizeZ] = STONE_BRICK_STAIRS_EAST;

    map[2+7*sizeX+4*sizeX*sizeZ] = STONE_BRICK_STAIRS_EAST;
    map[3+7*sizeX+4*sizeX*sizeZ] = STONE_BRICK_STAIRS_EAST_2;
    map[4+7*sizeX+4*sizeX*sizeZ] = STONE_BRICK_STAIRS_EAST;

    //pillars
    for(c=6; c<=9; c++){
        map[1+1*sizeX+c*sizeX*sizeZ] = STONE_BRICK;
        map[5+1*sizeX+c*sizeX*sizeZ] = STONE_BRICK;
        map[1+5*sizeX+c*sizeX*sizeZ] = STONE_BRICK;
    }

    //crossbeams
    map[4+1*sizeX+9*sizeX*sizeZ] = STONE_BRICK;
    map[3+1*sizeX+9*sizeX*sizeZ] = STONE_BRICK_2;
    map[2+1*sizeX+9*sizeX*sizeZ] = STONE_BRICK;
    map[1+2*sizeX+9*sizeX*sizeZ] = STONE_BRICK;
    map[1+3*sizeX+9*sizeX*sizeZ] = STONE_BRICK_2;
    map[1+4*sizeX+9*sizeX*sizeZ] = STONE_BRICK;

    //windows
    for(c=6; c<9; c++){
        map[4+1*sizeX+c*sizeX*sizeZ] = GLASS_PANE_EAST;
        map[3+1*sizeX+c*sizeX*sizeZ] = GLASS_PANE_EAST;
        map[2+1*sizeX+c*sizeX*sizeZ] = GLASS_PANE_EAST;

        map[1+2*sizeX+c*sizeX*sizeZ] = GLASS_PANE_WEST;
        map[1+3*sizeX+c*sizeX*sizeZ] = GLASS_PANE_WEST;
        map[1+4*sizeX+c*sizeX*sizeZ] = GLASS_PANE_WEST;
    }

    //stair on top of structure
    map[1+5*sizeX+9*sizeX*sizeZ] = STONE_BRICK_STAIRS_EAST;

	/* for(a=0; a<sizeX; a++) {
		map[a + sizeX*(sizeZ-1)] = 1;
	} */
	
}


/* void drawMap_C(void){
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
 */