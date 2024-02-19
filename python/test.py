import logging

# pylint: disable=import-error
from scom import SerialCommunicatorWrapper


def test_reconstruction(wrapper: SerialCommunicatorWrapper) -> bool:
    input_str = "FA FF 30 00 D1"
    input_bytes = wrapper.string_to_bytes(input_str)
    reconstructed_str = wrapper.bytes_to_string(input_bytes)
    logging.error(f"Input str: {input_str}, reconstructed str: {reconstructed_str}")
    return input_str == reconstructed_str


def test_write(wrapper: SerialCommunicatorWrapper) -> bool:
    input_str = "FA FF 30 00 D1"
    return wrapper.write(input_str)


def main():
    wrapper = SerialCommunicatorWrapper()
    success = wrapper.open("/dev/ttyUSB0", 115200)
    logging.error(f"Success: {success}")

    assert test_reconstruction(wrapper)
    assert test_write(wrapper)


if __name__ == "__main__":
    main()
