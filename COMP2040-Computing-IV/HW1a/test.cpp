#define BOOST_TEST_MODULE lfsrtest
#include <boost/test/included/unit_test.hpp>
#include "./LFSR.hpp"

BOOST_AUTO_TEST_SUITE (test)

    BOOST_AUTO_TEST_CASE (test1)
    {
        LFSR lfsr("01101000010", 8);
        BOOST_CHECK(lfsr.step() == 1);
        BOOST_CHECK(lfsr.step() == 1);
        BOOST_CHECK(lfsr.step() == 0);
        BOOST_CHECK(lfsr.step() == 0);
        BOOST_CHECK(lfsr.step() == 1);
        BOOST_CHECK(lfsr.step() == 0);
        BOOST_CHECK(lfsr.step() == 0);
        BOOST_CHECK(lfsr.step() == 1);
        BOOST_CHECK(lfsr.step() == 0);
        BOOST_CHECK(lfsr.step() == 0);
    }

    BOOST_AUTO_TEST_CASE (test2)
    {
        LFSR lfsr("01101000010", 8);
        BOOST_CHECK(lfsr.generate(5) == 25);
        BOOST_CHECK(lfsr.generate(5) == 4);
        BOOST_CHECK(lfsr.generate(5) == 30);
        BOOST_CHECK(lfsr.generate(5) == 27);
        BOOST_CHECK(lfsr.generate(5) == 18);
        BOOST_CHECK(lfsr.generate(5) == 26);
        BOOST_CHECK(lfsr.generate(5) == 28);
        BOOST_CHECK(lfsr.generate(5) == 24);
        BOOST_CHECK(lfsr.generate(5) == 23);
        BOOST_CHECK(lfsr.generate(5) == 29);
    }

BOOST_AUTO_TEST_SUITE_END( )


