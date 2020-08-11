libzip++ -- A safe modern C++ 17 wrapper around libzip
===================================================

Info about this repo
--------------------
This repo was originally found [here](https://bitbucket.org/markand/libzip/) (404), but @markand ([BitBucket](https://bitbucket.org/markand/), [GitHub](https://github.com/markand), [Website](http://markand.fr/), [Mercurial Server](http://hg.markand.fr)) has since taken the repo down for unknown reasons. The library had a permissive license, so I have re-uploaded/mirrored the library here for historical purposes.

In August 2020, the original library was found in a more updated version on the original author's Mercurial server [here](http://hg.markand.fr/libzip/summary). I updated the code in this repo accordingly!

Introduction
------------

The libzip library is a good C library for opening and creating zip archives,
this wrapper provides safe C++ classes around this great library.

The benefits:

- Automatic allocations and destructions (RAII),
- Easy way to add files,
- Easy API,
- Easy file reading in archive,
- Read only iterator interface,
- Convenience, thanks to C++ function overloads.

Documentation (copied from `mainpage.cpp`)
-------------

### Installation

Just copy the file zippy.hpp and add it to your project.

### Overview

A simple example of the extraction of a file.

```cpp
#include <iostream>

#include "zip.hpp"

int main()
{
    try {
        libzip::archive archive("mydata.zip");
        libzip::stat_info stat = archive.stat("README");
        libzip::file file = archive.open("README");

        std::cout << "content of README:" << std::endl;
        std::cout << file.read(stat.size);
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
}
```

Other libzip wrappers
---------------------

* [libzippp](https://github.com/ctabin/libzippp)