from pybind11.setup_helpers import (  # pylint: disable=import-error
    Pybind11Extension,
    build_ext,
)
from setuptools import setup

__version__ = "0.0.1"

ext_modules = [
    Pybind11Extension(
        "scom",
        ["code/bindings.cpp", "code/serial_communicator.cpp"],
        # Example: passing in the version to the compiled code
        define_macros=[("VERSION_INFO", __version__)],
    ),
]

setup(
    name="scom",
    version=__version__,
    author="cakes77lemon",
    author_email="cakes77lemon@gmail.com",
    url="https://github.com/cakes77lemon/serial_communicator",
    description="A serial communicator with a Pybind11 interface.",
    long_description="",
    ext_modules=ext_modules,
    extras_require={"test": "pytest"},
    # Currently, build_ext only provides an optional "highest supported C++
    # level" feature, but in the future it may provide more features.
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
    python_requires=">=3.7",
)
