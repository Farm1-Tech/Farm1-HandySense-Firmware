/* ======== Generate by IOXGD Designer ======== */
#include "lvgl.h"

LV_FONT_DECLARE(Kanit_Regular_20);
LV_FONT_DECLARE(Kanit_Regular_16);
LV_FONT_DECLARE(Kanit_Regular_14);

lv_obj_t* SettingsScreen;

/* ========== MainWiFiConfigs header ========== */
static lv_style_t MainWiFiConfigs_style;
lv_obj_t* MainWiFiConfigs;
/* ====== END of MainWiFiConfigs header ====== */

/* ========== txtHeader header ========== */
static lv_style_t txtHeader_style;
lv_obj_t* txtHeader;
/* ====== END of txtHeader header ====== */

/* ========== img7 header ========== */
LV_IMG_DECLARE(img_arrow_left);
/* ====== END of img7 header ====== */

/* ========== wifiSSIDBox header ========== */
static lv_style_t wifiSSIDBox_style;
lv_obj_t* wifiSSIDBox;
/* ====== END of wifiSSIDBox header ====== */

/* ========== wifiPasswordBox header ========== */
static lv_style_t wifiPasswordBox_style;
lv_obj_t* wifiPasswordBox;
/* ====== END of wifiPasswordBox header ====== */

/* ========== MainSensorConfigs header ========== */
static lv_style_t MainSensorConfigs_style;
lv_obj_t* MainSensorConfigs;
/* ====== END of MainSensorConfigs header ====== */

/* ========== objPosTempSensorSelect header ========== */
static lv_style_t objPosTempSensorSelect_style;
lv_obj_t* objPosTempSensorSelect;
/* ====== END of objPosTempSensorSelect header ====== */

/* ========== objPosHumiSensorSelect header ========== */
static lv_style_t objPosHumiSensorSelect_style;
lv_obj_t* objPosHumiSensorSelect;
/* ====== END of objPosHumiSensorSelect header ====== */

/* ========== objPosSoilSensorSelect header ========== */
static lv_style_t objPosSoilSensorSelect_style;
lv_obj_t* objPosSoilSensorSelect;
/* ====== END of objPosSoilSensorSelect header ====== */

/* ========== objPosLightSensorSelect header ========== */
static lv_style_t objPosLightSensorSelect_style;
lv_obj_t* objPosLightSensorSelect;
/* ====== END of objPosLightSensorSelect header ====== */

/* ========== btnSettingsWiFi header ========== */
lv_style_t btnSettingsWiFi_rel_style;
static lv_style_t btnSettingsWiFi_pr_style;
lv_obj_t* btnSettingsWiFi;
extern void btnSettingsWiFiHandle(lv_obj_t*, lv_event_t);
static lv_style_t btnSettingsWiFi_label_style;
lv_obj_t* btnSettingsWiFi_label;
/* ====== END of btnSettingsWiFi header ====== */

/* ========== img8 header ========== */
LV_IMG_DECLARE(img_wifi);
/* ====== END of img8 header ====== */

/* ========== btnSettingsSensor header ========== */
lv_style_t btnSettingsSensor_rel_style;
static lv_style_t btnSettingsSensor_pr_style;
lv_obj_t* btnSettingsSensor;
extern void btnSettingsSensorHandle(lv_obj_t*, lv_event_t);
static lv_style_t btnSettingsSensor_label_style;
lv_obj_t* btnSettingsSensor_label;
/* ====== END of btnSettingsSensor header ====== */

/* ========== img9 header ========== */
LV_IMG_DECLARE(img_sensor);
/* ====== END of img9 header ====== */


void load_page_settings() {
  SettingsScreen = lv_obj_create(NULL, NULL);

  static lv_style_t style_screen;
  lv_style_copy(&style_screen, &lv_style_plain);
  style_screen.body.main_color = lv_color_hex(0xFFFFFF);
  style_screen.body.grad_color = lv_color_hex(0xFFFFFF);
  lv_obj_set_style(SettingsScreen, &style_screen);
  
  /* ========== MainWiFiConfigs ========== */
  lv_style_copy(&MainWiFiConfigs_style, &lv_style_plain);
  MainWiFiConfigs_style.body.main_color = lv_color_hex(0xf9f9f9);
  MainWiFiConfigs_style.body.grad_color = lv_color_hex(0xf9f9f9);
  MainWiFiConfigs_style.body.radius = 0;
  MainWiFiConfigs_style.body.opa = 255;
  MainWiFiConfigs_style.body.border.color = lv_color_hex(0x000000);
  MainWiFiConfigs_style.body.border.width = 0;
  MainWiFiConfigs_style.body.border.opa = 255;
  MainWiFiConfigs_style.body.shadow.color = lv_color_hex(0x000000);
  MainWiFiConfigs_style.body.shadow.width = 0;
  MainWiFiConfigs_style.body.shadow.type = LV_SHADOW_FULL;
  
  MainWiFiConfigs = lv_obj_create(SettingsScreen, NULL);
  lv_obj_set_style(MainWiFiConfigs, &MainWiFiConfigs_style);
  lv_obj_set_size(MainWiFiConfigs, 320, 190);
  lv_obj_align(MainWiFiConfigs, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 50);
  
  lv_obj_set_hidden(MainWiFiConfigs, false);
  /* ====== END of MainWiFiConfigs ====== */
  
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
  
  topBar = lv_obj_create(SettingsScreen, NULL);
  lv_obj_set_style(topBar, &topBar_style);
  lv_obj_set_size(topBar, 320, 50);
  lv_obj_align(topBar, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
  
  lv_obj_set_hidden(topBar, false);
  /* ====== END of topBar ====== */
  
  /* ========== txtHeader ========== */
  lv_style_copy(&txtHeader_style, &lv_style_plain);
  txtHeader_style.text.color = lv_color_hex(0xFFFFFF);
  txtHeader_style.text.font = &Kanit_Regular_20;
  
  txtHeader = lv_label_create(topBar, NULL);
  lv_label_set_style(txtHeader, LV_LABEL_STYLE_MAIN, &txtHeader_style);
  lv_label_set_long_mode(txtHeader, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txtHeader, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txtHeader, "ตั้งค่า");
  lv_obj_set_size(txtHeader, 0, 0);
  lv_obj_align(txtHeader, NULL, LV_ALIGN_CENTER, -80, 0);
  
  lv_obj_set_hidden(txtHeader, false);
  /* ====== END of txtHeader ====== */
  
  /* ========== btn1 ========== */
  static lv_style_t btn1_rel_style;
  static lv_style_t btn1_pr_style;
  lv_obj_t* btn1;
  extern void SettingsScreenGoBackHandle(lv_obj_t*, lv_event_t);
  static lv_style_t btn1_label_style;
  lv_obj_t* btn1_label;
  
  lv_style_copy(&btn1_rel_style, &lv_style_plain);
  btn1_rel_style.body.main_color = lv_color_hex(0x0EA661);
  btn1_rel_style.body.grad_color = lv_color_hex(0x0EA661);
  btn1_rel_style.body.radius = 0;
  btn1_rel_style.body.border.color = lv_color_hex(0x0B1928);
  btn1_rel_style.body.border.width = 0;
  
  lv_style_copy(&btn1_pr_style, &lv_style_plain);
  btn1_pr_style.body.main_color = lv_color_hex(0x0C8950);
  btn1_pr_style.body.grad_color = lv_color_hex(0x0C8950);
  btn1_pr_style.body.radius = 0;
  btn1_pr_style.body.border.color = lv_color_hex(0x0B1928);
  btn1_pr_style.body.border.width = 0;
  
  btn1 = lv_btn_create(topBar, NULL);
  lv_obj_set_event_cb(btn1, SettingsScreenGoBackHandle);
  lv_btn_set_style(btn1, LV_BTN_STATE_REL, &btn1_rel_style);
  lv_btn_set_style(btn1, LV_BTN_STATE_PR, &btn1_pr_style);
  lv_obj_set_size(btn1, 40, 50);
  lv_obj_align(btn1, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
  
  lv_style_copy(&btn1_label_style, &lv_style_plain);
  btn1_label_style.text.color = lv_color_hex(0xFFFFFF);
  btn1_label_style.text.font = &lv_font_roboto_16;
  btn1_label = lv_label_create(btn1, NULL);
  lv_label_set_style(btn1_label, LV_LABEL_STYLE_MAIN, &btn1_label_style);
  lv_label_set_text(btn1_label, "");
  
  lv_obj_set_hidden(btn1, false);
  /* ====== END of btn1 ====== */
  
  /* ========== img7 ========== */
  lv_obj_t* img7;
  
  img7 = lv_img_create(topBar, NULL);
  lv_img_set_src(img7, &img_arrow_left);
  lv_obj_align(img7, NULL, LV_ALIGN_IN_LEFT_MID, 10, 0);
  
  lv_obj_set_hidden(img7, false);
  /* ====== END of img7 ====== */
  
  /* ========== txt1 ========== */
  static lv_style_t txt1_style;
  lv_obj_t* txt1;
  
  lv_style_copy(&txt1_style, &lv_style_plain);
  txt1_style.text.color = lv_color_hex(0x000000);
  txt1_style.text.font = &Kanit_Regular_16;
  
  txt1 = lv_label_create(MainWiFiConfigs, NULL);
  lv_label_set_style(txt1, LV_LABEL_STYLE_MAIN, &txt1_style);
  lv_label_set_long_mode(txt1, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txt1, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txt1, "ชื่อ WiFi");
  lv_obj_set_size(txt1, 0, 0);
  lv_obj_align(txt1, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 20);
  
  lv_obj_set_hidden(txt1, false);
  /* ====== END of txt1 ====== */
  
  /* ========== wifiSSIDBox ========== */
  lv_style_copy(&wifiSSIDBox_style, &lv_style_plain);
  wifiSSIDBox_style.body.main_color = lv_color_hex(0xFFFFFF);
  wifiSSIDBox_style.body.grad_color = lv_color_hex(0xFFFFFF);
  wifiSSIDBox_style.body.radius = 6;
  wifiSSIDBox_style.body.opa = 255;
  wifiSSIDBox_style.body.border.color = lv_color_hex(0x0EA661);
  wifiSSIDBox_style.body.border.width = 2;
  wifiSSIDBox_style.body.border.opa = 255;
  wifiSSIDBox_style.body.shadow.color = lv_color_hex(0x000000);
  wifiSSIDBox_style.body.shadow.width = 0;
  wifiSSIDBox_style.body.shadow.type = LV_SHADOW_FULL;
  
  wifiSSIDBox = lv_obj_create(MainWiFiConfigs, NULL);
  lv_obj_set_style(wifiSSIDBox, &wifiSSIDBox_style);
  lv_obj_set_size(wifiSSIDBox, 300, 40);
  lv_obj_align(wifiSSIDBox, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 40);
  
  lv_obj_set_hidden(wifiSSIDBox, false);
  /* ====== END of wifiSSIDBox ====== */
  
  /* ========== txt2 ========== */
  static lv_style_t txt2_style;
  lv_obj_t* txt2;
  
  lv_style_copy(&txt2_style, &lv_style_plain);
  txt2_style.text.color = lv_color_hex(0x000000);
  txt2_style.text.font = &Kanit_Regular_16;
  
  txt2 = lv_label_create(MainWiFiConfigs, NULL);
  lv_label_set_style(txt2, LV_LABEL_STYLE_MAIN, &txt2_style);
  lv_label_set_long_mode(txt2, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txt2, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txt2, "รหัสผ่าน WiFi");
  lv_obj_set_size(txt2, 0, 0);
  lv_obj_align(txt2, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 90);
  
  lv_obj_set_hidden(txt2, false);
  /* ====== END of txt2 ====== */
  
  /* ========== wifiPasswordBox ========== */
  lv_style_copy(&wifiPasswordBox_style, &lv_style_plain);
  wifiPasswordBox_style.body.main_color = lv_color_hex(0xFFFFFF);
  wifiPasswordBox_style.body.grad_color = lv_color_hex(0xFFFFFF);
  wifiPasswordBox_style.body.radius = 6;
  wifiPasswordBox_style.body.opa = 255;
  wifiPasswordBox_style.body.border.color = lv_color_hex(0x0EA661);
  wifiPasswordBox_style.body.border.width = 2;
  wifiPasswordBox_style.body.border.opa = 255;
  wifiPasswordBox_style.body.shadow.color = lv_color_hex(0x000000);
  wifiPasswordBox_style.body.shadow.width = 0;
  wifiPasswordBox_style.body.shadow.type = LV_SHADOW_FULL;
  
  wifiPasswordBox = lv_obj_create(MainWiFiConfigs, NULL);
  lv_obj_set_style(wifiPasswordBox, &wifiPasswordBox_style);
  lv_obj_set_size(wifiPasswordBox, 300, 40);
  lv_obj_align(wifiPasswordBox, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 110);
  
  lv_obj_set_hidden(wifiPasswordBox, false);
  /* ====== END of wifiPasswordBox ====== */
  
  /* ========== MainSensorConfigs ========== */
  lv_style_copy(&MainSensorConfigs_style, &lv_style_plain);
  MainSensorConfigs_style.body.main_color = lv_color_hex(0xf9f9f9);
  MainSensorConfigs_style.body.grad_color = lv_color_hex(0xf9f9f9);
  MainSensorConfigs_style.body.radius = 0;
  MainSensorConfigs_style.body.opa = 255;
  MainSensorConfigs_style.body.border.color = lv_color_hex(0x000000);
  MainSensorConfigs_style.body.border.width = 0;
  MainSensorConfigs_style.body.border.opa = 255;
  MainSensorConfigs_style.body.shadow.color = lv_color_hex(0x000000);
  MainSensorConfigs_style.body.shadow.width = 0;
  MainSensorConfigs_style.body.shadow.type = LV_SHADOW_FULL;
  
  MainSensorConfigs = lv_obj_create(SettingsScreen, NULL);
  lv_obj_set_style(MainSensorConfigs, &MainSensorConfigs_style);
  lv_obj_set_size(MainSensorConfigs, 320, 190);
  lv_obj_align(MainSensorConfigs, NULL, LV_ALIGN_IN_TOP_LEFT, 320, 50);
  
  lv_obj_set_hidden(MainSensorConfigs, false);
  /* ====== END of MainSensorConfigs ====== */
  
  /* ========== txtTempSensorLabel ========== */
  static lv_style_t txtTempSensorLabel_style;
  lv_obj_t* txtTempSensorLabel;
  
  lv_style_copy(&txtTempSensorLabel_style, &lv_style_plain);
  txtTempSensorLabel_style.text.color = lv_color_hex(0x000000);
  txtTempSensorLabel_style.text.font = &Kanit_Regular_14;
  
  txtTempSensorLabel = lv_label_create(MainSensorConfigs, NULL);
  lv_label_set_style(txtTempSensorLabel, LV_LABEL_STYLE_MAIN, &txtTempSensorLabel_style);
  lv_label_set_long_mode(txtTempSensorLabel, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txtTempSensorLabel, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txtTempSensorLabel, "เซ็นเซอร์อุณหภูมิ");
  lv_obj_set_size(txtTempSensorLabel, 0, 0);
  lv_obj_align(txtTempSensorLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 20);
  
  lv_obj_set_hidden(txtTempSensorLabel, false);
  /* ====== END of txtTempSensorLabel ====== */
  
  /* ========== txtHumiSensorLabel ========== */
  static lv_style_t txtHumiSensorLabel_style;
  lv_obj_t* txtHumiSensorLabel;
  
  lv_style_copy(&txtHumiSensorLabel_style, &lv_style_plain);
  txtHumiSensorLabel_style.text.color = lv_color_hex(0x000000);
  txtHumiSensorLabel_style.text.font = &Kanit_Regular_14;
  
  txtHumiSensorLabel = lv_label_create(MainSensorConfigs, NULL);
  lv_label_set_style(txtHumiSensorLabel, LV_LABEL_STYLE_MAIN, &txtHumiSensorLabel_style);
  lv_label_set_long_mode(txtHumiSensorLabel, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txtHumiSensorLabel, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txtHumiSensorLabel, "เซ็นเซอร์ความชื้นอากาศ");
  lv_obj_set_size(txtHumiSensorLabel, 0, 0);
  lv_obj_align(txtHumiSensorLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 170, 20);
  
  lv_obj_set_hidden(txtHumiSensorLabel, false);
  /* ====== END of txtHumiSensorLabel ====== */
  
  /* ========== objPosTempSensorSelect ========== */
  lv_style_copy(&objPosTempSensorSelect_style, &lv_style_plain);
  objPosTempSensorSelect_style.body.main_color = lv_color_hex(0xFFFFFF);
  objPosTempSensorSelect_style.body.grad_color = lv_color_hex(0xFFFFFF);
  objPosTempSensorSelect_style.body.radius = 6;
  objPosTempSensorSelect_style.body.opa = 255;
  objPosTempSensorSelect_style.body.border.color = lv_color_hex(0x0EA661);
  objPosTempSensorSelect_style.body.border.width = 2;
  objPosTempSensorSelect_style.body.border.opa = 255;
  objPosTempSensorSelect_style.body.shadow.color = lv_color_hex(0x000000);
  objPosTempSensorSelect_style.body.shadow.width = 0;
  objPosTempSensorSelect_style.body.shadow.type = LV_SHADOW_FULL;
  
  objPosTempSensorSelect = lv_obj_create(MainSensorConfigs, NULL);
  lv_obj_set_style(objPosTempSensorSelect, &objPosTempSensorSelect_style);
  lv_obj_set_size(objPosTempSensorSelect, 140, 40);
  lv_obj_align(objPosTempSensorSelect, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 40);
  
  lv_obj_set_hidden(objPosTempSensorSelect, false);
  /* ====== END of objPosTempSensorSelect ====== */
  
  /* ========== objPosHumiSensorSelect ========== */
  lv_style_copy(&objPosHumiSensorSelect_style, &lv_style_plain);
  objPosHumiSensorSelect_style.body.main_color = lv_color_hex(0xFFFFFF);
  objPosHumiSensorSelect_style.body.grad_color = lv_color_hex(0xFFFFFF);
  objPosHumiSensorSelect_style.body.radius = 6;
  objPosHumiSensorSelect_style.body.opa = 255;
  objPosHumiSensorSelect_style.body.border.color = lv_color_hex(0x0EA661);
  objPosHumiSensorSelect_style.body.border.width = 2;
  objPosHumiSensorSelect_style.body.border.opa = 255;
  objPosHumiSensorSelect_style.body.shadow.color = lv_color_hex(0x000000);
  objPosHumiSensorSelect_style.body.shadow.width = 0;
  objPosHumiSensorSelect_style.body.shadow.type = LV_SHADOW_FULL;
  
  objPosHumiSensorSelect = lv_obj_create(MainSensorConfigs, NULL);
  lv_obj_set_style(objPosHumiSensorSelect, &objPosHumiSensorSelect_style);
  lv_obj_set_size(objPosHumiSensorSelect, 140, 40);
  lv_obj_align(objPosHumiSensorSelect, NULL, LV_ALIGN_IN_TOP_LEFT, 170, 40);
  
  lv_obj_set_hidden(objPosHumiSensorSelect, false);
  /* ====== END of objPosHumiSensorSelect ====== */
  
  /* ========== txt3 ========== */
  static lv_style_t txt3_style;
  lv_obj_t* txt3;
  
  lv_style_copy(&txt3_style, &lv_style_plain);
  txt3_style.text.color = lv_color_hex(0x000000);
  txt3_style.text.font = &Kanit_Regular_14;
  
  txt3 = lv_label_create(MainSensorConfigs, NULL);
  lv_label_set_style(txt3, LV_LABEL_STYLE_MAIN, &txt3_style);
  lv_label_set_long_mode(txt3, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txt3, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txt3, "เซ็นเซอร์ความชื้นดิน");
  lv_obj_set_size(txt3, 0, 0);
  lv_obj_align(txt3, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 90);
  
  lv_obj_set_hidden(txt3, false);
  /* ====== END of txt3 ====== */
  
  /* ========== objPosSoilSensorSelect ========== */
  lv_style_copy(&objPosSoilSensorSelect_style, &lv_style_plain);
  objPosSoilSensorSelect_style.body.main_color = lv_color_hex(0xFFFFFF);
  objPosSoilSensorSelect_style.body.grad_color = lv_color_hex(0xFFFFFF);
  objPosSoilSensorSelect_style.body.radius = 6;
  objPosSoilSensorSelect_style.body.opa = 255;
  objPosSoilSensorSelect_style.body.border.color = lv_color_hex(0x0EA661);
  objPosSoilSensorSelect_style.body.border.width = 2;
  objPosSoilSensorSelect_style.body.border.opa = 255;
  objPosSoilSensorSelect_style.body.shadow.color = lv_color_hex(0x000000);
  objPosSoilSensorSelect_style.body.shadow.width = 0;
  objPosSoilSensorSelect_style.body.shadow.type = LV_SHADOW_FULL;
  
  objPosSoilSensorSelect = lv_obj_create(MainSensorConfigs, NULL);
  lv_obj_set_style(objPosSoilSensorSelect, &objPosSoilSensorSelect_style);
  lv_obj_set_size(objPosSoilSensorSelect, 140, 40);
  lv_obj_align(objPosSoilSensorSelect, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 110);
  
  lv_obj_set_hidden(objPosSoilSensorSelect, false);
  /* ====== END of objPosSoilSensorSelect ====== */
  
  /* ========== objPosLightSensorSelect ========== */
  lv_style_copy(&objPosLightSensorSelect_style, &lv_style_plain);
  objPosLightSensorSelect_style.body.main_color = lv_color_hex(0xFFFFFF);
  objPosLightSensorSelect_style.body.grad_color = lv_color_hex(0xFFFFFF);
  objPosLightSensorSelect_style.body.radius = 6;
  objPosLightSensorSelect_style.body.opa = 255;
  objPosLightSensorSelect_style.body.border.color = lv_color_hex(0x0EA661);
  objPosLightSensorSelect_style.body.border.width = 2;
  objPosLightSensorSelect_style.body.border.opa = 255;
  objPosLightSensorSelect_style.body.shadow.color = lv_color_hex(0x000000);
  objPosLightSensorSelect_style.body.shadow.width = 0;
  objPosLightSensorSelect_style.body.shadow.type = LV_SHADOW_FULL;
  
  objPosLightSensorSelect = lv_obj_create(MainSensorConfigs, NULL);
  lv_obj_set_style(objPosLightSensorSelect, &objPosLightSensorSelect_style);
  lv_obj_set_size(objPosLightSensorSelect, 140, 40);
  lv_obj_align(objPosLightSensorSelect, NULL, LV_ALIGN_IN_TOP_LEFT, 170, 110);
  
  lv_obj_set_hidden(objPosLightSensorSelect, false);
  /* ====== END of objPosLightSensorSelect ====== */
  
  /* ========== txt4 ========== */
  static lv_style_t txt4_style;
  lv_obj_t* txt4;
  
  lv_style_copy(&txt4_style, &lv_style_plain);
  txt4_style.text.color = lv_color_hex(0x000000);
  txt4_style.text.font = &Kanit_Regular_14;
  
  txt4 = lv_label_create(MainSensorConfigs, NULL);
  lv_label_set_style(txt4, LV_LABEL_STYLE_MAIN, &txt4_style);
  lv_label_set_long_mode(txt4, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txt4, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txt4, "เซ็นเซอร์แสงสว่าง");
  lv_obj_set_size(txt4, 0, 0);
  lv_obj_align(txt4, NULL, LV_ALIGN_IN_TOP_LEFT, 170, 90);
  
  lv_obj_set_hidden(txt4, false);
  /* ====== END of txt4 ====== */
  
  /* ========== btnSettingsWiFi ========== */
  lv_style_copy(&btnSettingsWiFi_rel_style, &lv_style_plain);
  btnSettingsWiFi_rel_style.body.main_color = lv_color_hex(0x0C8950);
  btnSettingsWiFi_rel_style.body.grad_color = lv_color_hex(0x0C8950);
  btnSettingsWiFi_rel_style.body.radius = 0;
  btnSettingsWiFi_rel_style.body.border.color = lv_color_hex(0x0B1928);
  btnSettingsWiFi_rel_style.body.border.width = 0;
  
  lv_style_copy(&btnSettingsWiFi_pr_style, &lv_style_plain);
  btnSettingsWiFi_pr_style.body.main_color = lv_color_hex(0x0A6E40);
  btnSettingsWiFi_pr_style.body.grad_color = lv_color_hex(0x0A6E40);
  btnSettingsWiFi_pr_style.body.radius = 0;
  btnSettingsWiFi_pr_style.body.border.color = lv_color_hex(0x0B1928);
  btnSettingsWiFi_pr_style.body.border.width = 0;
  
  btnSettingsWiFi = lv_btn_create(topBar, NULL);
  lv_obj_set_event_cb(btnSettingsWiFi, btnSettingsWiFiHandle);
  lv_btn_set_style(btnSettingsWiFi, LV_BTN_STATE_REL, &btnSettingsWiFi_rel_style);
  lv_btn_set_style(btnSettingsWiFi, LV_BTN_STATE_PR, &btnSettingsWiFi_pr_style);
  lv_obj_set_size(btnSettingsWiFi, 50, 40);
  lv_obj_align(btnSettingsWiFi, NULL, LV_ALIGN_IN_TOP_LEFT, 170, 10);
  
  lv_style_copy(&btnSettingsWiFi_label_style, &lv_style_plain);
  btnSettingsWiFi_label_style.text.color = lv_color_hex(0xFFFFFF);
  btnSettingsWiFi_label_style.text.font = &lv_font_roboto_16;
  btnSettingsWiFi_label = lv_label_create(btnSettingsWiFi, NULL);
  lv_label_set_style(btnSettingsWiFi_label, LV_LABEL_STYLE_MAIN, &btnSettingsWiFi_label_style);
  lv_label_set_text(btnSettingsWiFi_label, "");
  
  lv_obj_set_hidden(btnSettingsWiFi, false);
  /* ====== END of btnSettingsWiFi ====== */
  
  /* ========== img8 ========== */
  lv_obj_t* img8;
  
  img8 = lv_img_create(topBar, NULL);
  lv_img_set_src(img8, &img_wifi);
  lv_obj_align(img8, NULL, LV_ALIGN_IN_TOP_LEFT, 183, 19);
  
  lv_obj_set_hidden(img8, false);
  /* ====== END of img8 ====== */
  
  /* ========== btnSettingsSensor ========== */
  lv_style_copy(&btnSettingsSensor_rel_style, &lv_style_plain);
  btnSettingsSensor_rel_style.body.main_color = lv_color_hex(0x0EA661);
  btnSettingsSensor_rel_style.body.grad_color = lv_color_hex(0x0EA661);
  btnSettingsSensor_rel_style.body.radius = 0;
  btnSettingsSensor_rel_style.body.border.color = lv_color_hex(0x0B1928);
  btnSettingsSensor_rel_style.body.border.width = 0;
  
  lv_style_copy(&btnSettingsSensor_pr_style, &lv_style_plain);
  btnSettingsSensor_pr_style.body.main_color = lv_color_hex(0x0A6E40);
  btnSettingsSensor_pr_style.body.grad_color = lv_color_hex(0x0A6E40);
  btnSettingsSensor_pr_style.body.radius = 0;
  btnSettingsSensor_pr_style.body.border.color = lv_color_hex(0x0B1928);
  btnSettingsSensor_pr_style.body.border.width = 0;
  
  btnSettingsSensor = lv_btn_create(topBar, NULL);
  lv_obj_set_event_cb(btnSettingsSensor, btnSettingsSensorHandle);
  lv_btn_set_style(btnSettingsSensor, LV_BTN_STATE_REL, &btnSettingsSensor_rel_style);
  lv_btn_set_style(btnSettingsSensor, LV_BTN_STATE_PR, &btnSettingsSensor_pr_style);
  lv_obj_set_size(btnSettingsSensor, 50, 40);
  lv_obj_align(btnSettingsSensor, NULL, LV_ALIGN_IN_TOP_LEFT, 220, 10);
  
  lv_style_copy(&btnSettingsSensor_label_style, &lv_style_plain);
  btnSettingsSensor_label_style.text.color = lv_color_hex(0xFFFFFF);
  btnSettingsSensor_label_style.text.font = &lv_font_roboto_16;
  btnSettingsSensor_label = lv_label_create(btnSettingsSensor, NULL);
  lv_label_set_style(btnSettingsSensor_label, LV_LABEL_STYLE_MAIN, &btnSettingsSensor_label_style);
  lv_label_set_text(btnSettingsSensor_label, "");
  
  lv_obj_set_hidden(btnSettingsSensor, false);
  /* ====== END of btnSettingsSensor ====== */
  
  /* ========== img9 ========== */
  lv_obj_t* img9;
  
  img9 = lv_img_create(SettingsScreen, NULL);
  lv_img_set_src(img9, &img_sensor);
  lv_obj_align(img9, NULL, LV_ALIGN_IN_TOP_LEFT, 232, 20);
  
  lv_obj_set_hidden(img9, false);
  /* ====== END of img9 ====== */
}
