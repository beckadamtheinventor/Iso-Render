// convpng v7.2
#include <stdint.h>
#include "logo_gfx.h"

// 8 bpp image
uint8_t water_full_data[677] = {
 25,27,  // width,height
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x0C,0x41,0x00,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x23,0x0C,0x00,0x4D,0x23,0x00,0x1E,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x00,0x0C,0x0C,0x1E,0x0C,0x3C,0x0C,0x1E,0x0C,0x1E,0x00,0x06,0x06,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x06,0x06,0x00,0x23,0x0C,0x00,0x0C,0x0C,0x23,0x44,0x0C,0x00,0x0C,0x0C,0x0C,0x1E,0x1E,0x06,0x06,0x00,0x00,0x00,
 0x00,0x06,0x06,0x00,0x0C,0x0C,0x0C,0x0C,0x0C,0x1E,0x0C,0x1E,0x0C,0x0C,0x1E,0x0C,0x0C,0x0C,0x23,0x00,0x1E,0x1E,0x06,0x06,0x00,
 0x06,0x0C,0x00,0x23,0x0C,0x0C,0x40,0x0C,0x23,0x1E,0x0C,0x1E,0x44,0x1E,0x23,0x0C,0x23,0x0C,0x0C,0x1E,0x0C,0x0C,0x1E,0x00,0x06,
 0x06,0x06,0x06,0x0C,0x0C,0x00,0x0C,0x23,0x0C,0x0C,0x00,0x0C,0x40,0x23,0x0C,0x0C,0x0C,0x00,0x1E,0x0C,0x00,0x0C,0x06,0x06,0x06,
 0x06,0x10,0x10,0x06,0x06,0x0C,0x0C,0x0C,0x23,0x1E,0x0C,0x00,0x40,0x3C,0x0C,0x00,0x0C,0x0C,0x0C,0x0C,0x06,0x06,0x0D,0x2D,0x06,
 0x06,0x00,0x1D,0x1D,0x1D,0x06,0x06,0x0C,0x00,0x0C,0x0C,0x23,0x3C,0x0C,0x00,0x23,0x0C,0x0C,0x06,0x06,0x00,0x20,0x00,0x2D,0x06,
 0x06,0x10,0x10,0x00,0x10,0x00,0x26,0x06,0x06,0x0C,0x23,0x1E,0x4E,0x0C,0x0C,0x0C,0x06,0x06,0x0D,0x20,0x0D,0x0D,0x39,0x2D,0x06,
 0x06,0x26,0x10,0x10,0x26,0x10,0x10,0x10,0x1D,0x06,0x06,0x0C,0x41,0x00,0x06,0x06,0x0D,0x0D,0x2B,0x0D,0x20,0x00,0x0D,0x00,0x06,
 0x06,0x10,0x1D,0x00,0x1D,0x10,0x1D,0x00,0x10,0x10,0x26,0x06,0x06,0x06,0x0D,0x2B,0x0D,0x00,0x0D,0x0D,0x42,0x42,0x0D,0x2D,0x06,
 0x06,0x26,0x10,0x10,0x1D,0x00,0x10,0x10,0x10,0x1D,0x10,0x32,0x06,0x20,0x0D,0x00,0x0D,0x20,0x2B,0x0D,0x0D,0x00,0x20,0x49,0x06,
 0x06,0x1D,0x00,0x1D,0x10,0x26,0x1D,0x26,0x10,0x00,0x10,0x32,0x06,0x0D,0x2B,0x20,0x0D,0x0D,0x20,0x0D,0x42,0x0D,0x2B,0x2D,0x06,
 0x06,0x10,0x10,0x10,0x10,0x38,0x10,0x10,0x1D,0x38,0x3D,0x00,0x06,0x20,0x00,0x36,0x0D,0x20,0x20,0x0D,0x00,0x0D,0x0D,0x2D,0x06,
 0x06,0x00,0x1D,0x10,0x00,0x10,0x10,0x1D,0x00,0x10,0x00,0x45,0x06,0x4C,0x0D,0x20,0x00,0x39,0x20,0x36,0x0D,0x2B,0x0D,0x2D,0x06,
 0x06,0x10,0x26,0x1D,0x10,0x38,0x00,0x37,0x37,0x3E,0x37,0x32,0x06,0x0D,0x0D,0x0D,0x0D,0x0D,0x36,0x00,0x39,0x0D,0x0D,0x00,0x06,
 0x06,0x26,0x26,0x38,0x1D,0x00,0x46,0x3E,0x10,0x10,0x26,0x32,0x06,0x00,0x20,0x0D,0x0D,0x00,0x0D,0x0D,0x0D,0x36,0x20,0x2D,0x06,
 0x06,0x1D,0x00,0x3E,0x46,0x3D,0x10,0x10,0x10,0x00,0x10,0x00,0x06,0x20,0x0D,0x0D,0x0D,0x0D,0x0D,0x2B,0x0D,0x00,0x20,0x49,0x06,
 0x06,0x26,0x10,0x1D,0x10,0x1D,0x3D,0x1D,0x10,0x1D,0x10,0x32,0x06,0x0D,0x0D,0x00,0x2B,0x0D,0x00,0x0D,0x20,0x0D,0x39,0x2D,0x06,
 0x00,0x06,0x06,0x10,0x00,0x10,0x26,0x00,0x10,0x10,0x10,0x45,0x06,0x0D,0x0D,0x0D,0x0D,0x0D,0x0D,0x20,0x00,0x0D,0x06,0x06,0x00,
 0x00,0x00,0x00,0x06,0x06,0x10,0x10,0x10,0x26,0x1D,0x10,0x32,0x06,0x2B,0x0D,0x2B,0x0D,0x0D,0x2B,0x0D,0x06,0x06,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x10,0x00,0x10,0x37,0x00,0x06,0x0D,0x0D,0x0D,0x00,0x0D,0x06,0x06,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x10,0x10,0x32,0x06,0x00,0x20,0x0D,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x00,0x06,0x0D,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
