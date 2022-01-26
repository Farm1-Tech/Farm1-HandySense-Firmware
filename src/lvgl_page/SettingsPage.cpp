/* ======== Generate by IOXGD Designer ======== */
#include "lvgl.h"

LV_FONT_DECLARE(Kanit_Regular_20);
LV_FONT_DECLARE(Kanit_Regular_16);
LV_FONT_DECLARE(Kanit_Regular_14);

lv_obj_t* SettingsScreen;

/* ========== MainBoxQRConfigs header ========== */
static lv_style_t MainBoxQRConfigs_style;
lv_obj_t* MainBoxQRConfigs;
/* ====== END of MainBoxQRConfigs header ====== */

/* ========== txtHeader header ========== */
static lv_style_t txtHeader_style;
lv_obj_t* txtHeader;
/* ====== END of txtHeader header ====== */

/* ========== img7 header ========== */
LV_IMG_DECLARE(img_arrow_left);
/* ====== END of img7 header ====== */

/* ========== objBoxQRCode header ========== */
static lv_style_t objBoxQRCode_style;
lv_obj_t* objBoxQRCode;
/* ====== END of objBoxQRCode header ====== */

/* ========== txtWiFiSSID header ========== */
static lv_style_t txtWiFiSSID_style;
lv_obj_t* txtWiFiSSID;
/* ====== END of txtWiFiSSID header ====== */

/* ========== txtWiFiPassword header ========== */
static lv_style_t txtWiFiPassword_style;
lv_obj_t* txtWiFiPassword;
/* ====== END of txtWiFiPassword header ====== */


void load_page_settings() {
  SettingsScreen = lv_obj_create(NULL, NULL);

  static lv_style_t style_screen;
  lv_style_copy(&style_screen, &lv_style_plain);
  style_screen.body.main_color = lv_color_hex(0xFFFFFF);
  style_screen.body.grad_color = lv_color_hex(0xFFFFFF);
  lv_obj_set_style(SettingsScreen, &style_screen);
  
  /* ========== MainBoxQRConfigs ========== */
  lv_style_copy(&MainBoxQRConfigs_style, &lv_style_plain);
  MainBoxQRConfigs_style.body.main_color = lv_color_hex(0xf9f9f9);
  MainBoxQRConfigs_style.body.grad_color = lv_color_hex(0xf9f9f9);
  MainBoxQRConfigs_style.body.radius = 0;
  MainBoxQRConfigs_style.body.opa = 255;
  MainBoxQRConfigs_style.body.border.color = lv_color_hex(0x000000);
  MainBoxQRConfigs_style.body.border.width = 0;
  MainBoxQRConfigs_style.body.border.opa = 255;
  MainBoxQRConfigs_style.body.shadow.color = lv_color_hex(0x000000);
  MainBoxQRConfigs_style.body.shadow.width = 0;
  MainBoxQRConfigs_style.body.shadow.type = LV_SHADOW_FULL;
  
  MainBoxQRConfigs = lv_obj_create(SettingsScreen, NULL);
  lv_obj_set_style(MainBoxQRConfigs, &MainBoxQRConfigs_style);
  lv_obj_set_size(MainBoxQRConfigs, 320, 190);
  lv_obj_align(MainBoxQRConfigs, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 50);
  
  lv_obj_set_hidden(MainBoxQRConfigs, false);
  /* ====== END of MainBoxQRConfigs ====== */
  
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
  lv_obj_align(txtHeader, NULL, LV_ALIGN_CENTER, -90, 0);
  
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
  
  /* ========== objBoxQRCode ========== */
  lv_style_copy(&objBoxQRCode_style, &lv_style_plain);
  objBoxQRCode_style.body.main_color = lv_color_hex(0xFFFFFF);
  objBoxQRCode_style.body.grad_color = lv_color_hex(0xFFFFFF);
  objBoxQRCode_style.body.radius = 10;
  objBoxQRCode_style.body.opa = 255;
  objBoxQRCode_style.body.border.color = lv_color_hex(0x000000);
  objBoxQRCode_style.body.border.width = 0;
  objBoxQRCode_style.body.border.opa = 255;
  objBoxQRCode_style.body.shadow.color = lv_color_hex(0xBCBCBC);
  objBoxQRCode_style.body.shadow.width = 6;
  objBoxQRCode_style.body.shadow.type = LV_SHADOW_FULL;
  
  objBoxQRCode = lv_obj_create(MainBoxQRConfigs, NULL);
  lv_obj_set_style(objBoxQRCode, &objBoxQRCode_style);
  lv_obj_set_size(objBoxQRCode, 160, 160);
  lv_obj_align(objBoxQRCode, NULL, LV_ALIGN_IN_LEFT_MID, 20, 0);
  
  lv_obj_set_hidden(objBoxQRCode, false);
  /* ====== END of objBoxQRCode ====== */
  
  /* ========== txt1 ========== */
  static lv_style_t txt1_style;
  lv_obj_t* txt1;
  
  lv_style_copy(&txt1_style, &lv_style_plain);
  txt1_style.text.color = lv_color_hex(0x000000);
  txt1_style.text.font = &Kanit_Regular_16;
  
  txt1 = lv_label_create(MainBoxQRConfigs, NULL);
  lv_label_set_style(txt1, LV_LABEL_STYLE_MAIN, &txt1_style);
  lv_label_set_long_mode(txt1, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txt1, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txt1, "ชื่อ WiFi");
  lv_obj_set_size(txt1, 0, 0);
  lv_obj_align(txt1, NULL, LV_ALIGN_IN_TOP_LEFT, 200, 20);
  
  lv_obj_set_hidden(txt1, false);
  /* ====== END of txt1 ====== */
  
  /* ========== objBoxWiFiName ========== */
  static lv_style_t objBoxWiFiName_style;
  lv_obj_t* objBoxWiFiName;
  
  lv_style_copy(&objBoxWiFiName_style, &lv_style_plain);
  objBoxWiFiName_style.body.main_color = lv_color_hex(0xFFFFFF);
  objBoxWiFiName_style.body.grad_color = lv_color_hex(0xFFFFFF);
  objBoxWiFiName_style.body.radius = 6;
  objBoxWiFiName_style.body.opa = 255;
  objBoxWiFiName_style.body.border.color = lv_color_hex(0x0EA661);
  objBoxWiFiName_style.body.border.width = 2;
  objBoxWiFiName_style.body.border.opa = 255;
  objBoxWiFiName_style.body.shadow.color = lv_color_hex(0x000000);
  objBoxWiFiName_style.body.shadow.width = 0;
  objBoxWiFiName_style.body.shadow.type = LV_SHADOW_FULL;
  
  objBoxWiFiName = lv_obj_create(SettingsScreen, NULL);
  lv_obj_set_style(objBoxWiFiName, &objBoxWiFiName_style);
  lv_obj_set_size(objBoxWiFiName, 100, 30);
  lv_obj_align(objBoxWiFiName, NULL, LV_ALIGN_IN_TOP_LEFT, 200, 90);
  
  lv_obj_set_hidden(objBoxWiFiName, false);
  /* ====== END of objBoxWiFiName ====== */
  
  /* ========== txt2 ========== */
  static lv_style_t txt2_style;
  lv_obj_t* txt2;
  
  lv_style_copy(&txt2_style, &lv_style_plain);
  txt2_style.text.color = lv_color_hex(0x000000);
  txt2_style.text.font = &Kanit_Regular_16;
  
  txt2 = lv_label_create(MainBoxQRConfigs, NULL);
  lv_label_set_style(txt2, LV_LABEL_STYLE_MAIN, &txt2_style);
  lv_label_set_long_mode(txt2, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txt2, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txt2, "รหัสผ่าน WiFi");
  lv_obj_set_size(txt2, 0, 0);
  lv_obj_align(txt2, NULL, LV_ALIGN_IN_TOP_LEFT, 200, 80);
  
  lv_obj_set_hidden(txt2, false);
  /* ====== END of txt2 ====== */
  
  /* ========== objBoxWiFiPassword ========== */
  static lv_style_t objBoxWiFiPassword_style;
  lv_obj_t* objBoxWiFiPassword;
  
  lv_style_copy(&objBoxWiFiPassword_style, &lv_style_plain);
  objBoxWiFiPassword_style.body.main_color = lv_color_hex(0xFFFFFF);
  objBoxWiFiPassword_style.body.grad_color = lv_color_hex(0xFFFFFF);
  objBoxWiFiPassword_style.body.radius = 6;
  objBoxWiFiPassword_style.body.opa = 255;
  objBoxWiFiPassword_style.body.border.color = lv_color_hex(0x0EA661);
  objBoxWiFiPassword_style.body.border.width = 2;
  objBoxWiFiPassword_style.body.border.opa = 255;
  objBoxWiFiPassword_style.body.shadow.color = lv_color_hex(0x000000);
  objBoxWiFiPassword_style.body.shadow.width = 0;
  objBoxWiFiPassword_style.body.shadow.type = LV_SHADOW_FULL;
  
  objBoxWiFiPassword = lv_obj_create(SettingsScreen, NULL);
  lv_obj_set_style(objBoxWiFiPassword, &objBoxWiFiPassword_style);
  lv_obj_set_size(objBoxWiFiPassword, 100, 30);
  lv_obj_align(objBoxWiFiPassword, NULL, LV_ALIGN_IN_TOP_LEFT, 200, 150);
  
  lv_obj_set_hidden(objBoxWiFiPassword, false);
  /* ====== END of objBoxWiFiPassword ====== */
  
  /* ========== txt3 ========== */
  static lv_style_t txt3_style;
  lv_obj_t* txt3;
  
  lv_style_copy(&txt3_style, &lv_style_plain);
  txt3_style.text.color = lv_color_hex(0xFF0000);
  txt3_style.text.font = &Kanit_Regular_14;
  
  txt3 = lv_label_create(MainBoxQRConfigs, NULL);
  lv_label_set_style(txt3, LV_LABEL_STYLE_MAIN, &txt3_style);
  lv_label_set_long_mode(txt3, LV_LABEL_LONG_BREAK);
  lv_label_set_align(txt3, LV_LABEL_ALIGN_CENTER);
  lv_label_set_text(txt3, "สแกน QR Code เพื่อเชื่อมต่อ");
  lv_obj_set_size(txt3, 120, 0);
  lv_obj_align(txt3, NULL, LV_ALIGN_IN_TOP_LEFT, 190, 140);
  
  lv_obj_set_hidden(txt3, false);
  /* ====== END of txt3 ====== */
  
  /* ========== txtWiFiSSID ========== */
  lv_style_copy(&txtWiFiSSID_style, &lv_style_plain);
  txtWiFiSSID_style.text.color = lv_color_hex(0x000000);
  txtWiFiSSID_style.text.font = &Kanit_Regular_16;
  
  txtWiFiSSID = lv_label_create(objBoxWiFiName, NULL);
  lv_label_set_style(txtWiFiSSID, LV_LABEL_STYLE_MAIN, &txtWiFiSSID_style);
  lv_label_set_long_mode(txtWiFiSSID, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txtWiFiSSID, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txtWiFiSSID, "Farm1");
  lv_obj_set_size(txtWiFiSSID, 0, 0);
  lv_obj_align(txtWiFiSSID, NULL, LV_ALIGN_CENTER, 0, 0);
  
  lv_obj_set_hidden(txtWiFiSSID, false);
  /* ====== END of txtWiFiSSID ====== */
  
  /* ========== txtWiFiPassword ========== */
  lv_style_copy(&txtWiFiPassword_style, &lv_style_plain);
  txtWiFiPassword_style.text.color = lv_color_hex(0x000000);
  txtWiFiPassword_style.text.font = &Kanit_Regular_16;
  
  txtWiFiPassword = lv_label_create(objBoxWiFiPassword, NULL);
  lv_label_set_style(txtWiFiPassword, LV_LABEL_STYLE_MAIN, &txtWiFiPassword_style);
  lv_label_set_long_mode(txtWiFiPassword, LV_LABEL_LONG_EXPAND);
  lv_label_set_align(txtWiFiPassword, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(txtWiFiPassword, "123456789");
  lv_obj_set_size(txtWiFiPassword, 0, 0);
  lv_obj_align(txtWiFiPassword, NULL, LV_ALIGN_CENTER, 0, 0);
  
  lv_obj_set_hidden(txtWiFiPassword, false);
  /* ====== END of txtWiFiPassword ====== */
}
