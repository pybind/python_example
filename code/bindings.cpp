#include <pybind11/pybind11.h>

#include <iostream>
#include <sstream>

#include "serial_communicator.hpp"

class SerialCommunicatorWrapper {
 public:
  SerialCommunicatorWrapper() {}
  bool open(const std::string_view port, const size_t baud_rate) {
    if (!scom.initialize(port, baud_rate)) {
      std::cerr << "Failed to open serial port with port: " << port
                << ", baud: " << baud_rate << std::endl;
    } else {
      std::cerr << "Suceessfully opened " << port << ", @ baud " << baud_rate
                << std::endl;
    }
    return scom.valid();
  }

 private:
  scom::SerialCommunicator scom{};
};

namespace py = pybind11;

PYBIND11_MODULE(scom, m) {
  py::class_<SerialCommunicatorWrapper>(m, "SerialCommunicatorWrapper")
      .def(py::init<>())
      .def("open", &SerialCommunicatorWrapper::open);
}
