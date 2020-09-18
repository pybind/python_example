from setuptools import setup

# With setup_requires, this runs twice - once without setup_requires, and once
# with. The build only happens the second time.
try:
    from pybind11.setup_helpers import Pybind11Extension, build_ext
    from pybind11 import get_cmake_dir
except ImportError:
    from setuptools import Extension as Pybind11Extension
    from setuptools.command.build_ext import build_ext

import sys

__version__ = "0.0.1"

# The main interface is through Pybind11Extension.
# * You can add cxx_std=11/14/17, and then build_ext can be removed.
# * You can set include_pybind11=false to add the include directory yourself,
#   say from a submodule.
#
# Note:
#   Sort input source files if you glob sources to ensure bit-for-bit
#   reproducible builds (https://github.com/pybind/python_example/pull/53)

ext_modules = [
    Pybind11Extension("python_example",
        ["src/main.cpp"],
        # Example: passing in the version to the compiled code
        define_macros = [('VERSION_INFO', __version__)],
        ),
]

setup(
    name="python_example",
    version=__version__,
    author="Sylvain Corlay",
    author_email="sylvain.corlay@gmail.com",
    url="https://github.com/pybind/python_example",
    description="A test project using pybind11",
    long_description="",
    ext_modules=ext_modules,
    # Note: You have to add pybind11 to both setup and install requires to make
    # it available during the build. Using PEP 518's pyproject.toml is better!
    setup_requires=["pybind11 @ git+https://github.com/pybind/pybind11.git@master"],
    install_requires=["pybind11 @ git+https://github.com/pybind/pybind11.git@master"],
    extras_require={"test": "pytest"},
    # Currently, build_ext only provides an optional "highest supported C++
    # level" feature, but in the future it may provide more features.
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
)
