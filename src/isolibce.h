
#ifndef __ISOLIBCE_H__
#define __ISOLIBCE_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct __iso_config_t {
/* Array of block sprites. They must all be 25x27 pixels in size. */
	gfx_sprite_t *blocks;
/* First block ID considered to be partially transparent */
	uint8_t   first_semisolid;
/* Number of block IDs considered to be partially transparent following (and including) the first semisolid */
	uint8_t   num_semisolids;
/* First block ID considered to be partially transparent when the East face is viewed */
	uint8_t   first_east_semisolid;
/* Number of block IDs considered to be partially transparent when the East face is viewed following (and including) the first semisolid */
	uint8_t   num_east_semisolids;
/* First block ID considered to be partially transparent when the West face is viewed */
	uint8_t   first_west_semisolid;
/* Number of block IDs considered to be partially transparent when the West face is viewed following (and including) the first semisolid */
	uint8_t   num_west_semisolids;
} iso_config_t;

/**
 * Initializes the library.
 * @param config Pointer to configuration structure.
 * @return true if success.
 * @note currently always returns true. This might change in the future.
 */
bool iso_Init(iso_config_t *config);

/**
 * Draws a 16x16x16 block area isometrically.
 * @param map 4096 byte buffer containing block IDs to be drawn.
 * @return true if success, false if iso_Init hasn't been called yet.
 */
bool iso_DrawMap(uint8_t *map);

/**
 * Swaps the draw buffer used by the library.
 * @return Pointer to new draw buffer.
 */
void *iso_SwapDraw(void);

/**
 * Sets the draw buffer used by the library.
 * @param location 0 for vram, otherwise buffer.
 * @return Pointer to new draw buffer.
 */
void *iso_SetDraw(uint8_t location);

#endif
