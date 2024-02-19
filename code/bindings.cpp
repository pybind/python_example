#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <iostream>
#include <sstream>

#include "serial_communicator.hpp"

class SerialCommunicatorWrapper {
 public:
  SerialCommunicatorWrapper() {}
  bool open(const std::string_view port, const size_t baud_rate) {
    if (!communicator.initialize(port, baud_rate)) {
      std::cerr << "Failed to open serial port with port: " << port
                << ", baud: " << baud_rate << std::endl;
    } else {
      std::cerr << "Suceessfully opened " << port << ", @ baud " << baud_rate
                << std::endl;
    }
    return communicator.valid();
  }

  std::vector<char> string_to_bytes(const std::string& input_str) const {
    std::vector<char> bytes;
    scom::space_delimited_string_to_hex(input_str, bytes);
    return bytes;
  }

  std::string bytes_to_string(const std::vector<char>& bytes) const {
    return scom::hex_to_space_delimited_string(bytes);
  }

  bool write(const std::string& str) { return communicator.write_to_port(str); }

 private:
  scom::SerialCommunicator communicator{};
};

namespace py = pybind11;

PYBIND11_MODULE(scom, m) {
  py::class_<SerialCommunicatorWrapper>(m, "SerialCommunicatorWrapper")
      .def(py::init<>())
      .def("string_to_bytes", &SerialCommunicatorWrapper::string_to_bytes)
      .def("bytes_to_string", &SerialCommunicatorWrapper::bytes_to_string)
      .def("write", &SerialCommunicatorWrapper::write)
      .def("open", &SerialCommunicatorWrapper::open);
}
