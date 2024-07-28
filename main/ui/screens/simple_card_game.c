#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

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
#define BACK_OF_CARD "GWNU"

#define STATE_TO_STRING(bit) ((bit) ? "O" : "X")
#define GAME_PROGRESS(progress) ((progress) ? "Restart" : "Start")

bool progress = false;
struct choice_num {
    int value;
    int row;
    int col;   
};

char slider_value[3][10];
lv_obj_t *slider_labels[3];
uint16_t state_array[] = {0b0000000000, 0b0000000000, 0b0000000000};
int choice_value = 0;
struct choice_num choice = {0};
struct choice_num after_choice = {0};

// Fisher-Yates Shuflle
void shuffle_card(int card[TABLE_ROW][TABLE_COL]){
    int total = TABLE_ROW * TABLE_COL;
    for(int idx = total - 1; idx > 0; idx--) {
        int change_idx = rand() % (idx + 1);

        int right_row_idx = idx / TABLE_COL;
        int right_col_idx = idx % TABLE_COL;

        int left_row_idx = change_idx / TABLE_COL;
        int left_col_idx = change_idx % TABLE_COL;

        int temp = card[right_row_idx][right_col_idx];
        card[right_row_idx][right_col_idx] = card[left_row_idx][left_col_idx];
        card[left_row_idx][left_col_idx] = temp;
    }
}

void choice_init(void) {
    choice.value = 0;
    choice.row = 0;
    choice.col = 0;

    after_choice.value = 0;
    after_choice.row = 0;
    after_choice.col = 0;
}

void turn_card(lv_timer_t *timer) {
    lv_obj_t *obj = (lv_obj_t *)timer->user_data;
    ESP_LOGI("EVENT DEBUG","IN TIMER");
    if(obj) {
        ESP_LOGI("EVENT DEBUG","IN TIMER IF");
        lv_table_set_cell_value(obj, after_choice.row, after_choice.col, BACK_OF_CARD);
        lv_table_set_cell_value(obj, choice.row, choice.col, BACK_OF_CARD);
    }
    choice_init();
    lv_timer_del(timer);    
}

void event_state_change(lv_event_t *e) {
    lv_obj_t *obj = lv_event_get_target(e);
    int (*answer)[TABLE_COL] = (int (*)[TABLE_COL])lv_event_get_user_data(e);

    uint16_t col, row;
    char str[10];

    lv_table_get_selected_cell(obj, &row, &col);
    // ESP_LOGI("EVENT DEBUG","Selected cell: row = %d, col = %d, indx = %d", row, col,idx);
    char *data = lv_table_get_cell_value(obj, row, col);
    ESP_LOGI("EVENT DEBUG","Selected cell: row = %d, col = %d, value = %d", row, col, answer[row][col]);
    lv_snprintf(str, sizeof(str), "%d", (int)answer[row][col]);


    if(strcmp(data, "") ==0 || answer[row][col] == -1);
    else {
        lv_table_set_cell_value(obj, row, col, str);
        if(choice.value == 0) {
            choice.value = atoi(data);
            choice.row = row;
            choice.col = col;        
        } else if(choice.row == row && choice.col == col);
        else {
            if(choice.value == atoi(data)) {
                lv_table_set_cell_value(obj, row, col, "");
                lv_table_set_cell_value(obj, choice.row, choice.col, "");
                answer[row][col] = -1;
                answer[choice.row][choice.col] = -1;
                choice_init();
            } else {
                after_choice.value = answer[row][col];
                after_choice.row = row;
                after_choice.col = col;

                lv_timer_t *timer = lv_timer_create(turn_card, 500, obj);
                lv_timer_set_repeat_count(timer, 1);
            }
        }       
    }

}


void show_card(lv_timer_t *timer) {
    lv_obj_t *obj = (lv_obj_t *)timer->user_data;
    ESP_LOGI("EVENT DEBUG","IN TIMER");
    if(obj) {
        for(int row = 0; row < TABLE_ROW; row++) {
            for(int col=0; col < TABLE_COL; col++) {
                lv_table_set_cell_value(obj, row, col, BACK_OF_CARD);
            }
        }
    }
    choice_init();
    lv_timer_del(timer);    
}

void new_game_init(lv_obj_t *main_screen) {
    int (*answer)[TABLE_COL] = malloc(TABLE_ROW * TABLE_COL * sizeof(int));

    if(answer == NULL)
        return;
    else {
        int cnt = 1;
        for(int row=0;row<TABLE_ROW;row++) {
            for(int col=0;col<TABLE_COL;col+=2) {
                answer[row][col] = cnt;
                answer[row][col+1] = cnt;
                cnt++;
            }
        }
        shuffle_card(answer);

        for(int row=0;row<TABLE_ROW;row++) {
            for(int col=0;col<TABLE_COL;col++) {
                ESP_LOGI("EVENT DEBUG","Value: row = %d, col = %d, value = %d", row, col, answer[row][col]);
            }
        }
    }

    lv_obj_t *table = lv_table_create(main_screen);
    lv_table_set_row_cnt(table, TABLE_ROW);
    lv_table_set_col_cnt(table, TABLE_COL);
    lv_obj_set_size(table, TABLE_WIDTH, TABLE_HEIGHT);
    lv_obj_align(table, LV_ALIGN_CENTER, 0, 0);


    for(int row=0;row<TABLE_ROW;row++) {
        for(int col=0;col<TABLE_COL;col++) {
            char num[10];
            lv_snprintf(num, sizeof(num), "%d", (int)answer[row][col]);

            lv_table_set_cell_value(table, row, col, num);
            lv_table_set_col_width(table, col, TABLE_WIDTH/TABLE_ROW);
        }
    }
    lv_timer_t *timer = lv_timer_create(show_card, 1000, table);
    lv_timer_set_repeat_count(timer, 1);


    lv_obj_add_event_cb(table, event_state_change, LV_EVENT_VALUE_CHANGED, answer);
}

void start_btn_click_event(lv_event_t *e) {
    lv_obj_t * obj = lv_event_get_current_target(e);
    lv_obj_t *label = lv_obj_get_child(obj, 0);
    progress = !progress;
    lv_label_set_text(label, GAME_PROGRESS(progress));
    new_game_init(simple_card_game_Screen);
}


void simple_card_game_init(void) {
    srand((unsigned)time(NULL));
    simple_card_game_Screen = lv_obj_create(NULL);
    lv_obj_clear_flag(simple_card_game_Screen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *start_button = lv_btn_create(simple_card_game_Screen);
    lv_obj_set_width(start_button, 100);
    lv_obj_set_height(start_button, 50);
    lv_obj_set_align(start_button, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(start_button, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(start_button, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    
    lv_obj_t *start_button_label = lv_label_create(start_button);
    lv_label_set_text(start_button_label, GAME_PROGRESS(progress));
    lv_obj_center(start_button_label);

    lv_obj_add_event_cb(start_button, start_btn_click_event, LV_EVENT_CLICKED, NULL);

   
}