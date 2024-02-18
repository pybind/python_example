import logging

# pylint: disable=no-name-in-module
from scom import SerialCommunicatorWrapper


def main():
    wrapper = SerialCommunicatorWrapper()
    success = wrapper.open("/dev/ttyUSB0", 115200)
    logging.error(f"Success: {success}")


if __name__ == "__main__":
    main()
