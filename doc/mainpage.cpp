/**
 * \mainpage
 *
 * Welcome to the zip library.
 *
 * ## Introduction
 *
 * The libzip library is a good C library for opening and creating zip archives,
 * this wrapper provides safe C++ classes around this great library.
 *
 * The benefits:
 *
 * - Automatic allocations and destructions (RAII),
 * - Easy way to add files,
 * - Easy API,
 * - Easy file reading in archive,
 * - Read only iterator interface,
 * - Convenience, thanks to C++ function overloads.
 *
 * ## Requirements
 *
 * - [libzip](http://www.nih.at/libzip),
 * - C++17.
 *
 * ## Installation
 *
 * Just copy the file zip.hpp and add it to your project.
 *
 * ## Overview
 *
 * Very simple extraction of a file.
 *
 * ````cpp
 * #include <iostream>
 *
 * #include "zip.hpp"
 *
 * int main()
 * {
 *     try {
 *         libzip::archive archive("mydata.zip");
 *         libzip::stat_info stat = archive.stat("README");
 *         libzip::file file = archive.open("README");
 *
 *         std::cout << "content of README:" << std::endl;
 *         std::cout << file.read(stat.size);
 *     } catch (const std::exception &ex) {
 *         std::cerr << ex.what() << std::endl;
 *     }
 * }
 * ````
 */
