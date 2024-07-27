#include <stdio.h>
#include <stdbool.h>
#include "../ui.h"
#include "esp_log.h"

#define TABLE_ROW 10
#define TALBE_COL 2

#define TABLE_WIDTH 300
#define TABLE_HEIGHT 400

#define STATE_TO_STRING(bit) ((bit) ? "O" : "X")


void slider_event_cb(lv_event_t *e);


char slider_value[3][10];
lv_obj_t *slider_labels[3];
uint16_t state_array[] = {0b0000000000, 0b0000000000, 0b0000000000};
char *state_title[3][10] = {{"Auto1", "Auto2", "Auto3", "Auto4", "Auto5", "Auto6", "Auto7", "Auto8", "Auto9", "Auto10"},
                          {"Lab1", "Lab2", "Lab3", "Lab4", "Lab5", "Lab6", "Lab7", "Lab8", "Lab9", "Lab10"}, 
                          {"Home1", "Home2", "Home3", "Home4", "Home5", "Home6", "Home7", "Home8", "Home9", "Home10"}};

void event_state_change(lv_event_t *e) {
    lv_obj_t *obj = lv_event_get_target(e);
    int idx = (int)(uintptr_t)lv_event_get_user_data(e);

    uint16_t col, row;
    lv_table_get_selected_cell(obj, &row, &col);
    ESP_LOGI("EVENT DEBUG","Selected cell: row = %d, col = %d, indx = %d", row, col,idx);

    if(col != 0) {
        ESP_LOGI("EVENT DEBUG","Before toggle: state_array[%d] = 0x%X", idx, state_array[idx]);
        state_array[idx] ^= (1 << row);
        ESP_LOGI("EVENT DEBUG","Before toggle: state_array[%d] = 0x%X", idx, state_array[idx]);
        lv_table_set_cell_value(obj, row, col, STATE_TO_STRING(state_array[idx] & (1 << row)));
    }
}

void create_tab_setup(lv_obj_t *tab, int idx) {

    lv_obj_t *slider =lv_slider_create(tab);
    lv_obj_set_width(slider, TABLE_WIDTH);
    lv_obj_align(slider, LV_ALIGN_TOP_MID, 0, 10); // 상단 중앙에 정렬하고 여백 추가
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, idx);
        
    slider_labels[idx] = lv_label_create(tab);
    lv_label_set_text(slider_labels[idx], "0%");
    lv_obj_align_to(slider_labels[idx], slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 5); // 슬라이더 바로 아래에 정렬 및 여백 추가

    lv_obj_t *table = lv_table_create(tab);
    lv_table_set_row_cnt(table, TABLE_ROW);
    lv_table_set_col_cnt(table, TALBE_COL);
    lv_obj_set_size(table, TABLE_WIDTH, TABLE_HEIGHT);
    lv_obj_align(table, LV_ALIGN_BOTTOM_MID, 0, -10); // 탭의 하단 중앙에 정렬 및 여백 추가
    lv_obj_set_y(table, 100);

    for(int i=0;i<TABLE_ROW;i++) {
        lv_table_set_cell_value(table, i, 0, state_title[idx][i]);
        lv_table_set_cell_value(table, i, 1, STATE_TO_STRING(state_array[idx] & (1 << i) ));
    }
    lv_obj_add_event_cb(table, event_state_change, LV_EVENT_VALUE_CHANGED, idx);
}

void slider_event_cb(lv_event_t *e) {
    lv_obj_t *slider = lv_event_get_target(e);
    int idx = (int)(uintptr_t)lv_event_get_user_data(e);

    lv_snprintf(slider_value[idx], sizeof(slider_value[idx]), "%d%%", (int)lv_slider_get_value(slider));
    lv_label_set_text(slider_labels[idx], slider_value[idx]);
    lv_obj_align_to(slider_labels[idx], slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 5); // 슬라이더 바로 아래에 정렬 및 여백 추가
    //ESP_LOGI("EVENT DEBUG","Value = %s", slider_value[idx]);

}

void tabview_setup_Screen_screen_init(void) {
    lv_obj_t *tab_array[4];
    char *desc[] = {"Auto Set", "Lab Set", "Home Set"};
    char *name[] = {"Auto Set", "Lab Set", "Home Set"};
    
    tabview_setup_Screen = lv_obj_create(NULL);
    lv_obj_clear_flag(tabview_setup_Screen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_t *tabview = lv_tabview_create(tabview_setup_Screen, LV_DIR_TOP, 50 );

    for(int i=0;i<3;i++) {
        tab_array[i] = lv_tabview_add_tab(tabview, name[i]);
        create_tab_setup(tab_array[i], i);
    }
}