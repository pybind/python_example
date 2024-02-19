#include "serial_communicator.hpp"

#include <fcntl.h>
#include <unistd.h>

#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace scom {

void space_delimited_string_to_hex(const std::string& input_str,
                                   std::vector<char>& bytes) {
  bytes.clear();
  std::istringstream input_stream(input_str);
  std::string byte_string;
  while (std::getline(input_stream, byte_string, ' ')) {
    std::stringstream ss;
    ss << std::hex << byte_string;

    // This is needed because if byte was unsinged char, then >>
    // treats it as an alphabet text instead of number
    unsigned int byte;
    ss >> byte;
    bytes.emplace_back(static_cast<unsigned char>(byte));
  }
}

std::string hex_to_space_delimited_string(const std::vector<char>& bytes) {
  std::ostringstream output_stream;
  for (auto iter = bytes.begin(); iter != bytes.end(); ++iter) {
    output_stream << std::uppercase << std::setw(2) << std::setfill('0')
                  << std::hex << static_cast<int>(*iter);

    if (std::next(iter) != bytes.end()) {
      output_stream << " ";
    }
  }
  return output_stream.str();
}

SerialCommunicator::~SerialCommunicator() {
  if (fd_ >= 0) {
    close(fd_);
  }
}

bool SerialCommunicator::write_to_port(const std::string& input_str) {
  if (!valid()) {
    std::cerr << "Failed to write to port because port is invalid."
              << std::endl;
    return false;
  }
  std::vector<char> bytes;
  space_delimited_string_to_hex(input_str, bytes);
  const auto num_bytes_written = write(fd_, bytes.data(), bytes.size());
  return num_bytes_written == bytes.size();
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
