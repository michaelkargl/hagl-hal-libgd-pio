#pragma once

#define RGB565_RED_MASK 0xFF0000
#define RGB565_GREEN_MASK 0x00FF00
#define RGB565_BLUE_MASK 0x0000FF

/**
 * @brief extracts the RED portion from an rgb565 color
 * @details An RGB565 color looks like this: 0xRRGGBB.
 *          We mask out the channel we need and use bit
 *          shifting to remove the excess 0's
 *          Example: 0xFF2233 => 0x0000FF => 0xFF
 * @param rgb565 An RGB565 color (0xRRGGBB)
 * @return (uint8_t) the RED portion of the RGB565 color
 */
#define RGB565_TO_RED(color_var) ((color_var & RGB565_RED_MASK) >> 16)

/**
 * @brief extracts the GREEN portion from an rgb565 color.
 *        An RGB565 color looks like this: 0xRRGGBB.
 *        We mask out the channel we need and use bit
 *        shifting to remove the excess 0's.
 *        Example: 0x11FF33 => 0x0000FF => 0xFF
 * @param rgb565 An RGB565 color (0xRRGGBB)
 * @return (uint8_t) the GREEN portion of the RGB565 color
 */
#define RGB565_TO_GREEN(color_var) ((color_var & RGB565_GREEN_MASK) >> 8)

/**
 * @brief extracts the BLUE portion from an rgb565 color.
 *        We mask out the channel we need and use bit
 *        shifting to remove the excess 0's.
 *        Example: 0x11FF33 => 0x0000FF => 0xFF
 * @param rgb565 An RGB565 color (0xRRGGBB)
 * @returns (uint8_t) the BLUE portion of the RGB565 color
 */
#define RGB565_TO_BLUE(color_var) ((color_var & RGB565_BLUE_MASK))

/**
 * @brief converts an 0xRRGGBB color to a gd color index.
 *        Do not deallocate this color after use or colors won't work.
 *        The term "allocate" is misleading since there is no memory
 *        being allocated here.
 * @returns (int): the gd color index
 */
#define RGB565_TO_GD(image_var, color_var) (gdImageColorResolve( \
    image_var,                                                   \
    RGB565_TO_RED(color_var),                                    \
    RGB565_TO_GREEN(color_var),                                  \
    RGB565_TO_BLUE(color_var)))

/**
 * @brief turns separate rgb channel values into an 0xRRGGBB value
 *        0x11,0x22,0x33 => 0x110000 | 0x002200 | 0x000033
 * @returns (uint32_t) the 24bit rgb565 value
 */
#define RGB_TO_RGB565(redVar, greenVar, blueVar) ( \
    (redVar << 16) | (greenVar << 8) | (blueVar))
