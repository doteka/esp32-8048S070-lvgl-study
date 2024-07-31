#include "../ui.h"
#include "simple_card_game_var.h"

int min_score = 9999;
lv_obj_t *max_score_label;

void game_start_btn_event(lv_event_t *e) {
    simple_card_game_init();
    lv_disp_load_scr(simple_card_game_Screen);
}

void simple_card_game_main_Screen(void)
{
    char max_score_str[30];

    simple_card_game_init_Screen = lv_obj_create(NULL);
    lv_obj_clear_flag(simple_card_game_init_Screen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    max_score_label = lv_label_create(simple_card_game_init_Screen);
    lv_obj_center(max_score_label);
    if(min_score == 9999)
        lv_snprintf(max_score_str, sizeof(max_score_str), "Shortest Record : %d", (int)0);
    else
        lv_snprintf(max_score_str, sizeof(max_score_str), "Shortest Record : %d", (int)min_score);
    lv_label_set_text(max_score_label, max_score_str);

    lv_obj_t *game_start_btn = lv_btn_create(simple_card_game_init_Screen);
    lv_obj_set_width(game_start_btn, 100);
    lv_obj_set_height(game_start_btn, 50);
    lv_obj_align(game_start_btn, LV_ALIGN_BOTTOM_MID, 0, 0);
    
    lv_obj_t *game_start_btn_label = lv_label_create(game_start_btn);
    lv_obj_center(game_start_btn_label);
    lv_label_set_text(game_start_btn_label, "GAME START");

    lv_obj_add_event_cb(game_start_btn, game_start_btn_event, LV_EVENT_CLICKED, NULL);
}
