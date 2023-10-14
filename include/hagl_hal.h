/*

MIT License

Copyright (c) 2018-2021 Mika Tuupola

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

-cut-

This file is part of the Softraster HAL for the HAGL graphics library:
https://gitlab.com/ohsnaparts/osasoftworks/zube/softraster-hagl

SPDX-License-Identifier: MIT
*/


#ifndef _HAGL_SOFTRASTER_HAL_H
#define _HAGL_SOFTRASTER_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stddef.h"

/* This condition only makes development easier by getting rid of 
   potential reference error. Here you can mock temporarily mock 
   dependencies supplied by HAGL. `_HAGL_H` is set by HAGL. */
#ifdef _HAGL_H
#include <bitmap.h>
#else
// define mocked values here to get rid of design time synthax errors
#define mock_bitmap_t uint8_t
#define bitmap_t mock_bitmap_t
#endif


/** HAL must provide typedef for colors. This HAL uses RGB888. */
typedef uint32_t color_t;

/* HAL must provide display dimensions and depth. This HAL */
/* defaults to 320x240. Alternative dimensios can be passed */
/* using compiler flags. */
#ifndef DISPLAY_WIDTH
#define DISPLAY_WIDTH   (320)
#endif
#ifndef DISPLAY_HEIGHT
#define DISPLAY_HEIGHT  (240)
#endif
#define DISPLAY_DEPTH   (24)

/* These are t e optional features this HAL provides. These tell HAGL that we
   are providing certain features. HAGL is then able to call into and rely on our
   functions. Check out the `hagl.c` and `hagl.h` files. They make everything much clearer.*/
#define HAGL_HAS_HAL_INIT
#define HAGL_HAS_HAL_FLUSH
#define HAGL_HAS_HAL_CLOSE
#define HAGL_HAS_HAL_COLOR

/**
 * @brief Initialize the HAL
 *
 * Initialises all hardware and possible memory buffers needed
 * to draw and display an image. If HAL uses double or triple
 * buffering should return a pointer to current back buffer.
 *
 * @return pointer to bitmap_t or NULL
 */
bitmap_t *hagl_hal_init(void);


/**
 * @brief Output the image
 *
 * This is used for HAL implementations which do not display
 * the drawn pixels automatically. Call this function always when
 * you have finished rendering.
 * 
 * This HAL renders the softraster display to standard out.
 *
 * @return number of bytes written
 */
size_t hagl_hal_flush();


/**
 * @brief Close and clean up the HAL
 *
 * This is used for HAL implementations which need some cleanup, such
 * as deallocating memory, to be done when closing the program.
 */
void hagl_hal_close();


/**
 * @brief Draw a single pixel
 *
 * This is the only mandatory function HAL must provide.
 *
 * @param x X coordinate
 * @param y Y coorginate
 * @param color color
 */
void hagl_hal_put_pixel(int16_t x, int16_t y, color_t color);

/**
 * @brief Convert RGB to HAL color type
 *
 * This is used for HAL implementations which use some other pixel
 * format than RGB565.
 * 
 * This implementation converts RGB565 to RGB888
 */
static inline color_t hagl_hal_color(uint8_t r, uint8_t g, uint8_t b) {
    return (r << 16) | (g << 8) | (b);
};


#ifdef __cplusplus
}
#endif

#endif /* _HAGL_SOFTRASTER_HAL_H */