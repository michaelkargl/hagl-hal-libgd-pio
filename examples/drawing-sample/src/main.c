#include "hagl.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "font5x7.h"

#define FONT_CHAR_WIDTH 5
#define FONT_CHAR_HEIGHT 7

#if DISPLAY_WIDTH < DISPLAY_HEIGHT
#define MIN_DISPLAY_SIZE DISPLAY_WIDTH
#define MAX_DISPLAY_SIZE DISPLAY_HEIGHT
#else
#define MIN_DISPLAY_SIZE DISPLAY_HEIGHT
#define MAX_DISPLAY_SIZE DISPLAY_WIDTH
#endif

#define RANDOM_INT32 rand()
#define RANDOM(min, max) (min + (RANDOM_INT32 % (max - min)))
#define RANDOM_WCHAR ((wchar_t)(sizeof(wchar_t)))
#define RANDOM_CHAR ((char)RANDOM_INT32)
#define RANDOM_COLOR RANDOM(0, 0xFFFFFF)
#define RANDOM_X RANDOM(0, DISPLAY_WIDTH)
#define RANDOM_Y RANDOM(0, DISPLAY_HEIGHT)
#define RANDOM_SIZE RANDOM(1, MIN_DISPLAY_SIZE)
#define RANDOM_FONT_SCALE (RANDOM(100, MAX_DISPLAY_SIZE) / 100.0)
#define RANDOM_BORDER_RADIUS RANDOM(10, 30)

#define FILLED_COUNT RANDOM(1, 2)
#define HOLLOW_COUNT RANDOM(1, 3)
#define CHARACTER_COUNT RANDOM(20, MIN_DISPLAY_SIZE/100)


static bitmap_t font_glyph;

static void initialize() {

    // seed rand with current time
    srand((unsigned int)time(NULL));

    font_glyph.buffer = (uint8_t *)malloc(FONT_CHAR_WIDTH * FONT_CHAR_HEIGHT * sizeof(color_t));
    hagl_init();
}


static void draw_filled_elements(const uint32_t count)
{
    for (uint32_t i = 0; i < count; i++)
    {
        hagl_fill_circle(RANDOM_X, RANDOM_Y, RANDOM_SIZE, RANDOM_COLOR);
        hagl_fill_ellipse(RANDOM_X, RANDOM_Y, RANDOM_SIZE, RANDOM_SIZE, RANDOM_COLOR);
        hagl_fill_rectangle(RANDOM_X, RANDOM_Y, RANDOM_X, RANDOM_Y, RANDOM_COLOR);
        hagl_fill_rounded_rectangle(RANDOM_X, RANDOM_Y, RANDOM_X, RANDOM_Y, RANDOM_BORDER_RADIUS, RANDOM_COLOR);
        hagl_fill_triangle(RANDOM_X, RANDOM_Y, RANDOM_X, RANDOM_Y, RANDOM_X, RANDOM_Y, RANDOM_COLOR);
    }
}


static void draw_scaled_character(uint16_t pos_x, uint16_t pos_y, float scale) {
    const uint16_t glyph_width = FONT_CHAR_WIDTH * scale;
    const uint16_t glyph_height = FONT_CHAR_HEIGHT * scale;
    
    hagl_get_glyph(RANDOM_CHAR, RANDOM_COLOR, &font_glyph, font5x7);
    hagl_scale_blit(pos_x, pos_y, glyph_width, glyph_height, &font_glyph);
}

static void draw_characters(const uint32_t count)
{
    for (uint32_t i = 0; i < count; i++)
    {
        hagl_put_char(RANDOM_CHAR, RANDOM_X, RANDOM_Y, 0xFFFFFF, font5x7);
        hagl_put_text((wchar_t[]){
                          RANDOM_CHAR,
                          RANDOM_CHAR,
                          RANDOM_CHAR,
                          RANDOM_CHAR,
                          RANDOM_CHAR,
                          RANDOM_CHAR},
                      RANDOM_X, RANDOM_Y, RANDOM_COLOR, font5x7);
        draw_scaled_character(RANDOM_X, RANDOM_Y, RANDOM_FONT_SCALE);
    }
}

static void draw_hollow_elements(const uint32_t count)
{
    for (uint32_t i = 0; i < count; i++)
    {
        hagl_draw_line(RANDOM_X, RANDOM_Y, RANDOM_X, RANDOM_Y, RANDOM_COLOR);
        hagl_draw_circle(RANDOM_X, RANDOM_Y, RANDOM_SIZE, RANDOM_COLOR);
        hagl_draw_hline(RANDOM_X, RANDOM_Y, RANDOM_SIZE, RANDOM_COLOR);
        hagl_draw_vline(RANDOM_X, RANDOM_Y, RANDOM_SIZE, RANDOM_COLOR);
        hagl_draw_ellipse(RANDOM_X, RANDOM_Y, RANDOM_SIZE, RANDOM_SIZE, RANDOM_COLOR);
        hagl_draw_rectangle(RANDOM_X, RANDOM_Y, RANDOM_X, RANDOM_Y, RANDOM_COLOR);
        hagl_draw_rounded_rectangle(RANDOM_X, RANDOM_Y, RANDOM_X, RANDOM_Y, RANDOM_BORDER_RADIUS, RANDOM_COLOR);
        hagl_draw_triangle(RANDOM_X, RANDOM_Y, RANDOM_X, RANDOM_Y, RANDOM_X, RANDOM_Y, RANDOM_COLOR);
    }
}

int main()
{
    initialize();
    draw_filled_elements(FILLED_COUNT);
    draw_hollow_elements(HOLLOW_COUNT);
    draw_characters(CHARACTER_COUNT);

    hagl_close();
    return 0;
}
