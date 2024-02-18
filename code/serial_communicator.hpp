#pragma once
#include <termios.h>

namespace scom {
class SerialCommunicator {
 public:
  SerialCommunicator() : valid{false} {}

 private:
  bool valid;
};
}  // namespace scom
