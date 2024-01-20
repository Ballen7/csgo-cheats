#include <Arduino.h>
#include <Keyboard.h>
#include <LiquidCrystal.h>
#include <Mouse.h>

#include "Helpers/definitions.h"
#include "Helpers/global.h"
#include "Helpers/utils.h"

#if 1
uint8_t cnt = 0;
#define DEBUG_PRINTS(x) Serial1.print("pckt "); Serial1.print((0xFF & cnt++), HEX); Serial1.print(": "); Serial1.println(x)
#define DEBUG_PRINT_DELTA(X, Y)  Serial1.print(X, HEX); Serial1.print(","); Serial1.print(Y, HEX); Serial1.print("\n")
#else
#define DEBUG_PRINTS(x)
#define DEBUG_PRINT_DELTA(X, Y)
#endif

void setup() {
  Serial.begin(128000);
  Serial1.begin(115200);

  Global::lcd_screen.begin(16, 2);
  Global::lcd_screen.clear();
  Utils::LoadIcons();

  Mouse.begin();
  Keyboard.begin();

  Utils::LoadAllSettings();

  DEBUG_PRINTS("begin");

}

void loop() {
  if (Serial.available()) {
    int cmd = Serial.read();
    DEBUG_PRINTS("read");
    switch (cmd) {
      case CMD_JUMP: {
        DEBUG_PRINTS("jump");
        if (Global::bhop_button == BHOP_BTN_SPACE) {
          Keyboard.write(' ');
        } else if (Global::bhop_button == BHOP_BTN_MWHUP) {
          Mouse.move(0, 0, 127);
        }
        break;
      }

      case CMD_SHOOT: {
        DEBUG_PRINTS("shoot!!!!!!!");
        if (Global::trigger_bot_state == TRIGGER_ON) {
          if (!Global::trigger_bot_delay) {
            DEBUG_PRINTS("click");
            Mouse.click(MOUSE_LEFT);
          } else {
            if (!Global::trigger_bot_delay_start) {
              Global::trigger_bot_delay_start = millis();
            }
          }
        }
        break;
      }

      case CMD_AIM: {
        DEBUG_PRINTS("aim");
        // We must always read |delta_x| and |delta_y|!
        // (Else they will be read as command)
        char delta_x = static_cast<char>(Serial.read());
        char delta_y = static_cast<char>(Serial.read());
        if (Global::aim_bot_state == AIM_ON) {
          DEBUG_PRINTS("moving mouse (x,y): ");
          DEBUG_PRINT_DELTA(delta_x, delta_y);
          Mouse.move(delta_x, delta_y, 0);
        }
        break;
      }

      case CMD_UPDATE: {
        DEBUG_PRINTS("update");
        Utils::SendResponse(ARD_CMD_SET_BONE, Global::aim_bot_bone);
        Utils::SendResponse32(ARD_CMD_SET_FOV, Global::aim_bot_fov);
        Utils::SendResponse32(ARD_CMD_SET_SMOOTH, Global::aim_bot_smooth);
        break;
      }

      default: {
        DEBUG_PRINTS("default");
        Utils::SendResponse(ARD_ER_UNKNOWN_CMD);
        break;
      }
    }
  }

  if (Global::trigger_bot_delay_start
      && (millis() - Global::trigger_bot_delay_start)
         > Global::trigger_bot_delay) {
    Mouse.click(MOUSE_LEFT);
    Global::trigger_bot_delay_start = 0;
  }
/*
  if (Global::need_to_update_screen) {
    Utils::UpdateScreen();
  }

  switch (Utils::GetKeypadButton()) {
    case KP_NONE: {
      break;
    }

    case KP_RIGHT: {
      Utils::OnKpRightClicked();
      break;
    }

    case KP_UP: {
      Utils::OnKpUpClicked();
      break;
    }

    case KP_DOWN: {
      Utils::OnKpDownClicked();
      break;
    }

    case KP_LEFT: {
      Utils::OnKpLeftClicked();
      break;
    }

    case KP_SELECT: {
      Utils::OnKpSelectClicked();
      break;
    }
  }
  */
}
