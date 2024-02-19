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


def test_write_read(wrapper: SerialCommunicatorWrapper) -> bool:
    input_str = "FA FF 30 00 D1"
    expected_response = "FA FF 31 00 D0"
    if not wrapper.write(input_str):
        return False

    read_str = wrapper.read(5)
    logging.error(
        f"Testing write_read: expected str {expected_response}, read_str: {read_str}"
    )
    return expected_response == read_str


def main():
    wrapper = SerialCommunicatorWrapper()
    success = wrapper.open("/dev/ttyUSB0", 115200)
    logging.error(f"Success: {success}")

    assert test_reconstruction(wrapper)
    assert test_write(wrapper)
    assert test_write_read(wrapper)


if __name__ == "__main__":
    main()
