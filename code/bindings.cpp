#include <pybind11/pybind11.h>

#include <iostream>

#include "serial_communicator.hpp"

class SerialCommunicatorWrapper {
 public:
  SerialCommunicatorWrapper() {}
  void here(const int num) const {
    std::cout << "Here with " << num << std::endl;
  }

 private:
  scom::SerialCommunicator scom{};
};

namespace py = pybind11;

PYBIND11_MODULE(scom, m) {
  py::class_<SerialCommunicatorWrapper>(m, "SerialCommunicatorWrapper")
      .def(py::init<>())
      .def("here", &SerialCommunicatorWrapper::here);
}
