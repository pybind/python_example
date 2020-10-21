python_example
==============

[![Gitter][gitter-badge]][gitter-link]

|      CI              | status |
|----------------------|--------|
| Linux/macOS Travis   | [![Travis-CI][travis-badge]][travis-link] |
| MSVC 2015            | [![AppVeyor][appveyor-badge]][appveyor-link] |
| conda.recipe         | [![Conda Actions Status][actions-conda-badge]][actions-conda-link] |
| pip builds           | [![Pip Actions Status][actions-pip-badge]][actions-pip-link] |
| [`cibuildwheel`][]   | [![Wheels Actions Status][actions-wheels-badge]][actions-wheels-link] |

[gitter-badge]:            https://badges.gitter.im/pybind/Lobby.svg
[gitter-link]:             https://gitter.im/pybind/Lobby
[actions-badge]:           https://github.com/pybind/python_example/workflows/Tests/badge.svg
[actions-conda-link]:      https://github.com/pybind/python_example/actions?query=workflow%3A%22Conda
[actions-conda-badge]:     https://github.com/pybind/python_example/workflows/Conda/badge.svg
[actions-pip-link]:        https://github.com/pybind/python_example/actions?query=workflow%3A%22Pip
[actions-pip-badge]:       https://github.com/pybind/python_example/workflows/Pip/badge.svg
[actions-wheels-link]:     https://github.com/pybind/python_example/actions?query=workflow%3AWheels
[actions-wheels-badge]:    https://github.com/pybind/python_example/workflows/Wheels/badge.svg
[travis-link]:             https://travis-ci.org/pybind/python_example
[travis-badge]:            https://travis-ci.org/pybind/python_example.svg?branch=master&status=passed 
[appveyor-link]:           https://ci.appveyor.com/project/wjakob/python-example
<!-- TODO: get a real badge link for appveyor -->
[appveyor-badge]:          https://travis-ci.org/pybind/python_example.svg?branch=master&status=passed

An example project built with [pybind11](https://github.com/pybind/pybind11).

Installation
------------

**On Unix (Linux, OS X)**

 - clone this repository
 - `pip install ./python_example`

**On Windows (Requires Visual Studio 2015)**

 - For Python 3.5+:
     - clone this repository
     - `pip install ./python_example`
 - For Python 2.7:

   Pybind11 requires a C++11 compliant compiler (i.e. Visual Studio 2015 on
   Windows). Running a regular `pip install` command will detect the version
   of the compiler used to build Python and attempt to build the extension
   with it. We must force the use of Visual Studio 2015.

     - clone this repository
     - `"%VS140COMNTOOLS%\..\..\VC\vcvarsall.bat" x64`
     - `set DISTUTILS_USE_SDK=1`
     - `set MSSdk=1`
     - `pip install ./python_example`

   Note that this requires the user building `python_example` to have registry edition
   rights on the machine, to be able to run the `vcvarsall.bat` script.

CI Examples
-----------

There are examples for CI in `.github/workflows`. A simple way to produces
binary "wheels" for all platforms is illustrated in the "wheels.yml" file,
using [`cibuildwheel`][]. You can also see a basic recipe for building and
testing in `pip.yml`, and `conda.yml` has an example of a conda recipe build.

Windows Python 2.7 runtime requirements
----------------------------

On Windows, the Visual C++ 2015 redistributable packages are a runtime
requirement for this project if you build for Python 2.7 (newer versions of
Python include this redistributable). It can be found
[here](https://www.microsoft.com/en-us/download/details.aspx?id=48145).


Building the documentation
--------------------------

Documentation for the example project is generated using Sphinx. Sphinx has the
ability to automatically inspect the signatures and documentation strings in
the extension module to generate beautiful documentation in a variety formats.
The following command generates HTML-based reference documentation; for other
formats please refer to the Sphinx manual:

 - `cd python_example/docs`
 - `make html`

License
-------

pybind11 is provided under a BSD-style license that can be found in the LICENSE
file. By using, distributing, or contributing to this project, you agree to the
terms and conditions of this license.

Test call
---------

```python
import python_example
python_example.add(1, 2)
```

[`cibuildwheel`]:          https://cibuildwheel.readthedocs.io
