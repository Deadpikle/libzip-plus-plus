libzip++ -- A safe modern C++ wrapper around libzip
===================================================

Info about this repo
--------------------
This repo was originally found [here](https://bitbucket.org/markand/libzip/) (404), but @markand ([BitBucket](https://bitbucket.org/markand/), [GitHub](https://github.com/markand)) has since taken the repo down for unknown reasons. The library had a permissive license, so I have re-uploaded the library here for historical purposes. This version unfortunately does not represent the latest version that @markand had available since the project I was using it for never updated to the latest version.

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

Documentation (copied from `mainpage.cpp`)
-------------

### Installation

Just copy the file zippy.hpp and add it to your project.

### Overview

A simple example of the extraction of a file.

```cpp
#include <iostream>

#include "zippy.hpp"
try {
	  zippy::Archive archive("mydata.zip");
 	  zippy::Stat stat = archive.stat("README");
 	  zippy::File file = archive.open("README");
 
 	  std::cout << "content of README:" << std::endl;
 	  std::cout << file.read(stat.size);
} catch (const std::exception &ex) {
 	  std::cerr << ex.what() << std::endl;
}
```

