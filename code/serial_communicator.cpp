#include "serial_communicator.hpp"

#include <fcntl.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

namespace scom {

SerialCommunicator::~SerialCommunicator() {
  if (fd_ >= 0) {
    close(fd_);
  }
}
bool SerialCommunicator::initialize(const std::string_view port,
                                    const size_t baud_rate) {
  fd_ = open(port.data(), O_RDWR | O_NOCTTY | O_SYNC);
  if (fd_ < 0) {
    std::cerr << "Error opening serial port" << std::endl;
    return false;
  }

  struct termios tty;
  memset(&tty, 0, sizeof tty);
  if (tcgetattr(fd_, &tty) != 0) {
    std::cerr << "Error from tcgetattr" << std::endl;
    return valid();
  }

  // Set baud rate
  cfsetospeed(&tty, baud_rate);
  cfsetispeed(&tty, baud_rate);

  tty.c_cflag |= (CLOCAL | CREAD);  // Ignore modem controls and enable reading
  tty.c_cflag &= ~CSIZE;
  tty.c_cflag |= CS8;       // 8-bit characters
  tty.c_cflag &= ~PARENB;   // No parity bit
  tty.c_cflag &= ~CSTOPB;   // Only need 1 stop bit
  tty.c_cflag &= ~CRTSCTS;  // No hardware flow control

  // Setup for non-canonical mode
  tty.c_iflag &=
      ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
  tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
  tty.c_oflag &= ~OPOST;

  // Fetch bytes as they become available
  tty.c_cc[VMIN] = 1;
  tty.c_cc[VTIME] = 1;

  if (tcsetattr(fd_, TCSANOW, &tty) != 0) {
    std::cerr << "Error from tcsetattr" << std::endl;
  }

  return valid();
}
}  // namespace scom
