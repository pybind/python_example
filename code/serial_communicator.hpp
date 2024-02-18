#pragma once
#include <termios.h>

#include <string>

namespace scom {
class SerialCommunicator {
 public:
  SerialCommunicator() : fd_{-1} {}
  ~SerialCommunicator();

  /**
   * @brief: Check if communicator is valid
   * @return: True, if valid
   */
  bool valid() const { return fd_ >= 0; }
  /**
   * @brief:	Initialize serial communication on a specific port
   * @param[in]	port: 		Port name
   * @param[in]	baud_rate:	Baud rate in bps
   * @return: True, if success
   */
  bool initialize(const std::string_view port, const size_t baud_rate);

 private:
  int fd_ = -1;
};
}  // namespace scom
