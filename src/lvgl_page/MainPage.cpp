/* ======== Generate by IOXGD Designer ======== */

#include "lvgl.h"
LV_FONT_DECLARE(Kanit_Regular_20);
LV_FONT_DECLARE(Kanit_Regular_16);
LV_FONT_DECLARE(Kanit_Regular_14);

/* ========== txtTemp header ========== */
static lv_style_t txtTemp_style;
lv_obj_t* txtTemp;
/* ====== END of txtTemp header ====== */

/* ========== img1 header ========== */
LV_IMG_DECLARE(img_thermometer);
/* ====== END of img1 header ====== */

/* ========== img2 header ========== */
LV_IMG_DECLARE(img_humidity);
/* ====== END of img2 header ====== */

/* ========== txtHumi header ========== */
static lv_style_t txtHumi_style;
lv_obj_t* txtHumi;
/* ====== END of txtHumi header ====== */

/* ========== txtHumi2 header ========== */
static lv_style_t txtHumi2_style;
lv_obj_t* txtHumi2;
/* ====== END of txtHumi2 header ====== */

/* ========== img3 header ========== */
LV_IMG_DECLARE(img_humidity2);
/* ====== END of img3 header ====== */

/* ========== txtLight header ========== */
static lv_style_t txtLight_style;
lv_obj_t* txtLight;
/* ====== END of txtLight header ====== */

/* ========== img4 header ========== */
LV_IMG_DECLARE(img_sun);
/* ====== END of img4 header ====== */

/* ========== imgWiFi header ========== */
lv_obj_t* imgWiFi;
LV_IMG_DECLARE(img_wifi);
/* ====== END of imgWiFi header ====== */

/* ========== imgNexpie header ========== */
lv_obj_t* imgNexpie;
LV_IMG_DECLARE(img_cloud_computing);
/* ====== END of imgNexpie header ====== */

/* ========== txtTime header ========== */
static lv_style_t txtTime_style;
lv_obj_t* txtTime;
/* ====== END of txtTime header ====== */


void load_page() {
  static lv_style_t style_screen;
  lv_style_copy(&style_screen, &lv_style_plain);
  style_screen.body.main_color = lv_color_hex(0xFFFFFF);
  style_screen.body.grad_color = lv_color_hex(0xFFFFFF);
  lv_obj_set_style(lv_scr_act(), &style_screen);
  
  /* ========== Main ========== */
  static lv_style_t Main_style;
  lv_obj_t* Main;
  
  lv_style_copy(&Main_style, &lv_style_plain);
  Main_style.body.main_color = lv_color_hex(0xf9f9f9);
  Main_style.body.grad_color = lv_color_hex(0xf9f9f9);
  Main_style.body.radius = 0;
  Main_style.body.opa = 255;
  Main_style.body.border.color = lv_color_hex(0x000000);
  Main_style.body.border.width = 0;
  Main_style.body.border.opa = 255;
  Main_style.body.shadow.color = lv_color_hex(0x000000);
  Main_style.body.shadow.width = 0;
  Main_style.body.shadow.type = LV_SHADOW_FULL;
  
  Main = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_style(Main, &Main_style);
  lv_obj_set_size(Main, 320, 240);
  lv_obj_align(Main, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
  
  lv_obj_set_hidden(Main, false);
  /* ====== END of Main ====== */
  
  /* ========== tempBox ========== */
  static lv_style_t tempBox_style;
  lv_obj_t* tempBox;
  
  lv_style_copy(&tempBox_style, &lv_style_plain);
  tempBox_style.body.main_color = lv_color_hex(0xFFFFFF);
  tempBox_style.body.grad_color = lv_color_hex(0xFFFFFF);
  tempBox_style.body.radius = 20;
  tempBox_style.body.opa = 255;
  tempBox_style.body.border.color = lv_color_hex(0xE4E4E4);
  tempBox_style.body.border.width = 1;
  tempBox_style.body.border.opa = 255;
  tempBox_style.body.shadow.color = lv_color_hex(0x000000);
  tempBox_style.body.shadow.width = 0;
  tempBox_style.body.shadow.type = LV_SHADOW_FULL;
  
  tempBox = lv_obj_create(Main, NULL);
  lv_obj_set_style(tempBox, &tempBox_style);
  lv_obj_set_size(tempBox, 140, 80);
  lv_obj_align(tempBox, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 60);
  
  lv_obj_set_hidden(tempBox, false);
  /* ====== END of tempBox ====== */
  
  /* ========== txt1 ========== */
  static lv_style_t txt1_style;
  lv_obj_t* txt1;
  
  lv_style_copy(&txt1_style, &lv_style_plain);
  txt1_style.text.color = lv_color_hex(0x000000);
  txt1_style.text.font = &Kanit_Regular_14;
  
  txt1 = lv_label_create(tempBox, NULL);
  lv_label_set_style(txt1, LV_LABEL_STYLE_MAIN, &txt1_style);
  lv_label_set_long_mode(txt1, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txt1, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txt1, "อุณหภูมิ");
  lv_obj_set_size(txt1, 0, 0);
  lv_obj_align(txt1, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -20);
  
  lv_obj_set_hidden(txt1, false);
  /* ====== END of txt1 ====== */
  
  /* ========== txtTemp ========== */
  lv_style_copy(&txtTemp_style, &lv_style_plain);
  txtTemp_style.text.color = lv_color_hex(0x000000);
  txtTemp_style.text.font = &Kanit_Regular_20;
  
  txtTemp = lv_label_create(tempBox, NULL);
  lv_label_set_style(txtTemp, LV_LABEL_STYLE_MAIN, &txtTemp_style);
  lv_label_set_long_mode(txtTemp, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txtTemp, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txtTemp, "20.3");
  lv_obj_set_size(txtTemp, 0, 0);
  lv_obj_align(txtTemp, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -30, -37);
  
  lv_obj_set_hidden(txtTemp, false);
  /* ====== END of txtTemp ====== */
  
  /* ========== humiBox ========== */
  static lv_style_t humiBox_style;
  lv_obj_t* humiBox;
  
  lv_style_copy(&humiBox_style, &lv_style_plain);
  humiBox_style.body.main_color = lv_color_hex(0xFFFFFF);
  humiBox_style.body.grad_color = lv_color_hex(0xFFFFFF);
  humiBox_style.body.radius = 20;
  humiBox_style.body.opa = 255;
  humiBox_style.body.border.color = lv_color_hex(0xE4E4E4);
  humiBox_style.body.border.width = 1;
  humiBox_style.body.border.opa = 255;
  humiBox_style.body.shadow.color = lv_color_hex(0x000000);
  humiBox_style.body.shadow.width = 0;
  humiBox_style.body.shadow.type = LV_SHADOW_FULL;
  
  humiBox = lv_obj_create(Main, NULL);
  lv_obj_set_style(humiBox, &humiBox_style);
  lv_obj_set_size(humiBox, 140, 80);
  lv_obj_align(humiBox, NULL, LV_ALIGN_IN_TOP_LEFT, 170, 60);
  
  lv_obj_set_hidden(humiBox, false);
  /* ====== END of humiBox ====== */
  
  /* ========== humi2Box ========== */
  static lv_style_t humi2Box_style;
  lv_obj_t* humi2Box;
  
  lv_style_copy(&humi2Box_style, &lv_style_plain);
  humi2Box_style.body.main_color = lv_color_hex(0xFFFFFF);
  humi2Box_style.body.grad_color = lv_color_hex(0xFFFFFF);
  humi2Box_style.body.radius = 20;
  humi2Box_style.body.opa = 255;
  humi2Box_style.body.border.color = lv_color_hex(0xE4E4E4);
  humi2Box_style.body.border.width = 1;
  humi2Box_style.body.border.opa = 255;
  humi2Box_style.body.shadow.color = lv_color_hex(0xD6D6D6);
  humi2Box_style.body.shadow.width = 0;
  humi2Box_style.body.shadow.type = LV_SHADOW_FULL;
  
  humi2Box = lv_obj_create(Main, NULL);
  lv_obj_set_style(humi2Box, &humi2Box_style);
  lv_obj_set_size(humi2Box, 140, 80);
  lv_obj_align(humi2Box, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 150);
  
  lv_obj_set_hidden(humi2Box, false);
  /* ====== END of humi2Box ====== */
  
  /* ========== lightBox ========== */
  static lv_style_t lightBox_style;
  lv_obj_t* lightBox;
  
  lv_style_copy(&lightBox_style, &lv_style_plain);
  lightBox_style.body.main_color = lv_color_hex(0xFFFFFF);
  lightBox_style.body.grad_color = lv_color_hex(0xFFFFFF);
  lightBox_style.body.radius = 20;
  lightBox_style.body.opa = 255;
  lightBox_style.body.border.color = lv_color_hex(0xE4E4E4);
  lightBox_style.body.border.width = 1;
  lightBox_style.body.border.opa = 255;
  lightBox_style.body.shadow.color = lv_color_hex(0x000000);
  lightBox_style.body.shadow.width = 0;
  lightBox_style.body.shadow.type = LV_SHADOW_FULL;
  
  lightBox = lv_obj_create(Main, NULL);
  lv_obj_set_style(lightBox, &lightBox_style);
  lv_obj_set_size(lightBox, 140, 80);
  lv_obj_align(lightBox, NULL, LV_ALIGN_IN_TOP_LEFT, 170, 150);
  
  lv_obj_set_hidden(lightBox, false);
  /* ====== END of lightBox ====== */
  
  /* ========== img1 ========== */
  lv_obj_t* img1;
  
  img1 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(img1, &img_thermometer);
  lv_obj_align(img1, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 80);
  
  lv_obj_set_hidden(img1, false);
  /* ====== END of img1 ====== */
  
  /* ========== img2 ========== */
  lv_obj_t* img2;
  
  img2 = lv_img_create(humiBox, NULL);
  lv_img_set_src(img2, &img_humidity);
  lv_obj_align(img2, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 20);
  
  lv_obj_set_hidden(img2, false);
  /* ====== END of img2 ====== */
  
  /* ========== txtHumi ========== */
  lv_style_copy(&txtHumi_style, &lv_style_plain);
  txtHumi_style.text.color = lv_color_hex(0x000000);
  txtHumi_style.text.font = &Kanit_Regular_20;
  
  txtHumi = lv_label_create(humiBox, NULL);
  lv_label_set_style(txtHumi, LV_LABEL_STYLE_MAIN, &txtHumi_style);
  lv_label_set_long_mode(txtHumi, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txtHumi, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txtHumi, "20.3");
  lv_obj_set_size(txtHumi, 0, 0);
  lv_obj_align(txtHumi, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -23, -38);
  
  lv_obj_set_hidden(txtHumi, false);
  /* ====== END of txtHumi ====== */
  
  /* ========== txt5 ========== */
  static lv_style_t txt5_style;
  lv_obj_t* txt5;
  
  lv_style_copy(&txt5_style, &lv_style_plain);
  txt5_style.text.color = lv_color_hex(0x000000);
  txt5_style.text.font = &Kanit_Regular_16;
  
  txt5 = lv_label_create(humiBox, NULL);
  lv_label_set_style(txt5, LV_LABEL_STYLE_MAIN, &txt5_style);
  lv_label_set_long_mode(txt5, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txt5, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txt5, "%");
  lv_obj_set_size(txt5, 0, 0);
  lv_obj_align(txt5, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -40);
  
  lv_obj_set_hidden(txt5, false);
  /* ====== END of txt5 ====== */
  
  /* ========== txt6 ========== */
  static lv_style_t txt6_style;
  lv_obj_t* txt6;
  
  lv_style_copy(&txt6_style, &lv_style_plain);
  txt6_style.text.color = lv_color_hex(0x000000);
  txt6_style.text.font = &Kanit_Regular_14;
  
  txt6 = lv_label_create(humiBox, NULL);
  lv_label_set_style(txt6, LV_LABEL_STYLE_MAIN, &txt6_style);
  lv_label_set_long_mode(txt6, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txt6, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txt6, "ความชื้นอากาศ");
  lv_obj_set_size(txt6, 0, 0);
  lv_obj_align(txt6, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -20);
  
  lv_obj_set_hidden(txt6, false);
  /* ====== END of txt6 ====== */
  
  /* ========== txt7 ========== */
  static lv_style_t txt7_style;
  lv_obj_t* txt7;
  
  lv_style_copy(&txt7_style, &lv_style_plain);
  txt7_style.text.color = lv_color_hex(0x000000);
  txt7_style.text.font = &Kanit_Regular_14;
  
  txt7 = lv_label_create(humi2Box, NULL);
  lv_label_set_style(txt7, LV_LABEL_STYLE_MAIN, &txt7_style);
  lv_label_set_long_mode(txt7, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txt7, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txt7, "ความชื้นดิน");
  lv_obj_set_size(txt7, 0, 0);
  lv_obj_align(txt7, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -20);
  
  lv_obj_set_hidden(txt7, false);
  /* ====== END of txt7 ====== */
  
  /* ========== txtHumi2 ========== */
  lv_style_copy(&txtHumi2_style, &lv_style_plain);
  txtHumi2_style.text.color = lv_color_hex(0x000000);
  txtHumi2_style.text.font = &Kanit_Regular_20;
  
  txtHumi2 = lv_label_create(humi2Box, NULL);
  lv_label_set_style(txtHumi2, LV_LABEL_STYLE_MAIN, &txtHumi2_style);
  lv_label_set_long_mode(txtHumi2, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txtHumi2, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txtHumi2, "20.3");
  lv_obj_set_size(txtHumi2, 0, 0);
  lv_obj_align(txtHumi2, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -24, -38);
  
  lv_obj_set_hidden(txtHumi2, false);
  /* ====== END of txtHumi2 ====== */
  
  /* ========== txt9 ========== */
  static lv_style_t txt9_style;
  lv_obj_t* txt9;
  
  lv_style_copy(&txt9_style, &lv_style_plain);
  txt9_style.text.color = lv_color_hex(0x000000);
  txt9_style.text.font = &Kanit_Regular_16;
  
  txt9 = lv_label_create(humi2Box, NULL);
  lv_label_set_style(txt9, LV_LABEL_STYLE_MAIN, &txt9_style);
  lv_label_set_long_mode(txt9, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txt9, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txt9, "%");
  lv_obj_set_size(txt9, 0, 0);
  lv_obj_align(txt9, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -40);
  
  lv_obj_set_hidden(txt9, false);
  /* ====== END of txt9 ====== */
  
  /* ========== img3 ========== */
  lv_obj_t* img3;
  
  img3 = lv_img_create(humi2Box, NULL);
  lv_img_set_src(img3, &img_humidity2);
  lv_obj_align(img3, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 20);
  
  lv_obj_set_hidden(img3, false);
  /* ====== END of img3 ====== */
  
  /* ========== txtLight ========== */
  lv_style_copy(&txtLight_style, &lv_style_plain);
  txtLight_style.text.color = lv_color_hex(0x000000);
  txtLight_style.text.font = &Kanit_Regular_20;
  
  txtLight = lv_label_create(lightBox, NULL);
  lv_label_set_style(txtLight, LV_LABEL_STYLE_MAIN, &txtLight_style);
  lv_label_set_long_mode(txtLight, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txtLight, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txtLight, "20.3");
  lv_obj_set_size(txtLight, 0, 0);
  lv_obj_align(txtLight, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -47, -38);
  
  lv_obj_set_hidden(txtLight, false);
  /* ====== END of txtLight ====== */
  
  /* ========== txt12 ========== */
  static lv_style_t txt12_style;
  lv_obj_t* txt12;
  
  lv_style_copy(&txt12_style, &lv_style_plain);
  txt12_style.text.color = lv_color_hex(0x000000);
  txt12_style.text.font = &Kanit_Regular_14;
  
  txt12 = lv_label_create(lightBox, NULL);
  lv_label_set_style(txt12, LV_LABEL_STYLE_MAIN, &txt12_style);
  lv_label_set_long_mode(txt12, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txt12, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txt12, "แสงสว่าง");
  lv_obj_set_size(txt12, 0, 0);
  lv_obj_align(txt12, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -20);
  
  lv_obj_set_hidden(txt12, false);
  /* ====== END of txt12 ====== */
  
  /* ========== txt13 ========== */
  static lv_style_t txt13_style;
  lv_obj_t* txt13;
  
  lv_style_copy(&txt13_style, &lv_style_plain);
  txt13_style.text.color = lv_color_hex(0x000000);
  txt13_style.text.font = &Kanit_Regular_16;
  
  txt13 = lv_label_create(lightBox, NULL);
  lv_label_set_style(txt13, LV_LABEL_STYLE_MAIN, &txt13_style);
  lv_label_set_long_mode(txt13, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txt13, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txt13, "kLux");
  lv_obj_set_size(txt13, 0, 0);
  lv_obj_align(txt13, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -40);
  
  lv_obj_set_hidden(txt13, false);
  /* ====== END of txt13 ====== */
  
  /* ========== img4 ========== */
  lv_obj_t* img4;
  
  img4 = lv_img_create(lightBox, NULL);
  lv_img_set_src(img4, &img_sun);
  lv_obj_align(img4, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 20);
  
  lv_obj_set_hidden(img4, false);
  /* ====== END of img4 ====== */
  
  /* ========== topBar ========== */
  static lv_style_t topBar_style;
  lv_obj_t* topBar;
  
  lv_style_copy(&topBar_style, &lv_style_plain);
  topBar_style.body.main_color = lv_color_hex(0x0ea661);
  topBar_style.body.grad_color = lv_color_hex(0x0ea661);
  topBar_style.body.radius = 0;
  topBar_style.body.opa = 255;
  topBar_style.body.border.color = lv_color_hex(0x000000);
  topBar_style.body.border.width = 0;
  topBar_style.body.border.opa = 255;
  topBar_style.body.shadow.color = lv_color_hex(0x000000);
  topBar_style.body.shadow.width = 0;
  topBar_style.body.shadow.type = LV_SHADOW_FULL;
  
  topBar = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_style(topBar, &topBar_style);
  lv_obj_set_size(topBar, 320, 50);
  lv_obj_align(topBar, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
  
  lv_obj_set_hidden(topBar, false);
  /* ====== END of topBar ====== */
  
  /* ========== imgWiFi ========== */
  imgWiFi = lv_img_create(topBar, NULL);
  lv_img_set_src(imgWiFi, &img_wifi);
  lv_obj_align(imgWiFi, NULL, LV_ALIGN_IN_RIGHT_MID, -20, 0);
  
  lv_obj_set_hidden(imgWiFi, false);
  /* ====== END of imgWiFi ====== */
  
  /* ========== imgNexpie ========== */
  imgNexpie = lv_img_create(topBar, NULL);
  lv_img_set_src(imgNexpie, &img_cloud_computing);
  lv_obj_align(imgNexpie, NULL, LV_ALIGN_IN_RIGHT_MID, -50, 0);
  
  lv_obj_set_hidden(imgNexpie, false);
  /* ====== END of imgNexpie ====== */
  
  /* ========== txt14 ========== */
  static lv_style_t txt14_style;
  lv_obj_t* txt14;
  
  lv_style_copy(&txt14_style, &lv_style_plain);
  txt14_style.text.color = lv_color_hex(0x000000);
  txt14_style.text.font = &Kanit_Regular_16;
  
  txt14 = lv_label_create(tempBox, NULL);
  lv_label_set_style(txt14, LV_LABEL_STYLE_MAIN, &txt14_style);
  lv_label_set_long_mode(txt14, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txt14, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txt14, "*C");
  lv_obj_set_size(txt14, 0, 0);
  lv_obj_align(txt14, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -40);
  
  lv_obj_set_hidden(txt14, false);
  /* ====== END of txt14 ====== */
  
  /* ========== txtTime ========== */
  lv_style_copy(&txtTime_style, &lv_style_plain);
  txtTime_style.text.color = lv_color_hex(0xFFFFFF);
  txtTime_style.text.font = &Kanit_Regular_20;
  
  txtTime = lv_label_create(topBar, NULL);
  lv_label_set_style(txtTime, LV_LABEL_STYLE_MAIN, &txtTime_style);
  lv_label_set_long_mode(txtTime, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txtTime, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txtTime, "Hello");
  lv_obj_set_size(txtTime, 0, 0);
  lv_obj_align(txtTime, NULL, LV_ALIGN_IN_LEFT_MID, 20, 0);
  
  lv_obj_set_hidden(txtTime, false);
  /* ====== END of txtTime ====== */
}
