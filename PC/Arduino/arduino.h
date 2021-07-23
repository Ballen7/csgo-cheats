#ifndef PC_ARDUINO_ARDUINO_H_
#define PC_ARDUINO_ARDUINO_H_

#pragma comment(lib, "Setupapi.lib")

#include <Windows.h>
#include <SetupAPI.h>
#include <devguid.h>

#include <string>
#include <vector>

#include "Utils/utils.h"

// Commands
#define CMD_JUMP  1  // No arguments
#define CMD_SHOOT 2  // No arguments
#define CMD_AIM   3  // x, y -> how much to move mouse to in X and Y axis
#define CMD_INFO  4  // n - number of NOT dormant enemies (hp, weapon, position)
#define CMD_MAX   5

// Error codes
#define ER_UNKNOWN_CMD 1

class Arduino {
 public:
  static void Connect(LPCSTR com_port);

  static bool SendCommand(char cmd_index, const std::vector<char>& params = {});
  static bool SendData(const char* data, SIZE_T data_size);

  static bool ReadByte(char* byte);

  static bool GetDevice(LPCSTR friendly_name, LPSTR com_port);

 private:
  Arduino() = default;
  ~Arduino();

  static HANDLE arduino_handle_;
};

#endif  // PC_ARDUINO_ARDUINO_H_
