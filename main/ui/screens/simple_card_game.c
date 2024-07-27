#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ui.h"
#include "esp_log.h"

// #define WIDTH 350
// #define HEIGHT 350
// #define COL 3
// #define ROW 3

// void simple_card_game_init(void) {
//     // 그리드 열과 행 크기 설정
//     lv_coord_t col_dsc[] = {WIDTH / COL, WIDTH / COL, WIDTH / COL, LV_GRID_TEMPLATE_LAST};
//     lv_coord_t row_dsc[] = {HEIGHT / ROW, HEIGHT / ROW, HEIGHT / ROW, LV_GRID_TEMPLATE_LAST};

//     // 화면 생성
//     simple_card_game_Screen = lv_obj_create(NULL);
//     lv_obj_clear_flag(simple_card_game_Screen, LV_OBJ_FLAG_SCROLLABLE);

//     // 그리드 생성
//     lv_obj_t *grid = lv_obj_create(simple_card_game_Screen);
//     lv_obj_set_size(grid, WIDTH, HEIGHT);
//     lv_obj_center(grid);
//     lv_obj_set_layout(grid, LV_LAYOUT_GRID);
//     lv_obj_set_style_grid_column_dsc_array(grid, col_dsc, 0);
//     lv_obj_set_style_grid_row_dsc_array(grid, row_dsc, 0);
//     lv_obj_set_style_pad_all(grid, 0, 0);
    
//     // 그리드 배경색 설정 (디버깅용)
//     lv_obj_set_style_bg_color(grid, lv_color_hex(0xDDDDDD), 0); 

//     // 버튼 생성
//     for(uint32_t i = 0; i < COL * ROW; i++) {
//         uint8_t col = i % COL;
//         uint8_t row = i / COL;

//         lv_obj_t *obj = lv_btn_create(grid);
//         lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, col, 1, LV_GRID_ALIGN_STRETCH, row, 1); // 버튼 위치 설정

//         lv_obj_t *label = lv_label_create(obj);
//         lv_label_set_text(label, "BTN");
//         lv_obj_center(label);
        
//         // 버튼 스타일 설정
//         lv_obj_set_style_bg_color(obj, lv_color_hex(0x007BFF), 0); // 버튼 배경색
//         lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), 0); // 텍스트 색상
//     }

//     // 화면을 다시 그리기
//     lv_scr_load(simple_card_game_Screen);
// }


#define TABLE_ROW 4
#define TABLE_COL 4

#define TABLE_WIDTH 400
#define TABLE_HEIGHT 400

#define STATE_TO_STRING(bit) ((bit) ? "O" : "X")

struct choice_num {
    int value;
    int row;
    int col;   
};

char slider_value[3][10];
lv_obj_t *slider_labels[3];
uint16_t state_array[] = {0b0000000000, 0b0000000000, 0b0000000000};
int choice_value = 0;
struct choice_num choice = {0}; // 초기화

void event_state_change(lv_event_t *e) {
    lv_obj_t *obj = lv_event_get_target(e);
    int idx = (int)(uintptr_t)lv_event_get_user_data(e);

    
    uint16_t col, row;
    lv_table_get_selected_cell(obj, &row, &col);
    ESP_LOGI("EVENT DEBUG","Selected cell: row = %d, col = %d, indx = %d", row, col,idx);
    char *data = lv_table_get_cell_value(obj, row, col);
    if(strcmp(data, "")!= 0 && choice.value == 0) {
        choice.value = atoi(data);
        choice.row = row;
        choice.col = col;        
    } else if(choice.row == row && choice.col == col);
    else if(strcmp(data, "")!= 0) {
        int after_choice = atoi(data);
        if(choice.value == after_choice) {
            lv_table_set_cell_value(obj, row, col, "");
            lv_table_set_cell_value(obj, choice.row, choice.col, "");
        }
        choice.value = 0;
        choice.row = 0;
        choice.col = 0;
    } 
    // lv_table_set_cell_value(obj, row, col, "Clear");
    // if(col != 0) {
    //     ESP_LOGI("EVENT DEBUG","Before toggle: state_array[%d] = 0x%X", idx, state_array[idx]);
    //     state_array[idx] ^= (1 << row);
    //     ESP_LOGI("EVENT DEBUG","Before toggle: state_array[%d] = 0x%X", idx, state_array[idx]);
    //     lv_table_set_cell_value(obj, row, col, STATE_TO_STRING(state_array[idx] & (1 << row)));
    // }
}

void new_game_init(lv_obj_t *main_screen, int num[][TABLE_COL+1]) {

    lv_obj_t *table = lv_table_create(main_screen);
    lv_table_set_row_cnt(table, TABLE_ROW);
    lv_table_set_col_cnt(table, TABLE_COL);
    lv_obj_set_size(table, TABLE_WIDTH, TABLE_HEIGHT);
    lv_obj_align(table, LV_ALIGN_CENTER, 0, 0); // 탭의 하단 중앙에 정렬 및 여백 추가


    for(int row=1;row<=TABLE_ROW;row++) {
        for(int col=1;col<=TABLE_COL;col++) {
            char str[12];

            lv_snprintf(str, sizeof(str), "%d", (int)num[row][col]);
            lv_table_set_cell_value(table, row, col, str);
        }
    }
    lv_obj_add_event_cb(table, event_state_change, LV_EVENT_VALUE_CHANGED, NULL);
}


void simple_card_game_init(void) {
    int num[TABLE_ROW+1][TABLE_COL+1];
    simple_card_game_Screen = lv_obj_create(NULL);
    lv_obj_clear_flag(simple_card_game_Screen, LV_OBJ_FLAG_SCROLLABLE);
    int cnt = 1;
    for(int i=1; i<=TABLE_ROW; i++) {
        for(int j=1;j<=TABLE_COL;j+=2) {
            num[i][j] = cnt;
            num[i][j+1] = cnt;
            cnt++;
        }
    }

    new_game_init(simple_card_game_Screen, num);
}