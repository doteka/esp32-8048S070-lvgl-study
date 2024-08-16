/*******************************************************************************
 * Size: 20 px
 * Bpp: 1
 * Opts: --bpp 1 --size 20 --no-compress --font 7segment.ttf --symbols 0123456789: --range 48-58 --format lvgl -o sevent_seg_font20.c
 ******************************************************************************/


#include "lvgl.h"
#include "seven_seg_font20.h"

#ifndef SEVENT_SEG_FONT20
#define SEVENT_SEG_FONT20 1
#endif

#if SEVENT_SEG_FONT20

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0030 "0" */
    0x7f, 0xbd, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x0,
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xfe,

    /* U+0031 "1" */
    0x7f, 0xfc, 0xff, 0xf8,

    /* U+0032 "2" */
    0x7f, 0x3f, 0x3, 0x3, 0x3, 0x3, 0x3d, 0x3c,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xb8, 0x7c,

    /* U+0033 "3" */
    0xfe, 0xfc, 0x18, 0x30, 0x60, 0xdf, 0xbd, 0x6,
    0xc, 0x18, 0x30, 0x6f, 0xff, 0x0,

    /* U+0034 "4" */
    0x83, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xfc, 0x7e,
    0x6, 0x6, 0x6, 0x6, 0x6, 0x2,

    /* U+0035 "5" */
    0x7d, 0x7b, 0x6, 0xc, 0x18, 0x3f, 0x3f, 0x6,
    0xc, 0x18, 0x30, 0x6f, 0xff, 0x0,

    /* U+0036 "6" */
    0x7e, 0xbe, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xff,
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xfe,

    /* U+0037 "7" */
    0xfe, 0xf4, 0x18, 0x30, 0x60, 0xc1, 0x80, 0x2,
    0xc, 0x18, 0x30, 0x60, 0xc1, 0x0,

    /* U+0038 "8" */
    0x7f, 0xbf, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xfd,
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xfe,

    /* U+0039 "9" */
    0x7c, 0xbf, 0xc3, 0xc3, 0xc3, 0xc3, 0xfc, 0x7e,
    0x6, 0x6, 0x6, 0x6, 0x6, 0x7e, 0xfa,

    /* U+003A ":" */
    0xf0, 0x3, 0xc0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 150, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 150, .box_w = 2, .box_h = 15, .ofs_x = 7, .ofs_y = 0},
    {.bitmap_index = 19, .adv_w = 150, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 34, .adv_w = 150, .box_w = 7, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 150, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 62, .adv_w = 150, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 76, .adv_w = 150, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 91, .adv_w = 150, .box_w = 7, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 150, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 120, .adv_w = 150, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 135, .adv_w = 56, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 3}
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
    .bpp = 1,
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

lv_font_t seven_seg_font20 = {

    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if SEVENT_SEG_FONT20*/

