# Linux LVGL Example Project

## Overview
This project was created to test certain functionalities of LVGL before integrating them into the main LVGL project. Currently, it includes:
- Framebufffer on LVGL: For running on Embedded Computer
- SDl on LVGL: For previewing in developer computer
- Cross Compiler: To support ARM architecture

Before you run the project, just config the path in **lvgl** and **lv_drivers**
```c
// From
#include "lvgl/lvgl.h"
// To
#include "../../lvgl/lvgl.h"     
// In file: fbdev.h, sdl.h and sdl_common.h
```
