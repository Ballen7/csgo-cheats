#ifndef ARDUINO_HELPERS_GLOBAL_H_
#define ARDUINO_HELPERS_GLOBAL_H_

#include <inttypes.h>

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "definitions.h"

namespace Global {

LiquidCrystal lcd_screen
    (LCD_PIN_RS, LCD_PIN_EN, LCD_PIN_D4, LCD_PIN_D5, LCD_PIN_D6, LCD_PIN_D7);

uint32_t prev_press = 0;

bool is_anything_selected = false;
bool need_to_update_screen = true;

bool is_blinking = false;
uint8_t blink_col = 0;
uint8_t blink_row = 0;

byte menu_page = MENU_PAGE_BHOP;

byte wh_mode = WH_MODE_NEAREST;
byte wh_page = WH_PAGE_POS;
byte wh_player_index = 0;

byte bhop_button = BHOP_OFF;

byte trigger_bot_page = TRIGGER_PAGE_STATE;
byte trigger_bot_state = TRIGGER_ON;
int16_t trigger_bot_delay = 0;
uint32_t trigger_bot_delay_start = 0;

byte aim_bot_page = AIM_PAGE_STATE;
byte aim_bot_state = AIM_ON;
byte aim_bot_bone = AIM_BONE_HEAD;
float aim_bot_fov = 5.f;
float aim_bot_smooth = 1.f;

}  // namespace Global

#endif  // ARDUINO_HELPERS_GLOBAL_H_
