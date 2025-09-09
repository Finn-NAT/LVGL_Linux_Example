#include "../lvgl/lvgl.h"
#ifndef SDL_FLAG
#   include "../lv_drivers/display/fbdev.h"
#else
#   include "../lv_drivers/sdl/sdl.h"
#   include <SDL2/SDL.h>
#endif
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h> 

#define LV_HOR_RES_SCR 1280
#define LV_VER_RES_SCR 720

int main(void)
{

#ifndef SDL_FLAG
    lv_init();
    fbdev_init();

    static lv_color_t buf[LV_HOR_RES_SCR * LV_VER_RES_SCR ]; 
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_SCR * LV_VER_RES_SCR ); 

    /*Initialize and register a display driver*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf   = &disp_buf;
    disp_drv.flush_cb   = fbdev_flush;
    disp_drv.hor_res    = LV_HOR_RES_SCR;
    disp_drv.ver_res    = LV_VER_RES_SCR;
    lv_disp_drv_register(&disp_drv);
#else
    lv_init();
    sdl_init();

    // Tạo bộ nhớ đệm hiển thị
    static lv_color_t buf1[LV_HOR_RES_SCR * LV_VER_RES_SCR ];
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf1, NULL, LV_HOR_RES_SCR * LV_VER_RES_SCR );

    // Thiết lập driver hiển thị
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
    disp_drv.flush_cb = sdl_display_flush;
    disp_drv.hor_res = LV_HOR_RES_SCR;
    disp_drv.ver_res = LV_VER_RES_SCR;
    lv_disp_drv_register(&disp_drv);
#endif

    /*Create a "Hello world!" label*/
    lv_obj_t * label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Hello world!");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    /*Handle LitlevGL tasks (tickless mode)*/
    while(1) {
        lv_tick_inc(5);
        lv_timer_handler();
        usleep(5000);
    }

    return 0;
}