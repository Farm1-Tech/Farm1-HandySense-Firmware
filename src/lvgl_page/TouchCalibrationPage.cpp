/* ======== Generate by IOXGD Designer ======== */
#include "lvgl.h"

LV_FONT_DECLARE(Kanit_Regular_20);
LV_FONT_DECLARE(Kanit_Regular_16);
LV_FONT_DECLARE(Kanit_Regular_14);

lv_obj_t* TouchCalibrationScreen;

/* ========== MainBoxTouchCalibration header ========== */
static lv_style_t MainBoxTouchCalibration_style;
lv_obj_t* MainBoxTouchCalibration;
/* ====== END of MainBoxTouchCalibration header ====== */

/* ========== objTopLeftTouchPoint header ========== */
static lv_style_t objTopLeftTouchPoint_style;
lv_obj_t* objTopLeftTouchPoint;
/* ====== END of objTopLeftTouchPoint header ====== */

/* ========== objBottomLeftTouchPoint header ========== */
static lv_style_t objBottomLeftTouchPoint_style;
lv_obj_t* objBottomLeftTouchPoint;
/* ====== END of objBottomLeftTouchPoint header ====== */

/* ========== objBottomRightTouchPoint header ========== */
static lv_style_t objBottomRightTouchPoint_style;
lv_obj_t* objBottomRightTouchPoint;
/* ====== END of objBottomRightTouchPoint header ====== */

/* ========== objRightLeftTouchPoint header ========== */
static lv_style_t objRightLeftTouchPoint_style;
lv_obj_t* objRightLeftTouchPoint;
/* ====== END of objRightLeftTouchPoint header ====== */

/* ========== txtTouchCalibrationCountdown header ========== */
static lv_style_t txtTouchCalibrationCountdown_style;
lv_obj_t* txtTouchCalibrationCountdown;
/* ====== END of txtTouchCalibrationCountdown header ====== */

/* ========== txtTouchCalibrationStep header ========== */
static lv_style_t txtTouchCalibrationStep_style;
lv_obj_t* txtTouchCalibrationStep;
/* ====== END of txtTouchCalibrationStep header ====== */


void load_page_touch_calibration() {
  TouchCalibrationScreen = lv_obj_create(NULL, NULL);
  
  static lv_style_t style_screen;
  lv_style_copy(&style_screen, &lv_style_plain);
  style_screen.body.main_color = lv_color_hex(0xFFFFFF);
  style_screen.body.grad_color = lv_color_hex(0xFFFFFF);
  lv_obj_set_style(TouchCalibrationScreen, &style_screen);
  
  /* ========== MainBoxTouchCalibration ========== */
  lv_style_copy(&MainBoxTouchCalibration_style, &lv_style_plain);
  MainBoxTouchCalibration_style.body.main_color = lv_color_hex(0xf9f9f9);
  MainBoxTouchCalibration_style.body.grad_color = lv_color_hex(0xf9f9f9);
  MainBoxTouchCalibration_style.body.radius = 0;
  MainBoxTouchCalibration_style.body.opa = 255;
  MainBoxTouchCalibration_style.body.border.color = lv_color_hex(0x000000);
  MainBoxTouchCalibration_style.body.border.width = 0;
  MainBoxTouchCalibration_style.body.border.opa = 255;
  MainBoxTouchCalibration_style.body.shadow.color = lv_color_hex(0x000000);
  MainBoxTouchCalibration_style.body.shadow.width = 0;
  MainBoxTouchCalibration_style.body.shadow.type = LV_SHADOW_FULL;
  
  MainBoxTouchCalibration = lv_obj_create(TouchCalibrationScreen, NULL);
  lv_obj_set_style(MainBoxTouchCalibration, &MainBoxTouchCalibration_style);
  lv_obj_set_size(MainBoxTouchCalibration, 320, 240);
  lv_obj_align(MainBoxTouchCalibration, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
  
  lv_obj_set_hidden(MainBoxTouchCalibration, false);
  /* ====== END of MainBoxTouchCalibration ====== */
  
  /* ========== objTopLeftTouchPoint ========== */
  lv_style_copy(&objTopLeftTouchPoint_style, &lv_style_plain);
  objTopLeftTouchPoint_style.body.main_color = lv_color_hex(0xFF0000);
  objTopLeftTouchPoint_style.body.grad_color = lv_color_hex(0xFF0000);
  objTopLeftTouchPoint_style.body.radius = 100;
  objTopLeftTouchPoint_style.body.opa = 255;
  objTopLeftTouchPoint_style.body.border.color = lv_color_hex(0x000000);
  objTopLeftTouchPoint_style.body.border.width = 0;
  objTopLeftTouchPoint_style.body.border.opa = 255;
  objTopLeftTouchPoint_style.body.shadow.color = lv_color_hex(0x000000);
  objTopLeftTouchPoint_style.body.shadow.width = 0;
  objTopLeftTouchPoint_style.body.shadow.type = LV_SHADOW_FULL;
  
  objTopLeftTouchPoint = lv_obj_create(TouchCalibrationScreen, NULL);
  lv_obj_set_style(objTopLeftTouchPoint, &objTopLeftTouchPoint_style);
  lv_obj_set_size(objTopLeftTouchPoint, 16, 16);
  lv_obj_align(objTopLeftTouchPoint, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 20);
  
  lv_obj_set_hidden(objTopLeftTouchPoint, false);
  /* ====== END of objTopLeftTouchPoint ====== */
  
  /* ========== txt6 ========== */
  static lv_style_t txt6_style;
  lv_obj_t* txt6;
  
  lv_style_copy(&txt6_style, &lv_style_plain);
  txt6_style.text.color = lv_color_hex(0x0EA661);
  txt6_style.text.font = &Kanit_Regular_20;
  
  txt6 = lv_label_create(MainBoxTouchCalibration, NULL);
  lv_label_set_style(txt6, LV_LABEL_STYLE_MAIN, &txt6_style);
  lv_label_set_long_mode(txt6, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txt6, LV_LABEL_ALIGN_CENTER);
  lv_label_set_text(txt6, "ตั้งค่าจุดสัมผัส");
  lv_obj_set_size(txt6, 0, 0);
  lv_obj_align(txt6, NULL, LV_ALIGN_IN_TOP_MID, 0, 20);
  
  lv_obj_set_hidden(txt6, false);
  /* ====== END of txt6 ====== */
  
  /* ========== objBottomLeftTouchPoint ========== */
  lv_style_copy(&objBottomLeftTouchPoint_style, &lv_style_plain);
  objBottomLeftTouchPoint_style.body.main_color = lv_color_hex(0xFF0000);
  objBottomLeftTouchPoint_style.body.grad_color = lv_color_hex(0xFF0000);
  objBottomLeftTouchPoint_style.body.radius = 100;
  objBottomLeftTouchPoint_style.body.opa = 255;
  objBottomLeftTouchPoint_style.body.border.color = lv_color_hex(0x000000);
  objBottomLeftTouchPoint_style.body.border.width = 0;
  objBottomLeftTouchPoint_style.body.border.opa = 255;
  objBottomLeftTouchPoint_style.body.shadow.color = lv_color_hex(0x000000);
  objBottomLeftTouchPoint_style.body.shadow.width = 0;
  objBottomLeftTouchPoint_style.body.shadow.type = LV_SHADOW_FULL;
  
  objBottomLeftTouchPoint = lv_obj_create(MainBoxTouchCalibration, NULL);
  lv_obj_set_style(objBottomLeftTouchPoint, &objBottomLeftTouchPoint_style);
  lv_obj_set_size(objBottomLeftTouchPoint, 16, 16);
  lv_obj_align(objBottomLeftTouchPoint, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 20, -20);
  
  lv_obj_set_hidden(objBottomLeftTouchPoint, false);
  /* ====== END of objBottomLeftTouchPoint ====== */
  
  /* ========== objBottomRightTouchPoint ========== */
  lv_style_copy(&objBottomRightTouchPoint_style, &lv_style_plain);
  objBottomRightTouchPoint_style.body.main_color = lv_color_hex(0xFF0000);
  objBottomRightTouchPoint_style.body.grad_color = lv_color_hex(0xFF0000);
  objBottomRightTouchPoint_style.body.radius = 100;
  objBottomRightTouchPoint_style.body.opa = 255;
  objBottomRightTouchPoint_style.body.border.color = lv_color_hex(0x000000);
  objBottomRightTouchPoint_style.body.border.width = 0;
  objBottomRightTouchPoint_style.body.border.opa = 255;
  objBottomRightTouchPoint_style.body.shadow.color = lv_color_hex(0x000000);
  objBottomRightTouchPoint_style.body.shadow.width = 0;
  objBottomRightTouchPoint_style.body.shadow.type = LV_SHADOW_FULL;
  
  objBottomRightTouchPoint = lv_obj_create(MainBoxTouchCalibration, NULL);
  lv_obj_set_style(objBottomRightTouchPoint, &objBottomRightTouchPoint_style);
  lv_obj_set_size(objBottomRightTouchPoint, 16, 16);
  lv_obj_align(objBottomRightTouchPoint, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -20, -20);
  
  lv_obj_set_hidden(objBottomRightTouchPoint, false);
  /* ====== END of objBottomRightTouchPoint ====== */
  
  /* ========== objRightLeftTouchPoint ========== */
  lv_style_copy(&objRightLeftTouchPoint_style, &lv_style_plain);
  objRightLeftTouchPoint_style.body.main_color = lv_color_hex(0xFF0000);
  objRightLeftTouchPoint_style.body.grad_color = lv_color_hex(0xFF0000);
  objRightLeftTouchPoint_style.body.radius = 100;
  objRightLeftTouchPoint_style.body.opa = 255;
  objRightLeftTouchPoint_style.body.border.color = lv_color_hex(0x000000);
  objRightLeftTouchPoint_style.body.border.width = 0;
  objRightLeftTouchPoint_style.body.border.opa = 255;
  objRightLeftTouchPoint_style.body.shadow.color = lv_color_hex(0x000000);
  objRightLeftTouchPoint_style.body.shadow.width = 0;
  objRightLeftTouchPoint_style.body.shadow.type = LV_SHADOW_FULL;
  
  objRightLeftTouchPoint = lv_obj_create(MainBoxTouchCalibration, NULL);
  lv_obj_set_style(objRightLeftTouchPoint, &objRightLeftTouchPoint_style);
  lv_obj_set_size(objRightLeftTouchPoint, 16, 16);
  lv_obj_align(objRightLeftTouchPoint, NULL, LV_ALIGN_IN_TOP_RIGHT, -20, 20);
  
  lv_obj_set_hidden(objRightLeftTouchPoint, false);
  /* ====== END of objRightLeftTouchPoint ====== */
  
  /* ========== txtTouchCalibrationCountdown ========== */
  lv_style_copy(&txtTouchCalibrationCountdown_style, &lv_style_plain);
  txtTouchCalibrationCountdown_style.text.color = lv_color_hex(0xE74C3C);
  txtTouchCalibrationCountdown_style.text.font = &Kanit_Regular_16;
  
  txtTouchCalibrationCountdown = lv_label_create(MainBoxTouchCalibration, NULL);
  lv_label_set_style(txtTouchCalibrationCountdown, LV_LABEL_STYLE_MAIN, &txtTouchCalibrationCountdown_style);
  lv_label_set_long_mode(txtTouchCalibrationCountdown, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txtTouchCalibrationCountdown, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txtTouchCalibrationCountdown, "เหลืออีก 0 วินาที");
  lv_obj_set_size(txtTouchCalibrationCountdown, 0, 0);
  lv_obj_align(txtTouchCalibrationCountdown, NULL, LV_ALIGN_CENTER, 0, 26);
  
  lv_obj_set_hidden(txtTouchCalibrationCountdown, false);
  /* ====== END of txtTouchCalibrationCountdown ====== */
  
  /* ========== txtTouchCalibrationStep ========== */
  lv_style_copy(&txtTouchCalibrationStep_style, &lv_style_plain);
  txtTouchCalibrationStep_style.text.color = lv_color_hex(0x000000);
  txtTouchCalibrationStep_style.text.font = &Kanit_Regular_16;
  
  txtTouchCalibrationStep = lv_label_create(MainBoxTouchCalibration, NULL);
  lv_label_set_style(txtTouchCalibrationStep, LV_LABEL_STYLE_MAIN, &txtTouchCalibrationStep_style);
  lv_label_set_long_mode(txtTouchCalibrationStep, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txtTouchCalibrationStep, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txtTouchCalibrationStep, "กดจุดด้านบนซ้ายค้างไว้");
  lv_obj_set_size(txtTouchCalibrationStep, 0, 0);
  lv_obj_align(txtTouchCalibrationStep, NULL, LV_ALIGN_CENTER, 0, 0);
  
  lv_obj_set_hidden(txtTouchCalibrationStep, false);
  /* ====== END of txtTouchCalibrationStep ====== */
}
