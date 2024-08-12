#include "../ui.h"
#include <math.h>
#include "lvgl.h"


#define CANVAS_WIDTH  550
#define CANVAS_HEIGHT 240
#define AMPLITUDE     50      // 사인파의 진폭
#define FREQUENCY     (2 * M_PI / 100)  // 주기를 100으로 설정
#define PERIOD        100
lv_obj_t *canvas;
lv_color_t *buf;
int prev_x = 0;
int prev_y = CANVAS_HEIGHT / 2;
float y;
int x;
lv_draw_rect_dsc_t rect_dsc;

void drawing();

// (x, y) 좌표를 계산하는 함수 (가정)
void get_sine_point(int x, float *y) {
    *y = CANVAS_HEIGHT / 2 + AMPLITUDE * sin(FREQUENCY * x);
}

void draw_sine_wave(lv_obj_t *parent) {
    // 1. lv_canvas 객체 생성
    canvas = lv_canvas_create(parent);
    lv_obj_set_size(canvas, CANVAS_WIDTH, CANVAS_HEIGHT);
    lv_obj_set_pos(canvas, 0, 0);

    // 2. 버퍼 할당
    lv_canvas_set_buffer(canvas, buf, CANVAS_WIDTH, CANVAS_HEIGHT, LV_IMG_CF_TRUE_COLOR);

    // 3. 캔버스 초기화
    lv_canvas_fill_bg(canvas, lv_color_black(), NULL); // 캔버스 배경을 검은색으로 설정

    // 4. 점 스타일 설정
    // static lv_color_t color = lv_palette_main(LV_PALETTE_GREEN);
    lv_draw_rect_dsc_init(&rect_dsc);
    rect_dsc.bg_color = lv_palette_main(LV_PALETTE_GREEN);
    rect_dsc.bg_opa = LV_OPA_COVER; // 불투명하게 설정

    // 5. 사인파 점을 하나씩 그리기
    prev_x = 0;
    prev_y = CANVAS_HEIGHT / 2;

    lv_timer_t *timer = lv_timer_create(drawing, 100, NULL);

    // for (int x = 0; x < CANVAS_WIDTH; x++) {
    //     get_sine_point(x, &y);
    //     lv_canvas_set_px_color(canvas, x, (int)y, lv_palette_main(LV_PALETTE_GREEN));

    //     // 이전 점의 색상을 지우기 (원하는 경우)
    //     // if (x > 0) {
    //     //     lv_canvas_set_px_color(canvas, prev_x, prev_y, lv_color_black());
    //     // }

    //     prev_x = x;
    //     prev_y = (int)y;

    //     lv_task_handler();
    // }
}
void drawing() {
    get_sine_point(x, &y);
    // lv_canvas_set_px_color(canvas, x, (int)y, lv_palette_main(LV_PALETTE_GREEN));
    custom_lv_canvas_draw_rect(canvas, x, y, 5, 5, &rect_dsc);
    // lv_canvas_draw_rect(canvas, x, y, 5, 5, &rect_dsc);

    prev_x = x;
    prev_y = (int)y;
    x++;
    if(x)
        lv_obj_invalidate(canvas);
}


void canvas_exm_Screen(void)
{
    canvas_exm_Screen_init_Screen = lv_obj_create(NULL);
    lv_obj_clear_flag(canvas_exm_Screen_init_Screen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    buf = lv_mem_alloc(CANVAS_WIDTH * CANVAS_HEIGHT * sizeof(lv_color_t));
    draw_sine_wave(canvas_exm_Screen_init_Screen);   
}
