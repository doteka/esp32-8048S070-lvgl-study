#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "../ui.h"
#include "esp_log.h"
#include "simple_card_game_var.h"

#define TABLE_ROW 7
#define TABLE_COL 4

#define TABLE_WIDTH 400
#define TABLE_HEIGHT 400
#define BACK_OF_CARD "GWNU"

#define STATE_TO_STRING(bit) ((bit) ? "O" : "X")
#define GAME_PROGRESS(count) ((count) ? "Restart" : "START")

int count = -1;
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
lv_obj_t *score_label;

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
    char count_str[20];

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

            count++;
            lv_snprintf(count_str, sizeof(count_str), "Count : %d", (int)count);
            lv_label_set_text(score_label, count_str);

            if(max_score < count) {
                max_score = count;
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
    lv_obj_set_size(table, TABLE_WIDTH, TABLE_WIDTH / TABLE_ROW * TABLE_ROW);
    lv_obj_align(table, LV_ALIGN_CENTER, 0, 0);


    for(int row=0;row<TABLE_ROW;row++) {
        for(int col=0;col<TABLE_COL;col++) {
            char num[10];
            lv_snprintf(num, sizeof(num), "%d", (int)answer[row][col]);

            lv_table_set_cell_value(table, row, col, num);
            lv_table_set_col_width(table, col, TABLE_WIDTH/TABLE_COL);
        }
    }
    lv_timer_t *timer = lv_timer_create(show_card, 1000, table);
    lv_timer_set_repeat_count(timer, 1);

    count = 0;
    lv_obj_add_event_cb(table, event_state_change, LV_EVENT_VALUE_CHANGED, answer);
}

void restart_btn_click_event(lv_event_t *e) {
    lv_obj_t *obj = lv_event_get_current_target(e);
    lv_obj_t *box = lv_obj_get_parent(obj);
    lv_obj_t *box_bg = lv_obj_get_child(box, NULL);

    lv_label_set_text(score_label, "Count : 0");
    lv_obj_del(box_bg);
    lv_obj_del(box);
    new_game_init(simple_card_game_Screen);
}

void exit_btn_click_event(lv_event_t *e) {
    lv_obj_t * obj = lv_event_get_current_target(e);
    lv_obj_del(simple_card_game_Screen);
    simple_card_game_main_Screen();
    lv_disp_load_scr(simple_card_game_init_Screen);
}


void event_setting_btn(lv_event_t *e) {
    char max_score_str[50];
    lv_snprintf(max_score_str, sizeof(max_score_str), "MAX_SCORE : %d", (int)max_score);
    lv_obj_t *setting_box = lv_msgbox_create(NULL, "Setting", max_score_str, NULL, true);
    lv_obj_center(setting_box);

    lv_obj_t *restart_button = lv_btn_create(setting_box);
    lv_obj_center(restart_button);
    lv_obj_t *restart_label = lv_label_create(restart_button);
    lv_obj_center(restart_label);
    lv_label_set_text(restart_label, "Restart!");
    lv_obj_add_event_cb(restart_button, restart_btn_click_event, LV_EVENT_CLICKED, NULL);

    lv_obj_t *exit_button = lv_btn_create(setting_box);
    lv_obj_center(exit_button);
    lv_obj_t *exit_label = lv_label_create(exit_button);
    lv_obj_center(exit_label);
    lv_label_set_text(exit_label, "Exit!");
    lv_obj_add_event_cb(exit_button, exit_btn_click_event, LV_EVENT_CLICKED, NULL);
}

void simple_card_game_init(void) {
    srand((unsigned)time(NULL));
    simple_card_game_Screen = lv_obj_create(NULL);
    lv_obj_clear_flag(simple_card_game_Screen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *setting_btn = lv_btn_create(simple_card_game_Screen);
    lv_obj_set_align(setting_btn, LV_ALIGN_TOP_RIGHT);
    lv_obj_t *setting_btn_label = lv_label_create(setting_btn);
    lv_obj_center(setting_btn_label);
    lv_label_set_text(setting_btn_label, "Setting");
    lv_obj_add_event_cb(setting_btn, event_setting_btn, LV_EVENT_CLICKED, NULL);

    score_label = lv_label_create(simple_card_game_Screen);
    lv_label_set_text(score_label, "Count : 0");
    lv_obj_set_align(score_label, LV_ALIGN_BOTTOM_MID);
    new_game_init(simple_card_game_Screen);   
}