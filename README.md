libzip++ -- A safe modern C++ wrapper around libzip
===================================================

Info about this repo
--------------------
This repo was originally found [here](https://bitbucket.org/markand/libzip/), but @markand has since taken the repo down for unknown reasons. The library had a permissive license, so I have re-uploaded the library here for historical purposes. This version unfortunately does not represent the latest version that @markand had available since the project I was using it for never updated to the latest version.

Introduction
------------

The libzip library is a good C library for opening and creating zip archives, this wrapper provides safe C++ classes
around this great library.

The benefits:

  - Automatic allocations and destructions (RAII),
  - Easy way to add files,
  - Easy API,
  - Easy file reading in archive,
  - Convenience, thanks to C++ function overloads.

Documentation
-------------

See the the [API reference](http://markand.bitbucket.org/libzip).
