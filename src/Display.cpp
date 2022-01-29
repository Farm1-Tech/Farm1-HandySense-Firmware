#include <Arduino.h>
#include "Display.h"
#include <TFT_eSPI.h>
#include <lvgl.h>
#include <lv_qrcode.h>
#include <WiFi.h>
#include "SensorManager.h"
#include "debug.h"

#define LCD_BL_PIN 32

TFT_eSPI tft = TFT_eSPI();

static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors(&color_p->full, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}


struct {
  uint16_t max_x = 0;
  uint16_t max_y = 0;
  uint16_t min_x = 0;
  uint16_t min_y = 0;
} TouchCalibration;

bool my_input_read(lv_indev_drv_t * drv, lv_indev_data_t*data) {
  uint16_t x = 0, y = 0;
  // bool touched = tft.getTouch(&x, &y, 500);

  // uint16_t x, y;
  tft.getTouchRaw(&y, &x); // Axis wrong
  bool touched = (x > 10) && (y > 10);
  // Serial.printf("raw_x: %5d\traw_y: %5d\n", x, y);

  x = map(x, TouchCalibration.min_x, TouchCalibration.max_x, 28, 320 - 28);
  y = map(y, TouchCalibration.min_y, TouchCalibration.max_y, 28, 240 - 28);

  if (touched) {
    uint16_t xOld = x, yOld = y;
    y += 22.0 / 152.0 * xOld;
    //Serial.printf("Press: %d, %d\n", x, y);
    delay(50);
  } else {
    //Serial.println("No Press");
  }

  data->point.x = x;
  data->point.y = y;
  data->state = touched ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
  
  return false; /*No buffering now so no more data read*/
}

extern void load_page_main() ;

extern lv_obj_t* MainScreen;

extern lv_obj_t* txtTime;
extern lv_obj_t* imgWiFi;
extern lv_obj_t* imgNexpie;

extern lv_obj_t* txtTemp;
extern lv_obj_t* txtHumi;
extern lv_obj_t* txtHumi2;
extern lv_obj_t* txtLight;

extern void load_page_settings() ;

extern lv_obj_t* SettingsScreen;

extern lv_obj_t* objBoxQRCode;
lv_obj_t* wifiConnectQRCode;

extern lv_obj_t* txtWiFiSSID;
extern lv_obj_t* txtWiFiPassword;

extern void load_page_touch_calibration() ;
extern lv_obj_t* TouchCalibrationScreen;

extern lv_obj_t* objTopLeftTouchPoint;
extern lv_obj_t* objBottomLeftTouchPoint;
extern lv_obj_t* objBottomRightTouchPoint;
extern lv_obj_t* objRightLeftTouchPoint;

extern lv_obj_t* txtTouchCalibrationStep;
extern lv_obj_t* txtTouchCalibrationCountdown;

void btnGoToSettingsHandle(lv_obj_t *obj, lv_event_t event) {
  if(event == LV_EVENT_CLICKED) {
    String qr_code_str = "WIFI:T:WPA;S:Farm1;P:123456789;;";
    lv_qrcode_update(wifiConnectQRCode, (char*)qr_code_str.c_str(), qr_code_str.length());
    lv_scr_load(SettingsScreen);
  }
}

void SettingsScreenGoBackHandle(lv_obj_t *obj, lv_event_t event) {
  if(event == LV_EVENT_CLICKED) {
    lv_scr_load(MainScreen);
  }
}

void do_touch_calibration() {
  uint8_t state = 0;
  uint16_t i = 0;
  uint32_t posXsum = 0, posYsum = 0;
  uint8_t posSample = 0;
  while(1) {
    lv_task_handler(); /* let the GUI do its work */
    
    uint16_t x, y;
    // tft.getTouchRaw(&x, &y);
    tft.getTouchRaw(&y, &x); // Axis wrong
    // Serial.printf("x: %5d\ty: %5d\n", x, y);
    /* Serial.printf("x: %i     ", x);
    Serial.printf("y: %i     ", y);
    Serial.printf("z: %i \n", tft.getTouchRawZ());*/
    bool isPressed = (x > 0) && (y > 0);
    
    if (state == 0) {
      // Hide all point
      lv_obj_set_hidden(objTopLeftTouchPoint, true);
      lv_obj_set_hidden(objBottomLeftTouchPoint, true);
      lv_obj_set_hidden(objBottomRightTouchPoint, true);
      lv_obj_set_hidden(objRightLeftTouchPoint, true);
      
      lv_label_set_text(txtTouchCalibrationStep, "");

      // Hide countdown
      lv_obj_set_hidden(txtTouchCalibrationCountdown, true);

      // Show touch calibration screen
      lv_scr_load(TouchCalibrationScreen);
      state = 1;
    }
    if (state == 1) {
      lv_obj_set_hidden(objTopLeftTouchPoint, false);
      lv_label_set_text(txtTouchCalibrationStep, "กดจุดด้านบนซ้ายค้างไว้");
      lv_obj_align(txtTouchCalibrationStep, NULL, LV_ALIGN_CENTER, 0, 0);

      state = 2;
    }
    if (state == 2) {
      if (isPressed) {
        lv_label_set_text(txtTouchCalibrationStep, "กดค้างไว้ซักครู่");
        lv_obj_align(txtTouchCalibrationStep, NULL, LV_ALIGN_CENTER, 0, 0);

        i = 0;
        posXsum = 0;
        posYsum = 0;
        posSample = 0;
        state = 3;
      }
    }
    if (state == 3) {
      if (isPressed) {
        if (i >= 20) {
          posXsum += x;
          posYsum += y;
          posSample++;
          if (posSample >= 10) {
            TouchCalibration.min_x = (float)posXsum / (float)posSample;
            TouchCalibration.min_y = (float)posYsum / (float)posSample;

            lv_label_set_text(txtTouchCalibrationStep, "หยุดกดจุด");
            lv_obj_align(txtTouchCalibrationStep, NULL, LV_ALIGN_CENTER, 0, 0);
            lv_obj_set_hidden(objTopLeftTouchPoint, true);

            i = 0;
            state = 4;
          }
        }
        i++;
      } else {
        state = 1;
      }
    }
    if (state == 4) {
      if (!isPressed) {
        i++;
        if (i > 100) {
          state = 5;
        }
      }
    }
    if (state == 5) {
      lv_obj_set_hidden(objBottomRightTouchPoint, false);
      lv_label_set_text(txtTouchCalibrationStep, "กดจุดด้านล่างขวาค้างไว้");
      lv_obj_align(txtTouchCalibrationStep, NULL, LV_ALIGN_CENTER, 0, 0);

      state = 6;
    }
    if (state == 6) {
      if (isPressed) {
        lv_label_set_text(txtTouchCalibrationStep, "กดค้างไว้ซักครู่");
        lv_obj_align(txtTouchCalibrationStep, NULL, LV_ALIGN_CENTER, 0, 0);

        i = 0;
        posXsum = 0;
        posYsum = 0;
        posSample = 0;
        state = 7;
      }
    }
    if (state == 7) {
      if (isPressed) {
        if (i >= 20) {
          posXsum += x;
          posYsum += y;
          posSample++;
          if (posSample >= 10) {
            TouchCalibration.max_x = (float)posXsum / (float)posSample;
            TouchCalibration.max_y = (float)posYsum / (float)posSample;

            lv_label_set_text(txtTouchCalibrationStep, "หยุดกดจุด");
            lv_obj_align(txtTouchCalibrationStep, NULL, LV_ALIGN_CENTER, 0, 0);
            lv_obj_set_hidden(objBottomRightTouchPoint, true);

            i = 0;
            state = 8;
          }
        }
        i++;
      } else {
        state = 5;
      }
    }
    if (state == 8) {
      if (!isPressed) {
        i++;
        if (i > 100) {
          state = 9;
        }
      }
    }
    if (state == 9) {
      Serial.printf("min_x: %5d\tmin_y: %5d\n", TouchCalibration.min_x, TouchCalibration.min_y);
      Serial.printf("min_x: %5d\tmin_y: %5d\n", TouchCalibration.max_x, TouchCalibration.max_y);
      break;
    }

    delay(5);
  }
}

void Display_begin() {
  tft.begin(); /* TFT init */
  tft.setRotation(3); /* Landscape orientation */

  lv_init();

  lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);

  /*Initialize the display*/
  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = 320;
  disp_drv.ver_res = 240;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.buffer = &disp_buf;
  lv_disp_drv_register(&disp_drv);

  load_page_main();
  load_page_settings();
  load_page_touch_calibration();

  // Set all label
  lv_label_set_text(txtTime, "LOADING");
  lv_obj_align(txtTime, NULL, LV_ALIGN_IN_LEFT_MID, 20, 0);

  lv_obj_set_hidden(imgWiFi, false);
  lv_obj_set_hidden(imgNexpie, false);

  lv_label_set_text(txtTemp, "");
  lv_obj_align(txtTemp, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -30, -37);

  lv_label_set_text(txtHumi, "");
  lv_obj_align(txtHumi, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -23, -38);

  lv_label_set_text(txtHumi2, "");
  lv_obj_align(txtHumi2, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -24, -38);

  lv_label_set_text(txtLight, "");
  lv_obj_align(txtLight, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -47, -38);

  pinMode(LCD_BL_PIN, OUTPUT);
  digitalWrite(LCD_BL_PIN, LOW);

  do_touch_calibration();

  /*Initialize the (dummy) input device driver*/
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_input_read;
  lv_indev_drv_register(&indev_drv);

  lv_scr_load(MainScreen);
  // lv_scr_load(SettingsScreen);

  wifiConnectQRCode = lv_qrcode_create(objBoxQRCode, 150, lv_color_hex(0x000000), lv_color_hex(0xFFFFFF));
  lv_obj_align(wifiConnectQRCode, NULL, LV_ALIGN_CENTER, 0, 0);
}

void Display_runCycle() {
  static uint64_t ui_update_timer = 0;
  if (((millis() - ui_update_timer) >= 300) || (ui_update_timer == 0)) {
    lv_label_set_text(txtTemp, String(Sensor_get_temp(), 1).c_str());
    lv_obj_align(txtTemp, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -30, -37);

    lv_label_set_text(txtHumi, String(Sensor_get_humi(), 1).c_str());
    lv_obj_align(txtHumi, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -23, -38);

    lv_label_set_text(txtHumi2, String(Sensor_get_soil(), 1).c_str());
    lv_obj_align(txtHumi2, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -24, -38);

    lv_label_set_text(txtLight, String(Sensor_get_lux(), 1).c_str());
    lv_obj_align(txtLight, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -47, -38);

    if (WiFi.isConnected()) {
      lv_obj_set_hidden(imgWiFi, false);
      /*if (client.connected()) {
        lv_obj_set_hidden(imgNexpie, false);
      } else {
        lv_obj_set_hidden(imgNexpie, !lv_obj_get_hidden(imgNexpie));
      }*/
    } else {
      lv_obj_set_hidden(imgWiFi, !lv_obj_get_hidden(imgWiFi));
      lv_obj_set_hidden(imgNexpie, true);
    }

    ui_update_timer = millis();
  }

  static uint64_t lvgl_timer = 0;
  if (((millis() - lvgl_timer) >= 20) || (lvgl_timer == 0)) {
    lv_task_handler(); /* let the GUI do its work */
    lvgl_timer = millis();
  }
}

