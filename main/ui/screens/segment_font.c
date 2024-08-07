/*******************************************************************************
 * Size: 16 px
 * Bpp: 4
 * Opts: --bpp 4 --size 16 --lcd --font Seven Segment.ttf --range 48-58 --format lvgl -o segment_font.c
 ******************************************************************************/

// #ifdef LV_LVGL_H_INCLUDE_SIMPLE
// #include "lvgl.h"
// #else
// #include "lvgl/lvgl.h"
// #endif
#include "lvgl.h"
#include "segment_font.h"

#ifndef SEGMENT_FONT
#define SEGMENT_FONT 1
#endif

#if SEGMENT_FONT

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0030 "0" */
    0x0, 0xc4, 0xd7, 0xff, 0xfe, 0xb6, 0x20, 0xf,
    0x2d, 0x67, 0xff, 0xff, 0x2, 0x3f, 0x2d, 0x40,
    0x38, 0x44, 0x62, 0x1, 0xfe, 0x70, 0x17, 0x31,
    0x0, 0xff, 0xe8, 0x8, 0x8c, 0x40, 0x3f, 0xce,
    0x2, 0xe6, 0x20, 0x12, 0xde, 0x42, 0x0, 0x7f,
    0x8e, 0x32, 0x54, 0x3, 0x2d, 0xe4, 0x20, 0x7,
    0xf8, 0xe3, 0x25, 0x40, 0x38, 0x44, 0x62, 0x1,
    0xfe, 0x70, 0x17, 0x31, 0x0, 0xff, 0xe8, 0x8,
    0x8c, 0x40, 0x3f, 0xce, 0x2, 0xe6, 0x20, 0x12,
    0xde, 0x7f, 0xff, 0xf0, 0x23, 0xf2, 0x94, 0x0,

    /* U+0031 "1" */
    0x0, 0xff, 0x8e, 0x72, 0xc, 0x3, 0x31, 0x19,
    0x30, 0x7, 0xff, 0x28, 0x46, 0x31, 0x0, 0xc9,
    0x19, 0x8, 0x1, 0x96, 0x36, 0xd0, 0x3, 0x84,
    0x0, 0x20, 0x1f, 0xfc, 0xa6, 0x34, 0x26, 0x0,
    0x0,

    /* U+0032 "2" */
    0x0, 0xc2, 0xb7, 0xff, 0xfe, 0xb6, 0x20, 0xf,
    0xc2, 0xb7, 0xff, 0xfe, 0x8f, 0xcb, 0x50, 0xf,
    0xfe, 0x3b, 0x80, 0xb9, 0x88, 0x7, 0xff, 0x79,
    0xc0, 0x5c, 0xc4, 0x3, 0x89, 0xaf, 0xff, 0xfd,
    0x1f, 0x94, 0xa0, 0x19, 0x6b, 0x3f, 0xff, 0xf8,
    0x16, 0xc4, 0x20, 0x1e, 0x11, 0x18, 0x80, 0x7f,
    0xf8, 0x4, 0x46, 0x20, 0x1f, 0xfc, 0x75, 0xbc,
    0xff, 0xff, 0xe0, 0x5b, 0x8, 0x6,

    /* U+0033 "3" */
    0x0, 0x13, 0xe7, 0xff, 0xf7, 0x4a, 0x88, 0x7,
    0x13, 0xe7, 0xff, 0xf7, 0x67, 0xfa, 0x50, 0x3,
    0xff, 0x88, 0x62, 0x23, 0x10, 0xf, 0xfe, 0xc9,
    0x88, 0x8c, 0x40, 0x22, 0x7c, 0xff, 0xfe, 0xef,
    0xcc, 0x42, 0x0, 0x44, 0xf9, 0xff, 0xfd, 0xdf,
    0x98, 0x84, 0x0, 0xff, 0xe2, 0x18, 0x88, 0xc4,
    0x3, 0xff, 0xb2, 0x62, 0x23, 0x10, 0x8, 0x9f,
    0x3f, 0xff, 0xbb, 0x3f, 0xd2, 0x80,

    /* U+0034 "4" */
    0x0, 0x1c, 0xe4, 0x18, 0x7, 0xf8, 0x9e, 0xe5,
    0x0, 0x33, 0x11, 0x93, 0x0, 0x7f, 0x9b, 0x91,
    0x48, 0x40, 0x3f, 0xfd, 0x2, 0x23, 0x10, 0xf,
    0xf3, 0x80, 0xb9, 0x88, 0x4, 0xb7, 0x9f, 0xff,
    0xfc, 0x8, 0xed, 0x95, 0x0, 0xe1, 0x26, 0xbf,
    0xff, 0xf4, 0x76, 0xca, 0x80, 0x7f, 0xf1, 0xdc,
    0x5, 0xcc, 0x40, 0x3f, 0xfe, 0xcd, 0xc8, 0xa4,
    0x20,

    /* U+0035 "5" */
    0x0, 0xc4, 0xd7, 0xff, 0xfe, 0xb6, 0x10, 0xf,
    0x2d, 0x67, 0xff, 0xff, 0x2, 0xd8, 0x40, 0x3e,
    0x11, 0x18, 0x80, 0x7f, 0xf8, 0x4, 0x46, 0x20,
    0x1f, 0xfc, 0x75, 0xbc, 0xff, 0xff, 0xe0, 0x5b,
    0x10, 0x7, 0xc2, 0x4d, 0x7f, 0xff, 0xe8, 0xfc,
    0xb5, 0x0, 0xff, 0xe3, 0xb8, 0xb, 0x98, 0x80,
    0x7f, 0xf7, 0x9c, 0x5, 0xcc, 0x40, 0x38, 0x56,
    0xff, 0xff, 0xd1, 0xf9, 0x4a, 0x0,

    /* U+0036 "6" */
    0x0, 0xc4, 0xd7, 0xff, 0xfe, 0xb6, 0x10, 0xf,
    0x2d, 0x67, 0xff, 0xff, 0x2, 0xd8, 0x40, 0x3e,
    0x11, 0x18, 0x80, 0x7f, 0xf8, 0x4, 0x46, 0x20,
    0x1f, 0xfc, 0x75, 0xbd, 0xef, 0xff, 0xfa, 0xd8,
    0x80, 0x3c, 0xb7, 0xbd, 0xff, 0xff, 0x47, 0xe5,
    0xa8, 0x7, 0x8, 0x8c, 0x40, 0x3f, 0xce, 0x2,
    0xe6, 0x20, 0x1f, 0xfd, 0x1, 0x11, 0x88, 0x7,
    0xf9, 0xc0, 0x5c, 0xc4, 0x2, 0x5b, 0xcf, 0xff,
    0xfe, 0x4, 0x7e, 0x52, 0x80, 0x0,

    /* U+0037 "7" */
    0x0, 0x13, 0xe7, 0xff, 0xf7, 0x4a, 0x88, 0x7,
    0x13, 0xe7, 0xff, 0xf7, 0x67, 0xfa, 0x50, 0x3,
    0xff, 0x88, 0x62, 0x23, 0x10, 0xf, 0xfe, 0xc9,
    0x88, 0x8c, 0x40, 0x3f, 0xf8, 0x8b, 0x79, 0x8,
    0x1, 0xff, 0xc4, 0x5b, 0xc8, 0x40, 0xf, 0xfe,
    0x21, 0x88, 0x8c, 0x40, 0x3f, 0xfd, 0xc4, 0x43,
    0x26, 0x0,

    /* U+0038 "8" */
    0x0, 0xc4, 0xd7, 0xff, 0xfe, 0xb6, 0x20, 0xf,
    0x2d, 0x67, 0xff, 0xff, 0x2, 0x3f, 0x2d, 0x40,
    0x38, 0x44, 0x62, 0x1, 0xfe, 0x70, 0x17, 0x31,
    0x0, 0xff, 0xe8, 0x8, 0x8c, 0x40, 0x3f, 0xce,
    0x2, 0xe6, 0x20, 0x12, 0xde, 0xf7, 0xff, 0xfd,
    0x1d, 0xb2, 0xa0, 0x19, 0x6f, 0x7b, 0xff, 0xfe,
    0x8e, 0xd9, 0x50, 0xe, 0x11, 0x18, 0x80, 0x7f,
    0x9c, 0x5, 0xcc, 0x40, 0x3f, 0xfa, 0x2, 0x23,
    0x10, 0xf, 0xf3, 0x80, 0xb9, 0x88, 0x4, 0xb7,
    0x9f, 0xff, 0xfc, 0x8, 0xfc, 0xa5, 0x0, 0x0,

    /* U+0039 "9" */
    0x0, 0xc4, 0xd7, 0xff, 0xfe, 0xb6, 0x20, 0xf,
    0x2d, 0x67, 0xff, 0xff, 0x2, 0x3f, 0x2d, 0x40,
    0x38, 0x44, 0x62, 0x1, 0xfe, 0x70, 0x17, 0x31,
    0x0, 0xff, 0xe8, 0x8, 0x8c, 0x40, 0x3f, 0xce,
    0x2, 0xe6, 0x20, 0x12, 0xde, 0x7f, 0xff, 0xf0,
    0x23, 0xb6, 0x54, 0x3, 0x84, 0x9a, 0xff, 0xff,
    0xd1, 0xdb, 0x2a, 0x1, 0xff, 0xc7, 0x70, 0x17,
    0x31, 0x0, 0xff, 0xef, 0x38, 0xb, 0x98, 0x80,
    0x70, 0xad, 0xff, 0xff, 0xa3, 0xf2, 0x94, 0x0,

    /* U+003A ":" */
    0x0, 0x9, 0xa1, 0x80, 0x71, 0x5f, 0xa1, 0x80,
    0x63, 0x8b, 0x73, 0x0, 0xc2, 0x68, 0x60, 0x1c,
    0x57, 0xf6, 0x60, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 129, .box_w = 24, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 47, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 113, .adv_w = 129, .box_w = 24, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 116, .box_w = 21, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 237, .adv_w = 129, .box_w = 24, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 294, .adv_w = 129, .box_w = 24, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 356, .adv_w = 129, .box_w = 24, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 426, .adv_w = 116, .box_w = 21, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 476, .adv_w = 129, .box_w = 24, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 556, .adv_w = 129, .box_w = 24, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 628, .adv_w = 47, .box_w = 9, .box_h = 5, .ofs_x = 0, .ofs_y = 0}
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
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 1,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t segment_font = {
#else
lv_font_t segment_font = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 12,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_HOR,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -5,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if SEGMENT_FONT*/
