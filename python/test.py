from scom import SerialCommunicatorWrapper


def main():
    wrapper = SerialCommunicatorWrapper()
    wrapper.here(10)


if __name__ == "__main__":
    main()
