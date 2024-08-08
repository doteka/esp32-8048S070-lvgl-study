/*******************************************************************************
 * Size: 20 px
 * Bpp: 2
 * Opts: --bpp 2 --size 20 --no-compress --font Seven Segment.ttf --symbols 0123456789: --range 48-58 --format lvgl -o segment_font_20size.c
 ******************************************************************************/

#include "segment_font_20size.h"
#include "lvgl.h"

#ifndef SEGMENT_FONT_20SIZE
#define SEGMENT_FONT_20SIZE 1
#endif

#if SEGMENT_FONT_20SIZE

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0030 "0" */
    0x2f, 0xf8, 0x95, 0x56, 0xd0, 0x7, 0xd0, 0x7,
    0xd0, 0x7, 0xd0, 0x7, 0x40, 0x1, 0x40, 0x1,
    0xd0, 0x7, 0xd0, 0x7, 0xd0, 0x7, 0xd0, 0x7,
    0x95, 0x56, 0x2f, 0xf8,

    /* U+0031 "1" */
    0x9, 0xdd, 0xdd, 0xd4, 0x4d, 0xdd, 0xdd, 0x90,

    /* U+0032 "2" */
    0x2f, 0xf8, 0x5, 0x56, 0x0, 0x7, 0x0, 0x7,
    0x0, 0x7, 0x0, 0x7, 0x2f, 0xf8, 0x90, 0x0,
    0xd0, 0x0, 0xd0, 0x0, 0xd0, 0x0, 0xd0, 0x0,
    0x95, 0x50, 0x2f, 0xf8,

    /* U+0033 "3" */
    0xbf, 0xe0, 0x55, 0x60, 0x1, 0xc0, 0x7, 0x0,
    0x1c, 0x0, 0x7b, 0xfe, 0x0, 0x6, 0x0, 0x1c,
    0x0, 0x70, 0x1, 0xc0, 0x7, 0x15, 0x5a, 0xff,
    0x80,

    /* U+0034 "4" */
    0x0, 0x0, 0xd0, 0x7, 0xd0, 0x7, 0xd0, 0x7,
    0xd0, 0x7, 0xd0, 0x7, 0x90, 0x7, 0x2f, 0xf8,
    0x0, 0x6, 0x0, 0x7, 0x0, 0x7, 0x0, 0x7,
    0x0, 0x7, 0x0, 0x7, 0x0, 0x1,

    /* U+0035 "5" */
    0x2f, 0xf8, 0x95, 0x50, 0xd0, 0x0, 0xd0, 0x0,
    0xd0, 0x0, 0x90, 0x0, 0x2f, 0xf8, 0x0, 0x6,
    0x0, 0x7, 0x0, 0x7, 0x0, 0x7, 0x0, 0x7,
    0x5, 0x56, 0x2f, 0xf8,

    /* U+0036 "6" */
    0x2f, 0xf8, 0x95, 0x50, 0xd0, 0x0, 0xd0, 0x0,
    0xd0, 0x0, 0x90, 0x0, 0x2f, 0xf8, 0x90, 0x6,
    0xd0, 0x7, 0xd0, 0x7, 0xd0, 0x7, 0xd0, 0x7,
    0x95, 0x56, 0x2f, 0xf8,

    /* U+0037 "7" */
    0xbf, 0xe0, 0x55, 0x60, 0x1, 0xc0, 0x7, 0x0,
    0x1c, 0x0, 0x70, 0x0, 0x40, 0x1, 0x0, 0x1c,
    0x0, 0x70, 0x1, 0xc0, 0x7, 0x0, 0x1c, 0x0,
    0x20, 0x0, 0x0,

    /* U+0038 "8" */
    0x2f, 0xf8, 0x95, 0x56, 0xd0, 0x7, 0xd0, 0x7,
    0xd0, 0x7, 0x90, 0x7, 0x2f, 0xf8, 0x90, 0x6,
    0xd0, 0x7, 0xd0, 0x7, 0xd0, 0x7, 0xd0, 0x7,
    0x95, 0x56, 0x2f, 0xf8,

    /* U+0039 "9" */
    0x2f, 0xf8, 0x95, 0x56, 0xd0, 0x7, 0xd0, 0x7,
    0xd0, 0x7, 0x90, 0x7, 0x2f, 0xf8, 0x0, 0x6,
    0x0, 0x7, 0x0, 0x7, 0x0, 0x7, 0x0, 0x7,
    0x5, 0x56, 0x2f, 0xf8,

    /* U+003A ":" */
    0x49, 0x0, 0x99
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 161, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 28, .adv_w = 59, .box_w = 2, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 36, .adv_w = 161, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 64, .adv_w = 145, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 161, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 161, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 161, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 145, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 202, .adv_w = 161, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 230, .adv_w = 161, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 258, .adv_w = 59, .box_w = 2, .box_h = 6, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 48, .range_length = 11, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 2,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/

lv_font_t segment_font_20size = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -6,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if SEGMENT_FONT_20SIZE*/

