#include "libgd_hagl_hal.h"
#include "stdio.h"
#include "stdbool.h"
#include "gd.h"
#include "color_util.h"
#include "stdio.h"

static gdImagePtr image;

static void export_bmp(const char *filename, bool compression_enabled)
{
    FILE *out = fopen(filename, "wb");
    gdImageBmp(image, out, compression_enabled);
    fclose(out);
}

bitmap_t *hagl_hal_init(void)
{
    image = gdImageCreate(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    return NULL;
}

size_t hagl_hal_flush()
{
    export_bmp("./hagl.bmp", true);
    return 0;
}

void hagl_hal_close()
{
    hagl_hal_flush();
    gdImageDestroy(image);
}

void hagl_hal_put_pixel(int16_t positionX, int16_t positionY, color_t color)
{
    // printf("Drawing pixel...\n");
    int gd_color = RGB565_TO_GD(image, color);
    gdImageSetPixel(image, positionX, positionY, gd_color);    
}
