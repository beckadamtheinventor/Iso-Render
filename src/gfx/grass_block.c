// convpng v7.2
#include <stdint.h>
#include "logo_gfx.h"

// 8 bpp image
uint8_t grass_block_data[677] = {
 25,27,  // width,height
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x18,0x1A,0x1A,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x30,0x18,0x18,0x18,0x3A,0x18,0x1A,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x18,0x18,0x33,0x3A,0x1A,0x18,0x1A,0x1A,0x18,0x30,0x33,0x06,0x06,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x06,0x06,0x1A,0x18,0x1A,0x1A,0x1A,0x18,0x51,0x33,0x18,0x18,0x3A,0x1A,0x18,0x1A,0x18,0x06,0x06,0x00,0x00,0x00,
 0x00,0x06,0x06,0x18,0x18,0x18,0x1A,0x33,0x30,0x18,0x1A,0x18,0x18,0x18,0x33,0x4F,0x1A,0x18,0x33,0x1A,0x18,0x30,0x06,0x06,0x00,
 0x06,0x47,0x1A,0x1A,0x47,0x18,0x18,0x18,0x51,0x18,0x18,0x18,0x30,0x1A,0x18,0x1A,0x18,0x1A,0x30,0x1A,0x30,0x1A,0x18,0x31,0x06,
 0x06,0x06,0x06,0x18,0x1A,0x1A,0x33,0x1A,0x18,0x47,0x1A,0x18,0x18,0x18,0x18,0x4F,0x1A,0x18,0x1A,0x18,0x1A,0x3F,0x06,0x06,0x06,
 0x06,0x4B,0x18,0x06,0x06,0x18,0x1A,0x18,0x30,0x18,0x18,0x3A,0x18,0x3A,0x18,0x3A,0x1A,0x1A,0x18,0x1A,0x06,0x06,0x33,0x18,0x06,
 0x06,0x1A,0x1A,0x18,0x4B,0x06,0x06,0x18,0x1A,0x3A,0x1A,0x3A,0x1A,0x18,0x30,0x1A,0x18,0x3F,0x06,0x06,0x1A,0x18,0x3B,0x18,0x06,
 0x06,0x18,0x18,0x1A,0x18,0x47,0x1A,0x06,0x06,0x3A,0x1A,0x1A,0x18,0x33,0x1A,0x31,0x06,0x06,0x4A,0x3B,0x18,0x4A,0x1A,0x33,0x06,
 0x06,0x31,0x13,0x1A,0x18,0x18,0x1A,0x18,0x1A,0x06,0x06,0x18,0x1A,0x1A,0x06,0x06,0x3B,0x4A,0x1A,0x1A,0x30,0x3B,0x0E,0x31,0x06,
 0x06,0x11,0x13,0x3F,0x31,0x18,0x18,0x1A,0x18,0x4B,0x18,0x06,0x06,0x06,0x1A,0x53,0x1A,0x30,0x3B,0x1A,0x3F,0x31,0x0E,0x17,0x06,
 0x06,0x2A,0x11,0x11,0x13,0x31,0x3F,0x18,0x33,0x18,0x30,0x18,0x06,0x3B,0x30,0x1A,0x1A,0x1A,0x0E,0x31,0x29,0x17,0x0E,0x17,0x06,
 0x06,0x13,0x13,0x11,0x2A,0x13,0x2F,0x31,0x3F,0x13,0x18,0x18,0x06,0x1A,0x1A,0x30,0x31,0x31,0x17,0x0E,0x0E,0x0E,0x0E,0x17,0x06,
 0x06,0x2A,0x11,0x13,0x13,0x11,0x13,0x13,0x2A,0x13,0x31,0x18,0x06,0x3B,0x31,0x17,0x0E,0x0E,0x17,0x0E,0x17,0x0E,0x17,0x29,0x06,
 0x06,0x13,0x11,0x11,0x13,0x13,0x11,0x13,0x11,0x11,0x11,0x31,0x06,0x17,0x0E,0x17,0x0E,0x17,0x0E,0x0E,0x0E,0x17,0x0E,0x17,0x06,
 0x06,0x11,0x2A,0x2F,0x13,0x11,0x13,0x2A,0x13,0x2A,0x11,0x11,0x06,0x17,0x2E,0x0E,0x0E,0x29,0x2E,0x0E,0x0E,0x29,0x17,0x17,0x06,
 0x06,0x13,0x13,0x11,0x11,0x11,0x13,0x13,0x13,0x13,0x13,0x11,0x06,0x0E,0x0E,0x0E,0x17,0x0E,0x0E,0x29,0x0E,0x17,0x0E,0x29,0x06,
 0x06,0x11,0x13,0x2F,0x11,0x13,0x11,0x13,0x2F,0x13,0x11,0x11,0x06,0x17,0x2E,0x2E,0x0E,0x17,0x2E,0x0E,0x0E,0x0E,0x17,0x29,0x06,
 0x06,0x2F,0x13,0x11,0x11,0x11,0x11,0x13,0x13,0x11,0x13,0x2A,0x06,0x0E,0x29,0x0E,0x0E,0x0E,0x0E,0x0E,0x17,0x0E,0x17,0x17,0x06,
 0x00,0x06,0x06,0x13,0x11,0x11,0x13,0x13,0x11,0x11,0x11,0x11,0x06,0x0E,0x17,0x0E,0x2E,0x17,0x17,0x17,0x0E,0x29,0x06,0x06,0x00,
 0x00,0x00,0x00,0x06,0x06,0x13,0x13,0x11,0x13,0x11,0x2F,0x11,0x06,0x17,0x0E,0x0E,0x0E,0x17,0x0E,0x0E,0x06,0x06,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x13,0x13,0x13,0x11,0x11,0x06,0x0E,0x17,0x2E,0x0E,0x0E,0x06,0x06,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x11,0x13,0x2A,0x06,0x0E,0x0E,0x29,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x11,0x06,0x17,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
