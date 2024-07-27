#include <stdbool.h>
#include "../ui.h"
#include "esp_log.h"

void tabview_grid_Screen_init(void) {
    // 컬럼과 행의 크기를 정의
    static lv_coord_t col_dsc[] = {70, 70, 70, LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {50, 50, 50, LV_GRID_TEMPLATE_LAST};

    // 그리드 레이아웃을 가진 컨테이너 생성
    lv_obj_t * tabview_setup_Screen = lv_obj_create(NULL);
    if (tabview_setup_Screen == NULL) {
        ESP_LOGE("UI", "tabview_setup_Screen 생성 실패");
        return;
    }

    // 컬럼 및 행 설명 배열 설정
    lv_obj_set_style_grid_column_dsc_array(tabview_setup_Screen, col_dsc, 0);
    lv_obj_set_style_grid_row_dsc_array(tabview_setup_Screen, row_dsc, 0);
    
    // 사이즈와 위치 설정
    lv_obj_set_size(tabview_setup_Screen, 300, 220);
    lv_obj_center(tabview_setup_Screen);
    lv_obj_set_layout(tabview_setup_Screen, LV_LAYOUT_GRID);

    lv_obj_t * label;
    lv_obj_t * obj;

    for(uint32_t i = 0; i < 9; i++) {
        uint8_t col = i % 3;
        uint8_t row = i / 3;

        obj = lv_btn_create(tabview_setup_Screen);
        if (obj == NULL) {
            ESP_LOGE("UI", "버튼 생성 실패");
            return;
        }

        // 그리드 셀에 버튼 배치
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, col, 1,
                             LV_GRID_ALIGN_STRETCH, row, 1);

        label = lv_label_create(obj);
        if (label == NULL) {
            ESP_LOGE("UI", "레이블 생성 실패");
            return;
        }
        lv_label_set_text_fmt(label, "c%d, r%d", col, row);
        lv_obj_center(label);
    }
}
