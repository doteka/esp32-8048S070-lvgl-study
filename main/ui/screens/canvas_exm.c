#include "lvgl.h"
#include "../ui.h"
#include <math.h> // 사인 함수를 사용하기 위해 필요

#define MAX_POINTS 600          // 최대 점 개수 (한 화면에 표시할 점의 수)
#define TIMER_PERIOD 100        // 100ms
#define LINE_WIDTH 8
#define AMPLITUDE 50            // 사인파의 진폭
#define POINTS_PER_CYCLE 200    // 한 주기당 점의 개수
#define TOTAL_CYCLES (MAX_POINTS / POINTS_PER_CYCLE) // 총 주기의 개수
#define FREQUENCY (2 * M_PI / POINTS_PER_CYCLE) // 사인파의 주파수

static lv_point_t line_points[MAX_POINTS];  // 최대 MAX_POINTS까지의 좌표를 저장할 배열
static int point_count = 0;                 // 현재 좌표 개수

static lv_obj_t * line1;                    // 라인 객체
static lv_style_t style_line;               // 라인 스타일

// 타이머 콜백 함수: 100ms마다 실행됩니다.
static void timer_callback(lv_timer_t * timer) {
    if (point_count < MAX_POINTS) {
        // 새로운 좌표 계산
        lv_coord_t x_new = point_count;
        lv_coord_t y_new = AMPLITUDE * sin(FREQUENCY * x_new);

        // 기존 좌표 백업 (이전 점)
        lv_coord_t x_prev = point_count > 0 ? line_points[point_count - 1].x : x_new;
        lv_coord_t y_prev = point_count > 0 ? line_points[point_count - 1].y : y_new;

        // 새로운 좌표 추가
        line_points[point_count].x = x_new;
        line_points[point_count].y = y_new;
        point_count++;

        // 라인 포인트 업데이트
        lv_line_set_points(line1, line_points, point_count);

        // 선 두께를 사용하여 업데이트할 영역 계산
        lv_area_t update_area;
        update_area.x1 = LV_MIN(x_prev, x_new) - LINE_WIDTH / 2;
        update_area.y1 = LV_MIN(y_prev, y_new) - LINE_WIDTH / 2;
        update_area.x2 = LV_MAX(x_prev, x_new) + LINE_WIDTH / 2;
        update_area.y2 = LV_MAX(y_prev, y_new) + LINE_WIDTH / 2;

        // 해당 영역만 업데이트
        lv_obj_invalidate_area(line1, &update_area);

        // 1.5 주기 이후 이전 라인 지우기
        if (point_count >= MAX_POINTS) {
            point_count = 0; // 점 개수 초기화
            lv_obj_clean(canvas_exm_Screen_init_Screen); // 화면 초기화
            line1 = lv_line_create(canvas_exm_Screen_init_Screen); // 새 라인 객체 생성
            lv_obj_add_style(line1, &style_line, 0);
        }
    } else {
        // 타이머 멈춤 (모든 좌표가 추가되면)
        lv_timer_del(timer);
    }
}

void canvas_exm_Screen(void) {
    canvas_exm_Screen_init_Screen = lv_obj_create(NULL);
    lv_obj_clear_flag(canvas_exm_Screen_init_Screen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    // 라인 스타일 초기화
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, LINE_WIDTH);
    lv_style_set_line_color(&style_line, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_line_rounded(&style_line, true);

    // 라인 객체 생성
    line1 = lv_line_create(canvas_exm_Screen_init_Screen);
    lv_obj_add_style(line1, &style_line, 0);
    lv_obj_center(line1);

    // 타이머 생성: 100ms마다 실행
    lv_timer_t * timer = lv_timer_create(timer_callback, TIMER_PERIOD, NULL);
}
