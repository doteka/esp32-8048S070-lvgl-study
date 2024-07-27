// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.0
// LVGL version: 8.3.6
// Project name: SuntonESP32_example

#include "../ui.h"
#include <stdbool.h>
#include <stdio.h>
#include "esp_log.h"

#define DISPLAY_WIDTH 300
#define DISPLAY_HEIGHT 400
#define state_row 8
#define state_col 2
#define state_check(state) ((state)?"O":"X")

char *setup_option[] = {"Auto", "Timing", "Skip", "Win", "Lose", "Notion", "GWNU", "KWN"};
int setup_option_cnt = 8;
uint16_t checklist_state = 0b0010010;

void to_binary_string(char *str) {
    int len = setup_option_cnt;
    for(int i=0; i<len;i++) 
        str[i] = (checklist_state & (1 << i))?'1':'0';
    str[len] = '\0';
}

void change_option(lv_event_t *e) {
    ESP_LOGI("EVENT DEBUG","Event IN");
    lv_obj_t *obj = lv_event_get_target(e);
    lv_obj_t *label = lv_event_get_user_data(e);
    uint16_t col, row;
    lv_table_get_selected_cell(obj, &row, &col);
    if(col != 0) {
        checklist_state ^= (1 << row);
        lv_table_set_cell_value(obj, row, col, state_check(checklist_state & (1 << row)));
        char str[17];
        to_binary_string(str);
        lv_label_set_text(label, str);
    }
    ESP_LOGI("EVENT DEBUG","Selected cell: row = %d, col = %d", row, col);
}


void setup_set_Screen_screen_init(void)
{
    setup_set_Screen = lv_obj_create(NULL);
    lv_obj_clear_flag(setup_set_Screen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *option_table = lv_table_create(setup_set_Screen);
    lv_table_set_row_cnt(option_table, state_row);
    lv_table_set_col_cnt(option_table, state_col);
    lv_obj_set_width(option_table, DISPLAY_WIDTH);
    lv_obj_set_height(option_table, DISPLAY_HEIGHT);
    lv_obj_align(option_table, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(option_table, LV_OBJ_FLAG_CLICKABLE);

    char str[17];
    to_binary_string(str);

    lv_obj_t *label = lv_label_create(setup_set_Screen);
    lv_label_set_text(label, str);
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 0);

    for(int idx = 0; idx < setup_option_cnt; idx++) {
        lv_table_set_cell_value(option_table, idx, 0, setup_option[idx]);
        lv_table_set_cell_value(option_table, idx, 1, state_check(checklist_state & (1 << idx)));
    }
    lv_obj_add_event_cb(option_table, change_option, LV_EVENT_VALUE_CHANGED, label);
    
    
}