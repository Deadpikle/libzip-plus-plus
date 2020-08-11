/*
 * main.cpp -- test the zip wrapper functions
 *
 * Copyright (c) 2013-2018 David Demelier <markand@malikania.fr>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#define BOOST_TEST_MODULE "libzip++"
#include <boost/test/unit_test.hpp>

#include <zip.hpp>

namespace libzip {

namespace {

/*
 * Sources.
 * ------------------------------------------------------------------
 */

BOOST_AUTO_TEST_SUITE(sources)

BOOST_AUTO_TEST_CASE(file)
{
	remove("output.zip");

	{
		archive archive("output.zip", ZIP_CREATE);
		archive.add(source_file(DIRECTORY "data.txt"), "data.txt");
	}

	archive archive("output.zip");

	auto stats = archive.stat("data.txt");
	auto file = archive.open("data.txt");
	auto content = file.read(stats.size);

	BOOST_TEST(content == "abcdef\n");
}

BOOST_AUTO_TEST_CASE(buffer)
{
	remove("output.zip");

	{
		archive archive("output.zip", ZIP_CREATE);
		archive.add(source_buffer("abcdef"), "data.txt");
	}

	archive archive("output.zip");

	auto stats = archive.stat("data.txt");
	auto file = archive.open("data.txt");
	auto content = file.read(stats.size);

	BOOST_TEST(content == "abcdef");
}

BOOST_AUTO_TEST_SUITE_END()

/*
 * Write.
 * ------------------------------------------------------------------
 */

BOOST_AUTO_TEST_SUITE(write)

BOOST_AUTO_TEST_CASE(simple)
{
	remove("output.zip");

	// Open first and save some data.
	{
		archive archive("output.zip", ZIP_CREATE);
		archive.add(source_buffer("hello world!"), "DATA");
	}

	archive archive("output.zip");

	auto stats = archive.stat("DATA");
	auto file = archive.open("DATA");
	auto content = file.read(stats.size);

	BOOST_TEST(stats.size == 12U);
	BOOST_TEST(content == "hello world!");
}

BOOST_AUTO_TEST_CASE(notexist)
{
	remove("output.zip");

	{
		archive archive("output.zip", ZIP_CREATE);

		/*
		 * According to libzip, adding a file that does not exists
		 * on the disk is not an error.
		 */
		archive.add(source_file("file_not_exist"), "FILE");
	}
}

BOOST_AUTO_TEST_SUITE_END()

/*
 * Reading.
 * ------------------------------------------------------------------
 */

class reading_test {
protected:
	archive archive_;

	reading_test()
		: archive_(DIRECTORY "stats.zip")
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(reading_test_suite, reading_test)

BOOST_AUTO_TEST_CASE(num_entries)
{
	BOOST_TEST(archive_.get_num_entries() == 4U);
}

BOOST_AUTO_TEST_CASE(stat)
{
	const auto stat = archive_.stat("README");

	BOOST_TEST(stat.size == 15U);
	BOOST_TEST(stat.name == "README");
}

BOOST_AUTO_TEST_CASE(exists)
{
	BOOST_TEST(archive_.exists("README"));
}

BOOST_AUTO_TEST_CASE(read)
{
	auto file = archive_.open("README");
	auto stats = archive_.stat("README");
	auto text = file.read(stats.size);

	BOOST_TEST(text == "This is a test\n");
}

BOOST_AUTO_TEST_SUITE(iterator)

BOOST_AUTO_TEST_CASE(increment)
{
	{
		auto it = archive_.begin();

		BOOST_TEST((*it++).name == "README");
	}

	{
		auto it = archive_.begin();

		BOOST_TEST((*++it).name == "INSTALL");
	}

	{
		auto it = archive_.begin() + 1;

		BOOST_TEST((*it).name == "INSTALL");
	}
}

BOOST_AUTO_TEST_CASE(decrement)
{
	{
		auto it = archive_.begin() + 1;

		BOOST_TEST((*it--).name == "INSTALL");
	}

	{
		auto it = archive_.begin() + 1;

		BOOST_TEST((*--it).name == "README");
	}

	{
		auto it = archive_.end() - 1;

		BOOST_TEST((*it).name == "doc/REFMAN");
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(const_iterator)

BOOST_AUTO_TEST_CASE(increment)
{
	{
		auto it = archive_.cbegin();

		BOOST_TEST((*it++).name == "README");
	}

	{
		auto it = archive_.cbegin();

		BOOST_TEST((*++it).name == "INSTALL");
	}

	{
		auto it = archive_.cbegin() + 1;

		BOOST_TEST((*it).name == "INSTALL");
	}
}

BOOST_AUTO_TEST_CASE(decrement)
{
	{
		auto it = archive_.cbegin() + 1;

		BOOST_TEST((*it--).name == "INSTALL");
	}

	{
		auto it = archive_.cbegin() + 1;

		BOOST_TEST((*--it).name == "README");
	}

	{
		auto it = archive_.cend() - 1;

		BOOST_TEST((*it).name == "doc/REFMAN");
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(access)
{
	{
		auto it = archive_.begin();

		BOOST_TEST(it->name == "README");
		BOOST_TEST(it[1].name == "INSTALL");
	}

	{
		auto it = archive_.cbegin();

		BOOST_TEST(it->name == "README");
		BOOST_TEST(it[1].name == "INSTALL");
	}
}

BOOST_AUTO_TEST_CASE(loop)
{
	std::vector<std::string> names{"README", "INSTALL", "doc/", "doc/REFMAN"};
	int i = 0;

	for (const auto& s : archive_)
		BOOST_TEST(s.name == names[i++]);
}

} // !namespace

} // !libzip

BOOST_AUTO_TEST_SUITE_END()
