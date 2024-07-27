// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.0
// LVGL version: 8.3.6
// Project name: SuntonESP32_example

#ifndef _SUNTONESP32_EXAMPLE_UI_H
#define _SUNTONESP32_EXAMPLE_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#include "ui_events.h"
#include "ui_helpers.h"
// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
void ui_Screen2_screen_init(void);
void modal_Screen_screen_init(void);
void setup_set_Screen_screen_init(void);
void tabview_setup_Screen_screen_init(void);
void tabview_grid_Screen_init(void);
void simple_card_game_init(void);

extern lv_obj_t *ui_Screen1;
extern lv_obj_t *ui_Screen2;

extern lv_obj_t *ui_Button2;
extern lv_obj_t *ui_Button1;
extern lv_obj_t *ui_Button4;
extern lv_obj_t *ui_Button3;
extern lv_obj_t *ui_Button6;
extern lv_obj_t *ui____initial_actions0;

extern lv_obj_t *modal_Screen;
extern lv_obj_t *state_tabel;
extern lv_obj_t *open_modal_btn;
// extern lv_obj_t *ui_Screen2;
// extern lv_obj_t *label_title;
// extern lv_obj_t *label_desc;
// extern lv_obj_t *label_grad_dsc;
// extern lv_obj_t *ui_submit;

extern lv_obj_t *setup_set_Screen;
extern lv_obj_t *tabview_setup_Screen;
extern lv_obj_t *tabview_grid_Screen;
extern lv_obj_t *simple_card_game_Screen;

void ui_init(lv_disp_t *);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif