#pragma once
#include <termios.h>

#include <string>
#include <vector>

namespace scom {

/**
 * @brief:  Convert a space delimited hex string to bytes.
 * @param[in]   input_str:  Space delimited hex string
 * @param[in]   bytes:      A vector of bytes
 */
void space_delimited_string_to_hex(const std::string& input_str,
                                   std::vector<char>& bytes);

/**
 * @brief:  Convert a vector of bytes to a space delimited string
 * @param[in]   bytes:      A vector of bytes
 * @return: A space delimitted string representing the hex stream
 */
std::string hex_to_space_delimited_string(const std::vector<char>& bytes);

class SerialCommunicator {
 public:
  SerialCommunicator() : fd_{-1} {}
  ~SerialCommunicator();

  bool write_to_port(const std::string& input_str);

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
